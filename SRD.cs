using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Collections.ObjectModel;
using System.Text;
using System.Text.RegularExpressions;
using System.Data;
using System.Data.SqlClient;
using System.Xml;
using System.Xml.XPath;
using System.Timers;

using Oracle.DataAccess.Client;
using iTextSharp.text;
using iTextSharp.text.pdf;

using aSchedule.Logic.DAL;
using aSchedule.Logic.Entity;
using aSchedule.Logic.Manager;
using aSchedule.Logic.Secure;
using aSchedule.ar.gov.afip;

using System.Globalization;
using System.Diagnostics;

namespace aSchedule
{
    class SRD
    {
        #region Global Vars
        OracleConnection oraConn;
        OracleCommand oraCmd;
        SqlConnection sqlConn;
        SqlCommand sqlCmd;
        Config configuracion = null;
        ConfigMngr cnfgMngr = null;
        Emailing emailing;
        bool espera = false;
        int esperas = 0;
        bool countersEnable;
        PerformanceCounter totalDesp = null;
        PerformanceCounter totalCalls = null;
        private static SRD instance = null;
        private static SRD instanceDesa = null;
        bool dontCheckTimes = true;
        int ejecucion=0;
        const String cuitLakaut = "30710964277";
        const bool isDesaMode = false;
        aSchedule.Logic.WS.afip AFIP = new aSchedule.Logic.WS.afip();
        #endregion

        #region Constructor

        private SRD(int mode)
        {
            try
            {
                Console.WriteLine("Email");
                emailing = Emailing.Instance;
                Console.WriteLine("Config");
                configuracion = new Config();
                Console.WriteLine("ConfigMngr");
                cnfgMngr = new ConfigMngr();
                Console.WriteLine("Modo:" + mode);
                configuracion = mode == 1 ? cnfgMngr.getConfig() : cnfgMngr.getConfigDESA();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static SRD Instance
        {
            get
            {
                Console.WriteLine("Obteniendo instancia srd(1)...");
                return instance = new SRD(1);
            }
        }

        public static SRD InstanceDesa
        {
            get
            {
                return instanceDesa = new SRD(2);
            }
        }

        #endregion

        #region Startup

        /// <summary>
        /// Los siguientes tres procesos inician la insercion de despachos a la DB filtrando por configuración.
        /// </summary>
        public void Iniciar()
        {
            Despachos("*");
        }
        public void IniciarUno()
        {
            Despachos(configuracion.FiltroUno);
        }
        public void IniciarDos()
        {
            Despachos(configuracion.FiltroDos);
        }
        public void IniciarTres()
        {
            Despachos(configuracion.FiltroTres);
        }
        public void IniciarDegiacomo()
        {
            DespachosDegiacomo();
        }
        /// <summary>
        /// 
        /// </summary>
        public void iniciarAvisoAfip()
        {
            adviceNewsDocument();
        }

        /// <summary>
        /// Inicio del proceso de inserción de despachos en SRD recursivo.
        /// </summary>
        public void DespachosRecursive()
        {
            Console.WriteLine("Dentro de instancia Recursiva...");
            dontCheckTimes = false;
            try
            {
                if (ejecucion >= 3)
                {
                    emailing.Soporte("SRD Schedule Despacho", "CheckTimes OFF!!! Ejecución: " + ejecucion);
                    dontCheckTimes = true;
                    ejecucion = 0;
                }
                Console.WriteLine("Iniciando ciclo Despachos(*)");
                Despachos("*");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                emailing.Soporte("DESPACHOS - No controlada", ex);
            }
            ejecucion++;
            DespachosRecursive();
        }

        #endregion

        #region Procesar Despachos
        /// <summary>
        /// Procesa los documentos unidos los ingresa a la BD de SRD y los mueve a la carpeta "Importados" para luego depurar.
        /// </summary>
        private void Despachos(String filter)
        {
            Console.WriteLine("Iniciando flujo... ");

            try
            {
                countersEnable = false;

                if (setupPerformanceCounter())
                {
                   // Total despachos ingresados
                   totalDesp = new PerformanceCounter();
                   totalDesp.CategoryName = "SRDTask";
                   totalDesp.CounterName = "Total PDF/FS";
                   totalDesp.MachineName = ".";
                   totalDesp.ReadOnly = false;
                   totalDesp.IncrementBy(-totalDesp.Increment());

                   // Total llamadas afip
                   totalCalls = new PerformanceCounter();
                   totalCalls.CategoryName = "SRDTask";
                   totalCalls.CounterName = "Total Afip Calls";
                   totalCalls.MachineName = ".";
                   totalCalls.ReadOnly = false;
                   totalCalls.IncrementBy(-totalCalls.Increment());
                }

                Console.WriteLine("Obteniendo configuración... ");

                Console.WriteLine("Running config: " + configuracion.DesaMode);
                string ruta = configuracion.DesaMode? @"C:\A importar a la DB" : configuracion.Archivos;
                Console.WriteLine(ruta);
                
                if (Directory.Exists(ruta))
                {
                    oraConn = configuracion.DesaMode? Conexion.InstanceDESA() : Conexion.Instance();

                    if (dontCheckTimes)
                    {
                        oraCmd = new OracleCommand();
                        oraCmd.Connection = oraConn;
                        oraCmd.CommandText = "DELETE FROM SRD_LOGS";
                        oraCmd.CommandType = CommandType.Text;
                        oraCmd.ExecuteNonQuery();
                    }

                    string[] files = Directory.GetFiles(ruta, filter + ".pdf");
                    if (files.Length > 0)
                    {
                        foreach (string pdf in files)
                        {
                            if (pdf.Contains("11037IC03000014C"))
                            {
                                try
                                {
                                    if (checkTimes(pdf))
                                    {
                                        if (countersEnable) totalDesp.Increment();

                                        string despacho = pdf.Replace(ruta, "").Replace("\\", "").ToUpper().Replace(".PDF", "");
                                        Console.WriteLine("Obteniendo Despacho: " + despacho);
                                        string cuitcliente = "";
                                        string cliente = "";
                                        string cuitdespachante = "";
                                        string despachante = "";
                                        string paginas = "";
                                        string nrointerno = "0";
                                        string tipoOper = "";
                                        string sigea = "";
                                        int idGuiaDetalle = 0;
                                        DateTime fecOfi = DateTime.MinValue;
                                        DateTime dateToInsert = DateTime.Now;
                                        int bytespdf = 0;
                                        aSchedule.Logic.Manager.Guias.GuiaAdapterMngr avisoFacturar = new Logic.Manager.Guias.GuiaAdapterMngr();


                                        if (VerificadorDespacho(despacho))
                                        {
                                            if (ValidarDespacho(despacho))
                                            {
                                                /* ************************ NOMRALES ************************ */
                                                #region Normal



                                                FileStream fls = new FileStream(pdf, FileMode.Open, FileAccess.Read);
                                                bytespdf = System.Convert.ToInt32(fls.Length);
                                                fls.Close();

                                                XmlDocument xd = new XmlDocument();
                                                xd.Load(pdf.ToUpper().Replace(".PDF", ".XML"));

                                                string imageneslote = "";
                                                string paginaslote = "";
                                                int caja = 0;

                                                XmlNodeList nodeList = xd.SelectNodes("//root/document/field");
                                                foreach (XmlNode nd in nodeList)
                                                    switch (nd.Attributes[1].Value)
                                                    {
                                                        case "Recuento de imágenes en documento":
                                                            imageneslote = nd.Attributes[2].Value;
                                                            break;
                                                        case "Image count in document":
                                                            imageneslote = nd.Attributes[2].Value;
                                                            break;
                                                        case "Recuento de páginas en documento":
                                                            paginaslote = nd.Attributes[2].Value;
                                                            break;
                                                        case "Page count in document":
                                                            paginaslote = nd.Attributes[2].Value;
                                                            break;
                                                        case "Caja Fisica":
                                                            caja = int.Parse(nd.Attributes[2].Value);
                                                            break;
                                                    }
                                                xd = null;

                                                // Trato de obtener los datos de Solobian, caso contrario de BAS.
                                                bool isInSolobian = false; //<-- Indica si esta en BAS
                                                bool isInSRD = false; //<-- Indica si esta en SRD
                                                bool fechaVeintidos = false; //<-- doc[0].fechapres es igual al 22 de feb; aviso y digi, Post solo digi
                                                Console.WriteLine("Obteniendo Datos de Solovian.... ");
                                                Documento[] doc = getsolobianData(despacho);

                                                if (doc.Length > 0)
                                                {
                                                    cuitcliente = doc[0].cuit_i;
                                                    cliente = doc[0].nombre_i;
                                                    cuitdespachante = doc[0].cuit_d;
                                                    despachante = doc[0].nombre_d;
                                                    paginas = doc[0].fojas;

                                                    try { nrointerno = doc[0].nrointerno; }
                                                    catch { nrointerno = "00"; }
                                                    nrointerno = (nrointerno == null) ? "0" : nrointerno;
                                                    nrointerno = (nrointerno.Trim().Equals("")) ? "0" : nrointerno;

                                                    tipoOper = doc[0].tipo_op;
                                                    fecOfi = doc[0].fecofi;
                                                    try
                                                    {
                                                        isInSolobian = (paginas != null && (Convert.ToInt32(paginas) > 0) && !cliente.Equals("Sistema anterior"));
                                                        fechaVeintidos = (DateTime.Parse(doc[0].fechapres).Day == 22 && DateTime.Parse(doc[0].fechapres).Month == 2 && paginas != null);
                                                    }
                                                    catch (Exception ex)
                                                    {
                                                        Informe("SCHEDULE", ex.Message + "Despacho: " + despacho, "", "");
                                                    }
                                                }
                                                else
                                                {
                                                    Console.WriteLine("NO ENCONTRADO EN SOLOVIAN");
                                                }

                                                // Si no se encontro en Solobian, lo busco en SRD.
                                                if (!isInSolobian)
                                                {
                                                    Console.WriteLine("Obteniendo Datos de SRD-GUIAS.... ");
                                                    try
                                                    {
                                                        oraCmd = new OracleCommand();
                                                        oraCmd.Connection = oraConn;
                                                        oraCmd.CommandText = "SCH_P_LOADFROMGUIAS";
                                                        oraCmd.CommandType = CommandType.StoredProcedure;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Anio", OracleDbType.Decimal)).Value = "20" + despacho.Substring(0, 2);
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Aduana", OracleDbType.Varchar2, 3)).Value = despacho.Substring(2, 3);
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoTipo", OracleDbType.Varchar2, 4)).Value = despacho.Substring(5, 4).ToUpper();
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoNro", OracleDbType.Varchar2, 6)).Value = despacho.Substring(9, 6);
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Letra", OracleDbType.Varchar2, 1)).Value = despacho.Substring(15, 1).ToUpper();
                                                        oraCmd.Parameters.Add(new OracleParameter("O_Cursor", OracleDbType.RefCursor)).Direction = ParameterDirection.Output;

                                                        OracleDataReader odr = oraCmd.ExecuteReader();

                                                        if (odr.Read())
                                                        {
                                                            Console.WriteLine("  LEYENDO DATOS DE SRD GUIAS...");
                                                            idGuiaDetalle = (odr.IsDBNull(odr.GetOrdinal("IDNS_GUIA_DETALLE"))) ? 0 : int.Parse(odr.GetDecimal(odr.GetOrdinal("IDNS_GUIA_DETALLE")).ToString());
                                                            paginas = (odr.IsDBNull(odr.GetOrdinal("NS_FOJAS"))) ? "0" : odr.GetDecimal(odr.GetOrdinal("NS_FOJAS")).ToString();
                                                            nrointerno = (odr.IsDBNull(odr.GetOrdinal("SD_NRO_INTERNO"))) ? "0" : odr.GetOracleString(odr.GetOrdinal("SD_NRO_INTERNO")).ToString();
                                                            cuitcliente = (odr.IsDBNull(odr.GetOrdinal("CUIT_IMEX"))) ? "" : odr.GetOracleString(odr.GetOrdinal("CUIT_IMEX")).ToString();
                                                            cliente = (odr.IsDBNull(odr.GetOrdinal("SD_IMEX"))) ? "" : odr.GetOracleString(odr.GetOrdinal("SD_IMEX")).ToString();
                                                            cuitdespachante = (odr.IsDBNull(odr.GetOrdinal("SD_CUIT_DESPACHANTE"))) ? "" : odr.GetOracleString(odr.GetOrdinal("SD_CUIT_DESPACHANTE")).ToString();
                                                            despachante = (odr.IsDBNull(odr.GetOrdinal("SD_DESPACHANTE"))) ? "" : odr.GetOracleString(odr.GetOrdinal("SD_DESPACHANTE")).ToString();
                                                            fecOfi = (odr.IsDBNull(odr.GetOrdinal("H_OFICIALIZACION"))) ? DateTime.MinValue : DateTime.Parse(odr.GetOracleDate(odr.GetOrdinal("H_OFICIALIZACION")).ToString());
                                                            tipoOper = "AUT";
                                                            isInSRD = (paginas != null && (Convert.ToInt32(paginas) > 0) && !cliente.Equals("") && (idGuiaDetalle > 0));
                                                        }
                                                        else
                                                        {
                                                            Console.WriteLine("NO ENCONTRADO EN SRD-GUIAS");
                                                        }

                                                        odr = null;
                                                    }
                                                    catch (Exception ex)
                                                    {
                                                        emailing.Soporte("SRD SChedule - SRD_GUIAS", ex);
                                                        isInSRD = false;
                                                    }
                                                    finally
                                                    {
                                                        oraCmd = null;
                                                    }
                                                }

                                                // Si se pudo obtener algo, asi sea de SRD o Solobian; continuo...
                                                if (isInSolobian || isInSRD)
                                                {
                                                    if (cuitcliente.Length == 11)
                                                    {
                                                        if (paginas != "")
                                                        {
                                                            if (ValidaCuit(cuitcliente))
                                                            {

                                                                if ((cuitcliente.Length == 11) && (ValidaCuit(cuitcliente)))
                                                                {
                                                                    if ((cuitdespachante.Length == 11) && (ValidaCuit(cuitdespachante)))
                                                                    {
                                                                        if (tryParse(paginas))
                                                                        {
                                                                            Console.WriteLine("  DESPACHO VALIDADO");

                                                                            oraCmd = new OracleCommand();
                                                                            oraCmd.Connection = oraConn;
                                                                            OracleTransaction transaccionAfip = oraConn.BeginTransaction(IsolationLevel.ReadCommitted);
                                                                            try
                                                                            {

                                                                                byte[] saltC = Hashing.GenerateSalt();
                                                                                string saltStrC = Convert.ToBase64String(saltC);
                                                                                string passwordC = Hashing.GetSHA256("SERTEARSRD", saltC);

                                                                                byte[] saltD = Hashing.GenerateSalt();
                                                                                string saltStrD = Convert.ToBase64String(saltD);
                                                                                string passwordD = Hashing.GetSHA256("SERTEARSRD", saltD);

                                                                                Console.WriteLine("  AGREGANDO DOCUMENTO A SISTEMA SRD...");

                                                                                oraCmd.CommandText = "SCH_P_DOCUMENTOS_ADD";
                                                                                //oraCmd.CommandText = "SCH_P_DOCUMENTOS_UPD";
                                                                                oraCmd.CommandType = CommandType.StoredProcedure;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_Anio", OracleDbType.Decimal)).Value = "20" + despacho.Substring(0, 2);
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_Aduana", OracleDbType.Varchar2, 3)).Value = despacho.Substring(2, 3);
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoTipo", OracleDbType.Varchar2, 4)).Value = despacho.Substring(5, 4).ToUpper();
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoNro", OracleDbType.Varchar2, 6)).Value = despacho.Substring(9, 6);
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_Letra", OracleDbType.Varchar2, 1)).Value = despacho.Substring(15, 1).ToUpper();
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_Caja", OracleDbType.Varchar2, 20)).Value = caja;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_NC_Paginas", OracleDbType.Decimal)).Value = (int.Parse(paginaslote) - 1).ToString(); //paginas
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasLote", OracleDbType.Decimal)).Value = imageneslote;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasPDF", OracleDbType.Decimal)).Value = PdfUtils.Instance.cantPaginas(pdf); ;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasFacturador", OracleDbType.Decimal)).Value = paginas;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_CuitDespachante", OracleDbType.Varchar2, 11)).Value = cuitdespachante;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_Despachante", OracleDbType.Varchar2, 100)).Value = despachante.ToUpper().Trim();
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_CuitImportadorExportador", OracleDbType.Varchar2, 11)).Value = cuitcliente;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_ImportadorExportador", OracleDbType.Varchar2, 100)).Value = cliente.ToUpper().Trim();
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_NC_BytesPdf", OracleDbType.Decimal)).Value = bytespdf.ToString();
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_PasswordD", OracleDbType.Varchar2, 128)).Value = passwordD;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_SaltD", OracleDbType.Varchar2, 50)).Value = saltStrD;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_PasswordC", OracleDbType.Varchar2, 128)).Value = passwordC;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_SaltC", OracleDbType.Varchar2, 50)).Value = saltStrC;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_NC_NumeroInterno", OracleDbType.Varchar2, 100)).Value = nrointerno.ToString();
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_H_Upd", OracleDbType.Date)).Value = dateToInsert;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_SD_TipoOpe", OracleDbType.Varchar2, 24)).Value = tipoOper;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_H_Oficializacion", OracleDbType.Date)).Value = (fecOfi == DateTime.Parse("01/01/0001")) ? (object)DBNull.Value : fecOfi;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_NS_Digitalizador", OracleDbType.Decimal)).Value = "1";
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_NS_Resguardante", OracleDbType.Decimal)).Value = "3";
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_Resultado", OracleDbType.Varchar2, 100)).Direction = ParameterDirection.Output;
                                                                                oraCmd.Parameters.Add(new OracleParameter("P_BytesExistente", OracleDbType.Varchar2, 100)).Direction = ParameterDirection.Output;

                                                                                oraCmd.ExecuteNonQuery(); Console.WriteLine("  Store ejecutado!");

                                                                                string respuesta = oraCmd.Parameters["P_Resultado"].Value.ToString();
                                                                                string bytesExistente = oraCmd.Parameters["P_BytesExistente"].Value.ToString();

                                                                                if (!respuesta.Equals("0") && !configuracion.DesaMode)
                                                                                {
                                                                                    #region Aviso Afip
                                                                                    try
                                                                                    {
                                                                                        Console.WriteLine("  Avisando Afip...");

                                                                                        //if (countersEnable) totalCalls.Increment();

                                                                                        // Aviso Digit: Se informa Siempre.
                                                                                        CultureInfo ci = CultureInfo.InvariantCulture;
                                                                                        string hora = DateTime.Now.ToString("dd/MM/yyyy HH:mm:ss", ci);
                                                                                        hora = hora.Substring(11, 8).Replace(":", ""); // Extraigo
                                                                                        hora = hora + respuesta; // Adjunto

                                                                                        // Key de la URL
                                                                                        string key = despacho + hora;
                                                                                        Encryption64 enc = new Encryption64();
                                                                                        String encriptionResult = enc.Encrypt(key, enc.getDefaultKey());
                                                                                        String UrlDespacho = "www.sertears.com.ar/srd/getPdf.aspx?qid=" + encriptionResult;

                                                                                        // Aviso de digitalización
                                                                                        afipDigit.Recibo errorCode = AFIP.avisoDigitalizacion(
                                                                                            despacho,
                                                                                            cuitdespachante,
                                                                                            cuitLakaut,
                                                                                            cuitcliente,
                                                                                            "",
                                                                                            "000",
                                                                                            UrlDespacho,
                                                                                            getFamilyNumbers(pdf),
                                                                                            DateTime.Now,
                                                                                            "",
                                                                                            Hashing.Instance.GetAfipHash(pdf),
                                                                                            int.Parse(paginas),
                                                                                            sigea);

                                                                                        // TODO: Aviso de PSAD provisorio: 23/09/2010
                                                                                        if (errorCode.descError.Contains("No se encuentra en estado PSAD el legajo"))
                                                                                        {
                                                                                            Console.WriteLine("  No se encuentra en estado PSAD... ReAvisando PSAD...");
                                                                                            String now = String.Format("{0:s}", DateTime.Now);
                                                                                            String fechaHora = now + ".796875-03:00";
                                                                                            AFIP.avisoRecepAcept(despacho, cuitdespachante, cuitLakaut, cuitcliente, "000", fechaHora, "", "");
                                                                                            Console.WriteLine("  No se encuentra en estado PSAD... ReAvisando PSAD...");
                                                                                        }

                                                                                        Console.WriteLine("Rta Afip: " + errorCode.codError + " - " + errorCode.descError);

                                                                                        // Si se pudo realizar la digitalizacion:
                                                                                        if (errorCode.codError == 0)
                                                                                        {
                                                                                            Console.WriteLine("  ************* Moviendo... *************");
                                                                                            string destinationFolder = string.Concat(new object[] { @"", dateToInsert.Year, @"\", dateToInsert.Month.ToString("00"), @"\", dateToInsert.Day.ToString("00"), @"\" });

                                                                                            Console.WriteLine("  Copiando el archivo: " + pdf);
                                                                                            Console.WriteLine(pdf.ToUpper().Replace(@"SRD\A IMPORTAR A LA DB\", destinationFolder));

                                                                                            File.Copy(pdf, pdf.Replace(@"srd\A importar a la DB\", destinationFolder), true);
                                                                                            // Me fijo si pudo copiarlo
                                                                                            if (File.Exists(pdf.Replace(@"srd\A importar a la DB\", destinationFolder)))
                                                                                            {
                                                                                                Console.WriteLine("  Commit en bd...");
                                                                                                transaccionAfip.Commit();

                                                                                                Console.WriteLine("  Borrando pdf...");
                                                                                                File.Delete(pdf);

                                                                                                Console.WriteLine("  Copiando xml...");

                                                                                                while (!File.Exists(pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder)))
                                                                                                    File.Copy(pdf.ToUpper().Replace(".PDF", ".XML"), pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder), true);

                                                                                                if (File.Exists(pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder)))
                                                                                                {
                                                                                                    Console.WriteLine("  Borrando xml...");
                                                                                                    File.Delete(pdf.ToUpper().Replace(".PDF", ".XML"));
                                                                                                }
                                                                                                Console.WriteLine("  Fin!");

                                                                                                //avisoFacturar.avisoFacturacionWout(despacho, idGuiaDetalle);
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                Console.WriteLine("  NO SE PUDO MOVER EL ARCHIVO: " + pdf);
                                                                                                emailing.Soporte("SRD SChedule Despacho", "No se pudo copiar el archivo: " + pdf + " Reinforme de afip - intento DIGI.");
                                                                                                transaccionAfip.Rollback();
                                                                                            }
                                                                                        }
                                                                                        else if (errorCode.codError == 102 && (errorCode.descError.Contains("DIGI") || errorCode.descError.Contains("DIEN") || errorCode.descError.Contains("DEEN") || errorCode.descError.Contains("RELE")))
                                                                                        {
                                                                                            Console.WriteLine("  Moviendo por error afip 102");
                                                                                            string destinationFolder = string.Concat(new object[] { @"", dateToInsert.Year, @"\", dateToInsert.Month.ToString("00"), @"\", dateToInsert.Day.ToString("00"), @"\" });

                                                                                            Console.WriteLine("  Copiando el archivo: " + pdf);
                                                                                            File.Copy(pdf, pdf.Replace(@"srd\A importar a la DB\", destinationFolder), true);

                                                                                            if (File.Exists(pdf.Replace(@"srd\A importar a la DB\", destinationFolder)))
                                                                                            {
                                                                                                Console.WriteLine("  Commit en bd...");
                                                                                                transaccionAfip.Commit();

                                                                                                Console.WriteLine("  Borrando pdf...");
                                                                                                File.Delete(pdf);

                                                                                                Console.WriteLine("  Copiando xml...");
                                                                                                while (!File.Exists(pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder)))
                                                                                                    File.Copy(pdf.ToUpper().Replace(".PDF", ".XML"), pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder), true);

                                                                                                if (File.Exists(pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder)))
                                                                                                {
                                                                                                    Console.WriteLine("  Borrando xml...");
                                                                                                    File.Delete(pdf.ToUpper().Replace(".PDF", ".XML"));
                                                                                                }

                                                                                                if (errorCode.descError.Contains("DIGI"))
                                                                                                {
                                                                                                    oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate=3 WHERE IDNS_Documento =" + respuesta;
                                                                                                    oraCmd.CommandType = CommandType.Text;
                                                                                                    oraCmd.ExecuteNonQuery();
                                                                                                }
                                                                                                else if (errorCode.descError.Contains("DIEN"))
                                                                                                {
                                                                                                    oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate=4 WHERE IDNS_Documento =" + respuesta;
                                                                                                    oraCmd.CommandType = CommandType.Text;
                                                                                                    oraCmd.ExecuteNonQuery();
                                                                                                }
                                                                                                else if (errorCode.descError.Contains("DEEN"))
                                                                                                {
                                                                                                    oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate=5 WHERE IDNS_Documento =" + respuesta;
                                                                                                    oraCmd.CommandType = CommandType.Text;
                                                                                                    oraCmd.ExecuteNonQuery();
                                                                                                }
                                                                                                else if (errorCode.descError.Contains("RELE"))
                                                                                                {
                                                                                                    oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate=6 WHERE IDNS_Documento =" + respuesta;
                                                                                                    oraCmd.CommandType = CommandType.Text;
                                                                                                    oraCmd.ExecuteNonQuery();
                                                                                                }

                                                                                                Console.WriteLine("  Fin!");
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                Console.WriteLine("  NO SE PUDO MOVER EL ARCHIVO: " + pdf);
                                                                                                emailing.Soporte("SRD SChedule Despacho", "No se pudo copiar el archivo: " + pdf + " Reinforme de afip - intento POR 102");
                                                                                                transaccionAfip.Rollback();
                                                                                            }
                                                                                        }
                                                                                        else if (errorCode.codError == 101)
                                                                                        {
                                                                                            Console.WriteLine("  Moviendo por error afip 101");
                                                                                            string destinationFolder = string.Concat(new object[] { @"", dateToInsert.Year, @"\", dateToInsert.Month.ToString("00"), @"\", dateToInsert.Day.ToString("00"), @"\" });

                                                                                            Console.WriteLine("  Copiando el archivo: " + pdf);
                                                                                            File.Copy(pdf, pdf.Replace(@"srd\A importar a la DB\", destinationFolder), true);

                                                                                            if (File.Exists(pdf.Replace(@"srd\A importar a la DB\", destinationFolder)))
                                                                                            {
                                                                                                Console.WriteLine("  Commit en bd...");
                                                                                                transaccionAfip.Commit();

                                                                                                Console.WriteLine("  Borrando pdf...");
                                                                                                File.Delete(pdf);

                                                                                                Console.WriteLine("  Copiando xml...");
                                                                                                while (!File.Exists(pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder)))
                                                                                                    File.Copy(pdf.ToUpper().Replace(".PDF", ".XML"), pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder), true);

                                                                                                if (File.Exists(pdf.ToUpper().Replace(".PDF", ".XML").Replace(@"srd\A importar a la DB".ToUpper(), destinationFolder)))
                                                                                                {
                                                                                                    Console.WriteLine("  Borrando xml...");
                                                                                                    File.Delete(pdf.ToUpper().Replace(".PDF", ".XML"));
                                                                                                }

                                                                                                oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate=7 WHERE IDNS_Documento =" + respuesta;
                                                                                                oraCmd.CommandType = CommandType.Text;
                                                                                                oraCmd.ExecuteNonQuery();
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                Console.WriteLine("  NO SE PUDO MOVER EL ARCHIVO: " + pdf);
                                                                                                emailing.Soporte("SRD SChedule Despacho", "No se pudo copiar el archivo: " + pdf + " Reinforme de afip - intento POR 101");
                                                                                                transaccionAfip.Rollback();
                                                                                            }
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            transaccionAfip.Rollback();
                                                                                            if (errorCode.descError.Contains("Token no vigente o caducado"))
                                                                                                AFIP.renewTicketNow();
                                                                                            else
                                                                                                Informe("SCHEDULE", "AFIP, " + errorCode.codError + "; " + errorCode.descError + "; despacho: " + despacho, caja.ToString(), paginaslote);
                                                                                        }

                                                                                        Console.WriteLine("Procesar proximo?");
                                                                                        //Console.ReadLine();
                                                                                        Console.WriteLine("OK...");

                                                                                    }
                                                                                    catch (Exception ex)
                                                                                    {
                                                                                        try { transaccionAfip.Rollback(); }
                                                                                        catch { }
                                                                                        Console.WriteLine(ex.Message);
                                                                                        Informe("SCHEDULE", "AFIP CATCH, " + ex.Message + "; despacho: " + despacho, caja.ToString(), paginaslote);
                                                                                    }
                                                                                    #endregion
                                                                                }
                                                                                else
                                                                                {
                                                                                    try { transaccionAfip.Rollback(); }
                                                                                    catch { }
                                                                                    if (bytesExistente.Equals(bytespdf.ToString()))
                                                                                        Informe("SCHEDULE", "Existente. La imagen del despacho es idéntica , despacho " + despacho, caja.ToString(), paginaslote);
                                                                                    else
                                                                                        Informe("SCHEDULE", "Existente. Las imágenes son diferentes , despacho " + despacho, caja.ToString(), paginaslote);
                                                                                }
                                                                            }
                                                                            catch (Exception ex)
                                                                            {
                                                                                try { transaccionAfip.Rollback(); }
                                                                                catch { }
                                                                                Console.WriteLine(ex.Message);
                                                                                Informe("SCHEDULE", ex.Message, "", "");
                                                                            }
                                                                        }
                                                                        else
                                                                            Informe("SCHEDULE", "Número de Páginas Incorrecto, despacho " + despacho, caja.ToString(), paginaslote);
                                                                    }
                                                                    else
                                                                        Informe("SCHEDULE", "Cuit Incorrecto o Sin datos de Despachante en BAS, despacho " + despacho, caja.ToString(), paginaslote);
                                                                }
                                                                else
                                                                    Informe("SCHEDULE", "Cuit Incorrecto o Sin datos de Importador/Exportador en BAS, despacho " + despacho, caja.ToString(), paginaslote);
                                                            }
                                                            else
                                                                Informe("SCHEDULE", "Cuit Incorrecto en BAS (Digito Verificador), despacho " + despacho, caja.ToString(), paginaslote);
                                                        }
                                                        else
                                                            Informe("SCHEDULE", "No se informo cantidad de Páginas, despacho " + despacho, caja.ToString(), paginaslote);
                                                    }
                                                    else
                                                        Informe("SCHEDULE", "Cuit Incorrecto o Sin datos de Importador/Exportador en BAS, despacho " + despacho, caja.ToString(), paginaslote);
                                                }
                                                else
                                                {
                                                    Informe("SCHEDULE", "Despacho inexistente BAS, despacho " + despacho, caja.ToString(), paginaslote);
                                                }
                                                #endregion
                                            }
                                            else
                                            {
                                                if (AnexoMngr.Instance().isAnexo(despacho))
                                                {
                                                    #region Anexo
                                                    Anexo anexo = AnexoMngr.Instance().getDataFromXML(pdf);
                                                    
                                                    int resultado;
                                                    if (int.TryParse(anexo.Imageneslote, out resultado))
                                                    {
                                                        oraCmd = new OracleCommand();
                                                        oraCmd.Connection = oraConn;
                                                        OracleTransaction transaccionAfip = oraConn.BeginTransaction(IsolationLevel.ReadCommitted);
                                                        oraCmd.CommandText = "SDOA_P_DOCSA_ADD_ADICIONAL";
                                                        oraCmd.CommandType = CommandType.StoredProcedure;

                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Anio", OracleDbType.Decimal)).Value = "20" + anexo.Anio;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Aduana", OracleDbType.Varchar2, 3)).Value = anexo.Aduana;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoTipo", OracleDbType.Varchar2, 4)).Value = anexo.DocumentoTipo;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoNro", OracleDbType.Varchar2, 6)).Value = anexo.DocumentoNro;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Letra", OracleDbType.Varchar2, 1)).Value = anexo.Letra;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Caja", OracleDbType.Varchar2, 6)).Value = anexo.Caja;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasLote", OracleDbType.Decimal)).Value = anexo.Imageneslote;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_H_Upd", OracleDbType.Date)).Value = dateToInsert;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_BytesPdf", OracleDbType.Decimal)).Value = anexo.BytesPdf.ToString();
                                                        oraCmd.Parameters.Add(new OracleParameter("P_NS_familia", OracleDbType.Decimal)).Value = anexo.Familia.ToString();
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Ticket", OracleDbType.Varchar2, 100)).Value = anexo.Ticket;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_Resultado", OracleDbType.Int32)).Direction = ParameterDirection.Output;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_Secuencia", OracleDbType.Int32)).Direction = ParameterDirection.Output;
                                                        oraCmd.ExecuteNonQuery();

                                                        string respuesta = oraCmd.Parameters["P_Resultado"].Value.ToString();
                                                        string sec = oraCmd.Parameters["P_Secuencia"].Value.ToString();


                                                        if (!respuesta.Equals("0"))
                                                        {
                                                            try
                                                            {
                                                                // AFIP aviso PSAD
                                                                String now = String.Format("{0:s}", DateTime.Now);
                                                                String fechaHora = now + ".796875-03:00";
                                                                String sequence = "1"; sequence = DateTime.Now.Year.ToString() + sequence.PadLeft(20, '0');

                                                                //AFIP.avisoRecepAcept(anexo.DespachoNro, anexo.DespachoData.CuitDespachante, cuitLakaut, anexo.DespachoData.CuitImportadorExportador, "001", fechaHora, anexo.Ticket, "");

                                                                // AFIP aviso DIGI
                                                                CultureInfo ci = CultureInfo.InvariantCulture;
                                                                string hora = DateTime.Now.ToString("dd/MM/yyyy HH:mm:ss", ci);
                                                                hora = hora.Substring(11, 8).Replace(":", ""); // Extraigo.
                                                                hora = hora + respuesta; // Adjunto
                                                                string key = despacho + hora;
                                                                Encryption64 enc = new Encryption64();
                                                                String encriptionResult = enc.Encrypt(key, enc.getDefaultKey());
                                                                String UrlDespacho = "www.sertearsrd.com.ar/srd/getPdf.aspx?qid=" + encriptionResult;

                                                                afipDigit.Familia[] familys = new afipDigit.Familia[1];
                                                                familys[0] = new afipDigit.Familia();
                                                                familys[0].codigo = Convert.ToInt32(anexo.Familia).ToString("00");
                                                                familys[0].cantidad = int.Parse(anexo.Imageneslote);

                                                                // **********************************************************************************************************************************
                                                                // ******** Es importante dejar el archivo tal cual desde el origen ya que luego de informarlo a AFIP no se podra modificar. ********
                                                                // **********************************************************************************************************************************

                                                                string NewName = anexo.DespachoNro + "_" + int.Parse(sec).ToString("00") + ".pdf";
                                                                string pdfNewName = pdf.ToUpper().Replace(pdf.ToUpper().Replace(configuracion.Archivos.ToUpper(), "").Replace("\\", "").ToUpper(), NewName);

                                                                // Cambio el nombre del archivo en el origen
                                                                File.Copy(pdf, pdfNewName,true);

                                                                // Me fijo si el cambio se hiso
                                                                if (File.Exists(pdfNewName))
                                                                {
                                                                    try
                                                                    {
                                                                        // Informo AFIP
                                                                        afipDigit.Recibo errorCode = AFIP.avisoDigitalizacion(anexo.DespachoNro, anexo.DespachoData.CuitDespachante, cuitLakaut, anexo.DespachoData.CuitImportadorExportador, "", "001", UrlDespacho, familys, DateTime.Now, anexo.Ticket, Hashing.Instance.GetAfipHash(pdfNewName), int.Parse(anexo.Imageneslote), "");

                                                                        //Si no hubo error en el informe
                                                                        if (errorCode.codError == 0)
                                                                        {
                                                                            // Borro el viejo
                                                                            File.Delete(pdf);

                                                                            string origen = pdfNewName.ToUpper().Replace("SRD\\A IMPORTAR A LA DB\\" + pdfNewName.ToUpper().Replace(configuracion.Archivos.ToUpper(), "").Replace("\\", "").ToUpper().Replace(".PDF", "") + ".PDF", "");
                                                                            String destinationFolder = @"" + dateToInsert.Year + @"\" + dateToInsert.Month.ToString("00") + @"\" + dateToInsert.Day.ToString("00") + @"\";
                                                                            string destinoFinal = origen + destinationFolder + anexo.DespachoNro + "_" + int.Parse(sec).ToString("00") + ".pdf";

                                                                            // MUEVO EL PDF AL FS
                                                                            File.Copy(pdfNewName, destinoFinal, true);
                                                                            if (File.Exists(destinoFinal))
                                                                            {
                                                                                Console.WriteLine("  Commit en bd...");
                                                                                transaccionAfip.Commit();

                                                                                Console.WriteLine("  Borrando pdf...");
                                                                                File.Delete(pdfNewName);

                                                                                // ***** XML *****
                                                                                Console.WriteLine("  Copiando xml...");
                                                                                while (!File.Exists(destinoFinal.ToUpper().Replace(".PDF", ".XML")))
                                                                                    File.Copy(pdf.ToUpper().Replace(".PDF", ".XML"), destinoFinal.ToUpper().Replace(".PDF", ".XML"), true);

                                                                                if (File.Exists(destinoFinal.ToUpper().Replace(".PDF", ".XML")))
                                                                                {
                                                                                    Console.WriteLine("  Borrando xml...");
                                                                                    File.Delete(pdf.ToUpper().Replace(".PDF", ".XML"));
                                                                                }
                                                                            }
                                                                        }
                                                                        else
                                                                        {
                                                                            // Borro el nuevo creado ya no sirve.
                                                                            File.Delete(pdfNewName);
                                                                            Informe("SCHEDULE", "AFIP, " + errorCode.codError + "; " + errorCode.descError + "; despacho: " + despacho, anexo.Caja.ToString(), anexo.Imageneslote);
                                                                        }
                                                                    }
                                                                    catch (Exception ex)
                                                                    {
                                                                        try { transaccionAfip.Rollback(); }
                                                                        catch { }
                                                                        File.Delete(pdfNewName);
                                                                    }
                                                                }
                                                            }
                                                            catch
                                                            {
                                                                try { transaccionAfip.Rollback(); }
                                                                catch { }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            try { transaccionAfip.Rollback(); }
                                                            catch { }
                                                            Informe("SCHEDULE", "No se encontró el Despacho para el anexo, despacho " + despacho, anexo.Caja.ToString(), anexo.Imageneslote);
                                                        }
                                                    }
                                                    else
                                                        Informe("SCHEDULE", "Nro. de Páginas Incorrecto en Anexo, despacho " + despacho.Substring(1, 16), anexo.Caja.ToString(), anexo.Imageneslote);
                                                    #endregion
                                                }
                                                else if (PersonalMngr.Instance().isPersonal(despacho))
                                                {
                                                    #region Personal
                                                    Personal personal = PersonalMngr.Instance().getDataFromXML(pdf);
                                                    int guiaId = PersonalMngr.Instance().getGuiaID(despacho);
                                                    int resultado;
                                                    if (int.TryParse(personal.Imageneslote, out resultado))
                                                    {
                                                        oraCmd = new OracleCommand();
                                                        oraCmd.Connection = oraConn;
                                                        OracleTransaction transaccionAfip = oraConn.BeginTransaction(IsolationLevel.ReadCommitted);
                                                        oraCmd.CommandText = "SCH_P_DOCSA_ADD";
                                                        oraCmd.CommandType = CommandType.StoredProcedure;

                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Anio", OracleDbType.Decimal)).Value = "20" + personal.Anio;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Aduana", OracleDbType.Varchar2, 3)).Value = personal.Aduana;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoTipo", OracleDbType.Varchar2, 4)).Value = personal.DocumentoTipo;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoNro", OracleDbType.Varchar2, 6)).Value = personal.DocumentoNro;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Letra", OracleDbType.Varchar2, 1)).Value = personal.Letra;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Caja", OracleDbType.Varchar2, 6)).Value = personal.Caja;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasLote", OracleDbType.Decimal)).Value = personal.Imageneslote;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_H_Upd", OracleDbType.Date)).Value = dateToInsert;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_BytesPdf", OracleDbType.Decimal)).Value = personal.BytesPdf.ToString();
                                                        oraCmd.Parameters.Add(new OracleParameter("P_NS_TYPE", OracleDbType.Int32)).Value = 3;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_IDNS_DETALLEGUIA", OracleDbType.Int32)).Value = guiaId;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_Resultado", OracleDbType.Int32)).Direction = ParameterDirection.Output;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_Secuencia", OracleDbType.Int32)).Direction = ParameterDirection.Output;
                                                        oraCmd.Parameters.Add(new OracleParameter("P_ErrGuia", OracleDbType.Int32)).Direction = ParameterDirection.Output;
                                                        oraCmd.ExecuteNonQuery();

                                                        string respuesta = oraCmd.Parameters["P_Resultado"].Value.ToString();
                                                        string sec = oraCmd.Parameters["P_Secuencia"].Value.ToString();
                                                        string errGuia = oraCmd.Parameters["P_ErrGuia"].Value.ToString();

                                                        if (!respuesta.Equals("0"))
                                                        {
                                                            if (!errGuia.Equals("0") && !errGuia.Contains("NULL"))
                                                            {
                                                                try
                                                                {
                                                                    string origen = pdf.ToUpper().Replace("SRD\\A IMPORTAR A LA DB\\" + pdf.Replace(configuracion.Archivos, "").Replace("\\", "").ToUpper().Replace(".PDF", "") + ".PDF", "");
                                                                    String destinationFolder = @"" + dateToInsert.Year + @"\" + dateToInsert.Month.ToString("00") + @"\" + dateToInsert.Day.ToString("00") + @"\";
                                                                    string destinoFinal = origen + destinationFolder + personal.DespachoNro + "_" + sec + ".pdf";

                                                                    File.Copy(pdf, destinoFinal, true);
                                                                    if (File.Exists(destinoFinal))
                                                                    {
                                                                        Console.WriteLine("  Commit en bd...");
                                                                        transaccionAfip.Commit();

                                                                        Console.WriteLine("  Borrando pdf...");
                                                                        File.Delete(pdf);

                                                                        Console.WriteLine("  Copiando xml...");
                                                                        while (!File.Exists(destinoFinal.ToUpper().Replace(".PDF", ".XML")))
                                                                            File.Copy(pdf.ToUpper().Replace(".PDF", ".XML"), destinoFinal.ToUpper().Replace(".PDF", ".XML"), true);

                                                                        if (File.Exists(destinoFinal.ToUpper().Replace(".PDF", ".XML")))
                                                                        {
                                                                            Console.WriteLine("  Borrando xml...");
                                                                            File.Delete(pdf.ToUpper().Replace(".PDF", ".XML"));
                                                                        }
                                                                    }
                                                                }
                                                                catch
                                                                {
                                                                    transaccionAfip.Rollback();
                                                                }
                                                            }
                                                            else
                                                            {
                                                                transaccionAfip.Rollback();
                                                                Informe("SCHEDULE", "No se encontró la guia para el Adicional personal, despacho " + despacho + "; Guia adicional personal: " + guiaId, personal.Caja.ToString(), personal.Imageneslote);
                                                            }
                                                        }
                                                        else
                                                        {
                                                            transaccionAfip.Rollback();
                                                            Informe("SCHEDULE", "No se encontró el Despacho para el Adicional personal, despacho " + despacho + "; Guia adicional personal: " + guiaId, personal.Caja.ToString(), personal.Imageneslote);
                                                        }
                                                    }
                                                    else
                                                        Informe("SCHEDULE", "Nro. de Páginas Incorrecto en Adicional personal, despacho " + despacho.Substring(1, 16) + "; Guia adicional personal: " + guiaId, personal.Caja.ToString(), personal.Imageneslote);
                                                    #endregion
                                                }
                                                if (AnexoMngr.Instance().isRectificativa(despacho))
                                                {
                                                    #region Rectificativa
                                                    Console.WriteLine("Procesando rectificativa... ");

                                                    Rectificativa rectificativa = AnexoMngr.Instance().getDataFromXMLRectificativa(pdf);
                                                    int resultado;
                                                    if (rectificativa != null)
                                                    {
                                                        if (int.TryParse(rectificativa.Imageneslote, out resultado) && !rectificativa.Sigea.Equals(""))
                                                        {
                                                            oraCmd = new OracleCommand();
                                                            oraCmd.Connection = oraConn;
                                                            OracleTransaction transaccionAfip = oraConn.BeginTransaction(IsolationLevel.ReadCommitted);
                                                            oraCmd.CommandText = "SCH_P_DOCSA_RECTIFICATIVA_ADD";
                                                            oraCmd.CommandType = CommandType.StoredProcedure;

                                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_Anio", OracleDbType.Decimal)).Value = "20" + rectificativa.Anio;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_Aduana", OracleDbType.Varchar2, 3)).Value = rectificativa.Aduana;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoTipo", OracleDbType.Varchar2, 4)).Value = rectificativa.DocumentoTipo;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoNro", OracleDbType.Varchar2, 6)).Value = rectificativa.DocumentoNro;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_Letra", OracleDbType.Varchar2, 1)).Value = rectificativa.Letra;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_Caja", OracleDbType.Varchar2, 6)).Value = rectificativa.Caja;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasLote", OracleDbType.Decimal)).Value = rectificativa.Imageneslote;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_H_Upd", OracleDbType.Date)).Value = dateToInsert;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_NC_BytesPdf", OracleDbType.Decimal)).Value = rectificativa.BytesPdf.ToString();
                                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_CODCARP", OracleDbType.Varchar2, 3)).Value = rectificativa.codCarpeta;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_SIGEA", OracleDbType.Varchar2, 100)).Value = rectificativa.Sigea;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_Resultado", OracleDbType.Int32)).Direction = ParameterDirection.Output;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_Secuencia", OracleDbType.Int32)).Direction = ParameterDirection.Output;
                                                            oraCmd.Parameters.Add(new OracleParameter("P_ErrGuia", OracleDbType.Int32)).Direction = ParameterDirection.Output;
                                                            oraCmd.ExecuteNonQuery();

                                                            string respuesta = oraCmd.Parameters["P_Resultado"].Value.ToString();
                                                            string sec = oraCmd.Parameters["P_Secuencia"].Value.ToString();

                                                            if (!respuesta.Equals("0"))
                                                            {
                                                                try
                                                                {
                                                                    //PREPARO DATOS PARA AFIP aviso PSAD
                                                                    String now = String.Format("{0:s}", DateTime.Now);
                                                                    String fechaHora = now + ".796875-03:00";
                                                                    String sequence = "1"; sequence = DateTime.Now.Year.ToString() + sequence.PadLeft(20, '0');

                                                                    //PREPARO DATOS PARA AFIP aviso DIGI
                                                                    CultureInfo ci = CultureInfo.InvariantCulture;
                                                                    string hora = DateTime.Now.ToString("dd/MM/yyyy HH:mm:ss", ci);
                                                                    hora = hora.Substring(11, 8).Replace(":", ""); // Extraigo.
                                                                    hora = hora + respuesta; // Adjunto
                                                                    string key = despacho + hora;
                                                                    Encryption64 enc = new Encryption64();
                                                                    String encriptionResult = enc.Encrypt(key, enc.getDefaultKey());
                                                                    String UrlDespacho = "www.sertearsrd.com.ar/srd/getPdf.aspx?qid=" + encriptionResult;

                                                                    AFIP.avisoRecepAcept(rectificativa.DespachoNro, rectificativa.DespachoData.CuitDespachante, cuitLakaut, rectificativa.DespachoData.CuitImportadorExportador, rectificativa.codCarpeta, DateTime.Now.ToString(), rectificativa.Ticket, rectificativa.Sigea);

                                                                    // **********************************************************************************************************************************
                                                                    // ******** Es importante dejar el archivo tal cual desde el origen ya que luego de informarlo a AFIP no se podra modificar. ********
                                                                    // **********************************************************************************************************************************

                                                                    string NewName = rectificativa.DespachoNro + "_" + int.Parse(sec).ToString("00") + ".pdf";
                                                                    string pdfNewName = pdf.ToUpper().Replace(pdf.ToUpper().Replace(configuracion.Archivos.ToUpper(), "").Replace("\\", "").ToUpper(), NewName);

                                                                    // Cambio el nombre del archivo en el origen
                                                                    File.Copy(pdf, pdfNewName, true);

                                                                    // Me fijo si el cambio se hiso
                                                                    if (File.Exists(pdfNewName))
                                                                    {

                                                                        afipDigit.Recibo errorCode = null;

                                                                        if (pdf.Contains("$004$")) // Solo en caso de Post-Libramiento no se envian las familias del documento
                                                                            errorCode = AFIP.avisoDigitalizacion(rectificativa.DespachoNro, rectificativa.DespachoData.CuitDespachante, cuitLakaut, rectificativa.DespachoData.CuitImportadorExportador, "", rectificativa.codCarpeta, UrlDespacho, null, DateTime.Now, null, Hashing.Instance.GetAfipHash(pdfNewName), int.Parse(rectificativa.Imageneslote), rectificativa.Sigea);
                                                                        else
                                                                            errorCode = AFIP.avisoDigitalizacion(rectificativa.DespachoNro, rectificativa.DespachoData.CuitDespachante, cuitLakaut, rectificativa.DespachoData.CuitImportadorExportador, "", rectificativa.codCarpeta, UrlDespacho, getFamilyNumbers(pdfNewName), DateTime.Now, null, Hashing.Instance.GetAfipHash(pdfNewName), int.Parse(rectificativa.Imageneslote), rectificativa.Sigea);

                                                                        if (errorCode.codError == 0 || errorCode.descError.Contains("DIGI"))
                                                                        {
                                                                            File.Delete(pdf);

                                                                            string origen = pdfNewName.ToUpper().Replace("SRD\\A IMPORTAR A LA DB\\" + pdfNewName.ToUpper().Replace(configuracion.Archivos.ToUpper(), "").Replace("\\", "").ToUpper().Replace(".PDF", "") + ".PDF", "");
                                                                            string destinationFolder = @"" + dateToInsert.Year + @"\" + dateToInsert.Month.ToString("00") + @"\" + dateToInsert.Day.ToString("00") + @"\";
                                                                            string destinoFinal = origen + destinationFolder + rectificativa.DespachoNro + "_" + int.Parse(sec).ToString("00") + ".pdf";
                                                                            //File.Copy(pdf, destinoFinal, true);
                                                                            File.Copy(pdfNewName, destinoFinal, true);


                                                                            if (File.Exists(destinoFinal))
                                                                            {
                                                                                Console.WriteLine("  Commit en bd...");
                                                                                transaccionAfip.Commit();

                                                                                Console.WriteLine("  Borrando pdf...");
                                                                                File.Delete(pdfNewName);

                                                                                Console.WriteLine("  Copiando xml...");
                                                                                while (!File.Exists(destinoFinal.ToUpper().Replace(".PDF", ".XML")))
                                                                                    File.Copy(pdf.ToUpper().Replace(".PDF", ".XML"), destinoFinal.ToUpper().Replace(".PDF", ".XML"), true);

                                                                                if (File.Exists(destinoFinal.ToUpper().Replace(".PDF", ".XML")))
                                                                                {
                                                                                    Console.WriteLine("  Borrando xml...");
                                                                                    File.Delete(pdf.ToUpper().Replace(".PDF", ".XML"));
                                                                                }
                                                                            }
                                                                        }
                                                                        else
                                                                        {

                                                                            try { File.Delete(pdfNewName); }
                                                                            catch { }

                                                                            try { transaccionAfip.Rollback(); }
                                                                            catch { }
                                                                        
                                                                            Informe("SCHEDULE", "AFIP, " + errorCode.codError + "; " + errorCode.descError + "; despacho: " + despacho, rectificativa.Caja.ToString(), rectificativa.Imageneslote);
                                                                        }
                                                                    }
                                                                }
                                                                catch(Exception ex)
                                                                {
                                                                    try { transaccionAfip.Rollback(); }
                                                                    catch { }
                                                                }
                                                            }
                                                            else
                                                            {
                                                                try { transaccionAfip.Rollback(); }
                                                                catch { }
                                                                Informe("SCHEDULE", "No se encontró el Despacho para la rectificativa, despacho " + despacho, rectificativa.Caja.ToString(), rectificativa.Imageneslote);
                                                            }
                                                        }
                                                        else
                                                            Informe("SCHEDULE", "Nro. de Páginas Incorrecto en la rectificativa, despacho " + despacho.Substring(1, 16), rectificativa.Caja.ToString(), rectificativa.Imageneslote);
                                                    }
                                                    else
                                                        Informe("SCHEDULE", "No se encontro la guia para la rectificativa, despacho " + despacho.Substring(1, 16), "", "");
                                                    #endregion
                                                }
                                            }
                                        }
                                        else
                                            Informe("SCHEDULE", "Nro. de Despacho o Adicional personal Incorrecto (DV), despacho " + despacho, "", "");
                                    }
                                }
                                catch (Exception ex)
                                {
                                    Informe("SCHEDULE", ex.Message, "", "");
                                    emailing.Soporte("SRD SChedule Despacho", ex);
                                    if (sqlConn.State == ConnectionState.Closed)
                                    {
                                        sqlConn.Open();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                
                if (sqlConn.State == ConnectionState.Closed)
                {
                    sqlConn.Open();
                }
                Informe("SCHEDULE", ex.Message, "", "");
                emailing.Soporte("SRD SChedule Despacho", ex);
            }
            finally
            {
                if ((sqlConn != null) && (sqlConn.State != ConnectionState.Closed)) sqlConn.Close();
                sqlConn = null;

                if ((oraConn != null) && (oraConn.State != ConnectionState.Closed)) oraConn.Close();
                oraConn = null;
            }
        }


        private bool setupPerformanceCounter()
        {
            if (countersEnable)
            {
                // Set up the performance counter(s) if they don't already exist
                if (!PerformanceCounterCategory.Exists("SRDTask"))
                {
                    // Create the collection container
                    CounterCreationDataCollection counters = new
                       CounterCreationDataCollection();

                    // Create counter #1 and add it to the collection
                    CounterCreationData counterPdfMoved = new CounterCreationData();
                    counterPdfMoved.CounterName = "Total PDF/FS";
                    counterPdfMoved.CounterHelp = "Total de despachos satisfactorios movidos a FS.";
                    counterPdfMoved.CounterType = PerformanceCounterType.NumberOfItems32;
                    counters.Add(counterPdfMoved);

                    // Create counter #2 and add it to the collection
                    CounterCreationData counterCallsAfip = new CounterCreationData();
                    counterCallsAfip.CounterName = "Total Afip Calls";
                    counterCallsAfip.CounterHelp = "Total de llamadas servicio de informe Afip.";
                    counterCallsAfip.CounterType = PerformanceCounterType.NumberOfItems32;
                    counters.Add(counterCallsAfip);

                    // Create the category and all of the counters.
                    PerformanceCounterCategory.Create("SRDTask",
                       "Contadores de rendimiento proceso SRDTask",
                       counters);
                }
            }
            return true;
        }

        private bool checkTimes(String pdf)
        {
            if (dontCheckTimes)
                return true;
            {
                if ((File.GetCreationTime(pdf).AddMinutes(double.Parse(configuracion.LimiteMinutosEspera)) < DateTime.Now) && (File.GetCreationTime(pdf) > DateTime.Now.AddHours(-24)))
                    return true;
                else
                    return false;
            }
        }

        public void Arreglar()
        {
            string ruta = (@"\\clustersrdfs.lacaut.com.ar\srd\A importar a la DB").ToUpper();
            string newDir = "MOVED";

            ArrayList correct = loadVector();

            foreach (string pdf in correct)
            {
                try
                {
                    string archivo = ruta + @"\" + pdf;
                    string nuevaRuta = ruta + @"\" + newDir + @"\" + pdf;

                    if (File.Exists(archivo))
                    {
                        File.Move(archivo, nuevaRuta);
                        File.Move(archivo.ToUpper().Replace(".PDF", ".XML"), nuevaRuta.ToUpper().Replace(".PDF", ".XML"));
                    }
                }
                catch(Exception ex)
                {
                    string moved = ex.Message;
                }
            }

            return;
        }

        /// <summary>
        /// Depura los PDF importados a la BD.
        /// </summary>
        private void Depurar()
        {
            try
            {
                string ruta = configuracion.Archivos.Replace("A importar a la DB", "Importados a la DB");
                if (Directory.Exists(ruta))
                {
                    string[] files = Directory.GetFiles(ruta);
                    if (files.Length > 0)
                    {
                        foreach (string file in files)
                        {
                            if (File.GetCreationTime(file).AddDays(double.Parse(configuracion.DiasABorrarImportados)) < DateTime.Now) File.Delete(file);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Informe("SCHEDULE", ex.Message + ", No se pudo Depurar", "", "");
                emailing.Soporte("SRD SChedule Depurar", ex);
            }
            finally
            {
            }
        }

        private static int CalcularDigitoCuit(string cuit)
        {
            int[] mult = new[] { 5, 4, 3, 2, 7, 6, 5, 4, 3, 2 };
            char[] nums = cuit.ToCharArray();
            int total = 0;
            for (int i = 0; i < mult.Length; i++) total += int.Parse(nums[i].ToString()) * mult[i];
            var resto = total % 11;
            return resto == 0 ? 0 : resto == 1 ? 9 : 11 - resto;
        }

        private static bool ValidaCuit(string cuit)
        {
            if ((cuit == null) || (cuit.Length != 11)) return false;
            int calculado = CalcularDigitoCuit(cuit);
            int digito = int.Parse(cuit.Substring(10));
            return calculado == digito;
        }

        private static bool ValidarDespacho(string despacho)
        {
            try
            {
                if (despacho.Length == 16)
                {
                    int anioaduana = int.Parse(despacho.Substring(0, 5));
                    return true;
                }
                else
                    return false;
            }
            catch
            {
                return false;
            }
        }

        private static bool ValidarAnexo(string despacho)
        {
            try
            {
                if ((despacho.Length == 17) && (despacho.ToUpper().StartsWith("A") || despacho.ToUpper().StartsWith("B")))
                {
                    int anioaduana = int.Parse(despacho.Substring(1, 5));
                    return true;
                }
                else
                    return false;
            }
            catch
            {
                return false;
            }
        }

        private static bool isPedido(string despacho)
        {
            try
            {
                if (despacho.ToUpper().StartsWith("B"))
                {
                    return true;
                }
                else
                    return false;
            }
            catch
            {
                return false;
            }
        }

        private static bool VerificadorDespacho(string despacho)
        {
            try
            {
                if ((despacho.Length == 17) && (despacho.ToUpper().StartsWith("A") || despacho.ToUpper().StartsWith("B")) ) despacho = despacho.Substring(1, 16);
                if (despacho.IndexOf("$") > 0) despacho = despacho.Substring(0, 16);
                if (despacho != null && despacho.Length >= 15)
                {
                    int acumulador = 0;
                    string res = "";

                    if (despacho.Substring(5, 4).ToUpper() == "MANE")
                        res = despacho.Substring(0, 2) + despacho.Substring(2, 3) + "MANI" + despacho.Substring(9, 6);
                    else
                        res = despacho.Substring(0, 15);

                    Byte[] asc = System.Text.ASCIIEncoding.ASCII.GetBytes(res);
                    foreach (Byte BYTE in asc) acumulador += (int)BYTE;

                    acumulador = (acumulador % 23) + 65;

                    if (despacho.Substring(5, 4).ToUpper() == "MANE")
                        if (acumulador + 1 == 91)
                            acumulador = 65;

                    switch (Convert.ToChar(acumulador).ToString().ToUpper())
                    {
                        case "I":
                            return despacho.Substring(15, 1).ToUpper().Equals("X");
                        case "O":
                            return despacho.Substring(15, 1).ToUpper().Equals("Y");
                        case "Q":
                            return despacho.Substring(15, 1).ToUpper().Equals("Z");
                        default:
                            return Convert.ToChar(acumulador).ToString().ToUpper().Equals(despacho.Substring(15, 1).ToUpper());
                    }
                }
                else
                    return false;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        private bool ValidarDespachoAfip(string cuitcliente, string cuitdespachante, string despacho)
        {
            OracleConnection oraConn = null;
            OracleCommand oraCmd;
            string cuitdespachanteafip = "";
            string cuitimportadorexportadorafip = "";
            string idsecuencia1 = "";
            string idsecuencia2 = "";
            string idsecuencia3 = "";
            string idsecuencia4 = "";
            string idsecuencia5 = "";
            bool respuesta = false;
            try
            {
                if ((despacho.Substring(2, 3) == "001") || (despacho.Substring(2, 3) == "073"))
                {
                    oraConn = new OracleConnection(configuracion.CSSieg);
                    oraConn.Open();

                    oraCmd = new OracleCommand();
                    oraCmd.Connection = oraConn;
                    oraCmd.CommandText = "SELECT * FROM WIT_SLDETALLADACARATULAS WHERE DS_IDDESTINACION='" + despacho + "'";
                    oraCmd.CommandType = CommandType.Text;
                    OracleDataReader odr = oraCmd.ExecuteReader();
                    if (odr.Read())
                    {
                        cuitdespachanteafip = (odr.IsDBNull(odr.GetOrdinal("DS_CUITDESPACHANTE"))) ? "" : odr.GetOracleString(odr.GetOrdinal("DS_CUITDESPACHANTE")).ToString();
                        cuitimportadorexportadorafip = (odr.IsDBNull(odr.GetOrdinal("DS_CUITIMPORTADOREXPORTADOR"))) ? "" : odr.GetOracleString(odr.GetOrdinal("DS_CUITIMPORTADOREXPORTADOR")).ToString();
                    }
                    odr.Close();
                    odr = null;

                    if ((cuitdespachanteafip == "") || (cuitimportadorexportadorafip == ""))
                    {
                        oraCmd = new OracleCommand();
                        oraCmd.Connection = oraConn;
                        oraCmd.CommandText = "SELECT WIT_COMMON_SEQUENCE.Nextval AS Next FROM DUAL";
                        oraCmd.CommandType = CommandType.Text;
                        odr = oraCmd.ExecuteReader();
                        if (odr.Read()) idsecuencia1 = (odr.IsDBNull(odr.GetOrdinal("Next"))) ? "" : odr.GetOracleDecimal(odr.GetOrdinal("Next")).ToString();
                        odr = oraCmd.ExecuteReader();
                        if (odr.Read()) idsecuencia2 = (odr.IsDBNull(odr.GetOrdinal("Next"))) ? "" : odr.GetOracleDecimal(odr.GetOrdinal("Next")).ToString();
                        odr = oraCmd.ExecuteReader();
                        if (odr.Read()) idsecuencia3 = (odr.IsDBNull(odr.GetOrdinal("Next"))) ? "" : odr.GetOracleDecimal(odr.GetOrdinal("Next")).ToString();
                        odr = oraCmd.ExecuteReader();
                        if (odr.Read()) idsecuencia4 = (odr.IsDBNull(odr.GetOrdinal("Next"))) ? "" : odr.GetOracleDecimal(odr.GetOrdinal("Next")).ToString();
                        odr = oraCmd.ExecuteReader();
                        if (odr.Read()) idsecuencia5 = (odr.IsDBNull(odr.GetOrdinal("Next"))) ? "" : odr.GetOracleDecimal(odr.GetOrdinal("Next")).ToString();
                        odr.Close();
                        odr = null;

                        if ((idsecuencia1 != "") && (idsecuencia2 != "") && (idsecuencia3 != "") && (idsecuencia4 != "") && (idsecuencia5 != ""))
                        {
                            oraCmd = new OracleCommand();
                            oraCmd.Connection = oraConn;
                            oraCmd.CommandText = "INSERT INTO WIT_PETICIONES (MN_ESTADO, INC_PETICION, NN_CODIGOERROR, WS20_INC_SERVICIO, WM_IDN_MODULO) VALUES (0," + idsecuencia1 + ",0,8,1)";
                            oraCmd.CommandType = CommandType.Text;
                            oraCmd.ExecuteNonQuery();
                            oraCmd.CommandText = "INSERT INTO WIT_PARAMETROS_PETICIONES (ATTR_VALUE, INC_PARAMETRO_PETICION, ATTR_KEY, WP_INC_PETICION) VALUES ('" + despacho + "'," + idsecuencia2 + ",'ID_DESTINACION'," + idsecuencia1 + ")";
                            oraCmd.ExecuteNonQuery();
                            oraCmd.CommandText = "INSERT INTO WIT_PARAMETROS_PETICIONES (ATTR_VALUE, INC_PARAMETRO_PETICION, ATTR_KEY, WP_INC_PETICION) VALUES ('" + despacho.Substring(2, 3) + "'," + idsecuencia3 + ",'CODIGO_DE_ADUANA'," + idsecuencia1 + ")";
                            oraCmd.ExecuteNonQuery();
                            oraCmd.CommandText = "INSERT INTO WIT_PARAMETROS_PETICIONES (ATTR_VALUE, INC_PARAMETRO_PETICION, ATTR_KEY, WP_INC_PETICION) VALUES ('EXTE'," + idsecuencia4 + ",'ROL_DE_USUARIO'," + idsecuencia1 + ")";
                            oraCmd.ExecuteNonQuery();
                            oraCmd.CommandText = "INSERT INTO WIT_PARAMETROS_PETICIONES (ATTR_VALUE, INC_PARAMETRO_PETICION, ATTR_KEY, WP_INC_PETICION) VALUES ('DEPO'," + idsecuencia5 + ",'TIPO_DE_AGENTE'," + idsecuencia1 + ")";
                            oraCmd.ExecuteNonQuery();

                            espera = false;

                            System.Threading.Thread.Sleep(1000);
                            oraCmd = new OracleCommand();
                            oraCmd.Connection = oraConn;
                            oraCmd.CommandText = "SELECT * FROM WIT_PETICIONES WHERE INC_PETICION=" + idsecuencia1 + " And MN_Estado=1";
                            oraCmd.CommandType = CommandType.Text;
                            odr = oraCmd.ExecuteReader();
                            if (odr.Read())
                            {
                                string codigoerror = (odr.IsDBNull(odr.GetOrdinal("NN_CodigoError"))) ? "" : odr.GetOracleDecimal(odr.GetOrdinal("NN_CodigoError")).ToString();
                                if (codigoerror == "" || codigoerror == "-1" || codigoerror == "-1000")
                                {
                                    esperas = esperas + 1;
                                    espera = true;
                                }
                                else
                                {
                                    esperas = 0;
                                }
                            }
                            odr.Close();
                            odr = null;

                            if (!espera)
                            {
                                oraCmd = new OracleCommand();
                                oraCmd.Connection = oraConn;
                                oraCmd.CommandText = "SELECT DS_CuitDespachante,DS_CuitImportadorExportador FROM WIT_SLDETALLADACARATULAS WHERE DS_IDDESTINACION='" + despacho + "' AND INC_Peticion=" + idsecuencia1;
                                oraCmd.CommandType = CommandType.Text;
                                odr = oraCmd.ExecuteReader();
                                if (odr.Read())
                                {
                                    cuitdespachanteafip = (odr.IsDBNull(odr.GetOrdinal("DS_CUITDESPACHANTE"))) ? "" : odr.GetOracleString(odr.GetOrdinal("DS_CUITDESPACHANTE")).ToString();
                                    cuitimportadorexportadorafip = (odr.IsDBNull(odr.GetOrdinal("DS_CUITIMPORTADOREXPORTADOR"))) ? "" : odr.GetOracleString(odr.GetOrdinal("DS_CUITIMPORTADOREXPORTADOR")).ToString();
                                    if ((cuitdespachante == cuitdespachanteafip) && (cuitcliente == cuitimportadorexportadorafip)) respuesta = true;
                                }
                                odr.Close();
                                odr = null;
                            }
                        }
                    }
                    else
                    {
                        if ((cuitdespachante == cuitdespachanteafip) && (cuitcliente == cuitimportadorexportadorafip))
                            respuesta = true;
                    }
                    return respuesta;
                }
                else
                    return true;
            }
            catch (Exception ex)
            {
                try
                {
                    System.Net.Mail.MailMessage correo = new System.Net.Mail.MailMessage();
                    correo.From = new System.Net.Mail.MailAddress("webmaster@tca.aero");
                    correo.To.Add(configuracion.MailSoporte);
                    correo.Subject = "SRD SChedule ValidarCuitAfip";
                    correo.Body = ex.Message + "<br />" + ex.ToString();
                    correo.IsBodyHtml = true;
                    correo.Priority = System.Net.Mail.MailPriority.Normal;
                    System.Net.Mail.SmtpClient smtp = new System.Net.Mail.SmtpClient();
                    smtp.Host = configuracion.Mail;
                    smtp.Credentials = new System.Net.NetworkCredential(configuracion.MailUser, configuracion.MailPwd);
                    smtp.Send(correo);
                }
                catch { }
                return false;
            }
            finally
            {
                if ((oraConn != null) && (oraConn.State != ConnectionState.Closed)) oraConn.Close();
                oraConn = null;
            }
        }

        private static string Clave(int longitud)
        {
            Random random = new Random();
            string salida = "";
            string[] charArray = new string[36] {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
												  "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
												  "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
												  "U", "V", "W", "X", "Y", "Z"};
            while (salida.Length < longitud)
            { salida = salida + charArray[(int)(36 * random.NextDouble())].ToString(); }
            return salida;
        }

        #endregion

        #region Tools

        private void Informe(string asunto, string body, string caja, string imageneslote)
        {
            OracleConnection oraConn2 = null;
            try
            {
                oraConn2 = new OracleConnection(Configuracion.Default.CS1);
                oraConn2.Open();

                OracleCommand oraCmd2 = new OracleCommand();
                oraCmd2.Connection = oraConn2;
                oraCmd2.CommandText = "WLOG_P_LOGS_ADD";
                oraCmd2.CommandType = CommandType.StoredProcedure;

                oraCmd2.Parameters.Add(new OracleParameter("P_SD_Asunto", OracleDbType.Varchar2, 100)).Value = asunto;
                oraCmd2.Parameters.Add(new OracleParameter("P_SD_Texto", OracleDbType.Varchar2, 2000)).Value = body;
                oraCmd2.Parameters.Add(new OracleParameter("P_SD_Caja", OracleDbType.Varchar2, 6)).Value = caja;
                oraCmd2.Parameters.Add(new OracleParameter("P_NC_ImagenesLote", OracleDbType.Decimal)).Value = (imageneslote == "") ? (object)DBNull.Value : imageneslote;
                oraCmd2.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                emailing.Soporte("SRD SChedule Informe", ex);
            }
            finally
            {
                if ((oraConn2 != null) && (oraConn2.State != ConnectionState.Closed)) oraConn2.Close();
                oraConn2 = null;
            }
        }

        private bool tryParse(string _paginas)
        {
            try
            {
                int pag = int.Parse(_paginas);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        public afipDigit.Familia[] getFamilyNumbers(String pdfFile)
        {
            string page = null;
            string text = "";
            string textant = "";
            
            using (MemoryStream ms = new MemoryStream())
            {
                RandomAccessFileOrArray rafA = new RandomAccessFileOrArray(pdfFile);
                
                PdfReader pdfr = new PdfReader(rafA, null);

                afipDigit.Familia[] familys = new aSchedule.afipDigit.Familia[5];
                familys[0] = new afipDigit.Familia();
                familys[1] = new afipDigit.Familia();
                familys[2] = new afipDigit.Familia();
                familys[3] = new afipDigit.Familia();
                familys[4] = new afipDigit.Familia();

                //Start - Agregado segun nueva especific las familias, siempre se pasan.
                familys[0].cantidad = 0;
                familys[0].codigo = "01";
                familys[1].cantidad = 0;
                familys[1].codigo = "02";
                familys[2].cantidad = 0;
                familys[2].codigo = "03";
                familys[3].cantidad = 0;
                familys[3].codigo = "04";
                familys[4].cantidad = 0;
                familys[4].codigo = "05";

                if(SimpleBookmark.GetBookmark(pdfr)!=null)
                {
                    SimpleBookmark.ExportToXML(SimpleBookmark.GetBookmark(pdfr), ms, "UTF-8", false);
                    
                    rafA.Close();
                    pdfr.Close();
                    rafA = null;
                    pdfr = null;

                    ms.Position = 0;
                    using (XmlReader xr = XmlReader.Create(ms))
                    {
                        xr.MoveToContent();

                        Regex re = new Regex(@"^\d+");
                        while (xr.Read())
                        {
                            if (xr.NodeType == XmlNodeType.Element && xr.Name == "Title" && xr.IsStartElement())
                            {
                                page = re.Match(xr.GetAttribute("Page")).Captures[0].Value;
                                xr.Read();
                                if (xr.NodeType == XmlNodeType.Text)
                                {
                                    text = xr.Value.Replace(" ", "").Trim();
                                }
                            }
                            if (!text.Equals("") && text.IndexOf(".") > 0)
                            {
                                string textE = text.Substring(text.IndexOf(".") + 1, 1);
                                if (!textE.Equals(textant))
                                {
                                    familys[Convert.ToInt32(textE) - 1].codigo = "0" + textE;
                                    familys[Convert.ToInt32(textE) - 1].cantidad = Convert.ToInt32(text.Substring(0, text.IndexOf(".")));
                                    textant = textE;
                                }
                                else
                                {
                                    familys[Convert.ToInt32(textE) - 1].cantidad = Convert.ToInt32(text.Substring(0, text.IndexOf(".")));
                                }
                                text = "";
                            }
                        }

                        // Esto se agrega para entregar solo las familias que estan cargadas, las que no, se eliminan:
                        // Si no se usa, borrar:
                        //ArrayList familias = new ArrayList();
                        //foreach (afipDigit.Familia item in familys)
                        //{
                        //    if (item.cantidad != 0)
                        //        familias.Add(item);
                        //}

                        //afipDigit.Familia[] familysAux = new afipDigit.Familia[familias.Count];
                        //int i = 0;
                        //foreach (afipDigit.Familia item in familias)
                        //{
                        //    familysAux[i] = item;
                        //    i++;
                        //}
                        ms.Close();
                    }
                }
                return familys;
            }
        }

        private Documento[] getsolobianData(string despacho)
        {
            string password = "";
            System.Security.Cryptography.MD5CryptoServiceProvider x = new System.Security.Cryptography.MD5CryptoServiceProvider();
            byte[] data = System.Text.Encoding.ASCII.GetBytes(despacho + "workout");
            data = x.ComputeHash(data);
            for (int i = 0; i < data.Length; i++) password += data[i].ToString("x2").ToLower();

            lakaut lakaut = new lakaut();
            Credenciales credenciales = new Credenciales();
            credenciales.operacion = despacho;
            credenciales.password = password;
            return lakaut.get_oper(credenciales);
        }

        private string getsolobianTicket(string despacho, int secuencia)
        {
            int indiceStart;
            int indiceEnd;
            string ticket = "0";
            string respuestaTickets;
            string trueTicket;
            string password = "";
            string rsTicket = "0";


            System.Security.Cryptography.MD5CryptoServiceProvider x = new System.Security.Cryptography.MD5CryptoServiceProvider();
            byte[] data = System.Text.Encoding.ASCII.GetBytes(despacho + "workout");
            data = x.ComputeHash(data);
            for (int i = 0; i < data.Length; i++) password += data[i].ToString("x2").ToLower();

            ar.com.lakaut.gestion.lakaut lak = new ar.com.lakaut.gestion.lakaut();
            ar.com.lakaut.gestion.Credenciales cred = new ar.com.lakaut.gestion.Credenciales();
            cred.operacion = despacho;
            cred.password = password;
            ar.com.lakaut.gestion.Ticket[] doc = lak.get_ticket(cred);

            respuestaTickets = doc[0].ws_tickets;
            
            if (doc[0].ercode.Equals("0"))
            {
                try
                {
                    // Esto es inviable: Corto el string que envian
                    indiceStart = respuestaTickets.IndexOf(secuencia.ToString() + "_");
                    respuestaTickets = respuestaTickets.Substring(indiceStart, respuestaTickets.Length - indiceStart);
                    indiceStart = respuestaTickets.IndexOf(secuencia.ToString() + "_");
                    indiceEnd = respuestaTickets.IndexOf(";");
                    trueTicket = respuestaTickets.Substring(indiceStart, indiceEnd);
                    // Una vez que solo obtengo los datos que me importan 
                    // parseo el string resultante
                    indiceStart = trueTicket.IndexOf(secuencia.ToString() + "_") + 2;
                    indiceEnd = trueTicket.Length - indiceStart;
                    // en fin.. si todo esta bien, obtengo el ticket.
                    ticket = trueTicket.Substring(indiceStart, indiceEnd); 
                }
                catch 
                {
                    ticket = "0";
                }
                rsTicket = ticket.ToString();
            }
            rsTicket = ticket.ToString();

            return rsTicket;
        }

        #endregion

        #region Afip

        private void adviceNewsDocument()
        {
            createTextFile("LogAfipThread");

            writeTextFile("Iniciando ...");

            oraConn = new OracleConnection(Configuracion.Default.CS1);
            oraConn.Open();
            //aSchedule.Logic.WS.afip AFIP = new aSchedule.Logic.WS.afip();
            writeTextFile("Abriendo Base...");
            TrackingMngr tracking = new TrackingMngr();
            try
            {
                writeTextFile("Comenzando consulta de no informados: ");

                oraCmd = new OracleCommand();
                oraCmd.Connection = oraConn;
                oraCmd.CommandText = "SDOC_P_AFIP_ADVICEDOCUMENT";
                oraCmd.CommandType = CommandType.StoredProcedure;
                oraCmd.Parameters.Add(new OracleParameter("O_Cursor", OracleDbType.RefCursor)).Direction = ParameterDirection.Output;
                OracleDataReader odr = oraCmd.ExecuteReader();

                writeTextFile("Ejecutado! Inciciando loop de informe:");
                try
                {
                    while (odr.Read())
                    {
                        try
                        {
                            String desp = odr.GetOracleValue(odr.GetOrdinal("SD_Anio")).ToString().Substring(2, 2) + odr.GetString(odr.GetOrdinal("SD_Aduana")).ToString() + odr.GetString(odr.GetOrdinal("SD_DocumentoTipo")).ToString() + odr.GetString(odr.GetOrdinal("SD_DocumentoNro")).ToString() + odr.GetString(odr.GetOrdinal("SD_Letra")).ToString();

                            writeTextFile("Informando despacho: " + desp);

                            String id = (odr.IsDBNull(odr.GetOrdinal("IDNS_Documento"))) ? "0" : odr.GetOracleValue(odr.GetOrdinal("IDNS_Documento")).ToString();
                            int Anio = (odr.IsDBNull(odr.GetOrdinal("SD_Anio"))) ? 0 : int.Parse(odr.GetOracleValue(odr.GetOrdinal("SD_Anio")).ToString());
                            String Aduana = (odr.IsDBNull(odr.GetOrdinal("SD_Aduana"))) ? "" : odr.GetString(odr.GetOrdinal("SD_Aduana")).ToString();
                            String DocumentoTipo = (odr.IsDBNull(odr.GetOrdinal("SD_DocumentoTipo"))) ? "" : odr.GetString(odr.GetOrdinal("SD_DocumentoTipo")).ToString();
                            String DocumentoNro = (odr.IsDBNull(odr.GetOrdinal("SD_DocumentoNro"))) ? "" : odr.GetString(odr.GetOrdinal("SD_DocumentoNro")).ToString();
                            String Letra = (odr.IsDBNull(odr.GetOrdinal("SD_Letra"))) ? "" : odr.GetString(odr.GetOrdinal("SD_Letra")).ToString();
                            String Caja = (odr.IsDBNull(odr.GetOrdinal("SD_Caja"))) ? "" : odr.GetString(odr.GetOrdinal("SD_Caja")).ToString();
                            int Paginas = (odr.IsDBNull(odr.GetOrdinal("NC_Paginas"))) ? 0 : int.Parse(odr.GetInt16(odr.GetOrdinal("NC_Paginas")).ToString());
                            String CuitDespachante = (odr.IsDBNull(odr.GetOrdinal("SD_CuitDespachante"))) ? "" : odr.GetString(odr.GetOrdinal("SD_CuitDespachante")).ToString();
                            String Despachante = (odr.IsDBNull(odr.GetOrdinal("SD_Despachante"))) ? "" : odr.GetString(odr.GetOrdinal("SD_Despachante")).ToString();
                            String CuitImportadorExportador = (odr.IsDBNull(odr.GetOrdinal("SD_CuitImportadorExportador"))) ? "" : odr.GetString(odr.GetOrdinal("SD_CuitImportadorExportador")).ToString();
                            String ImportadorExportador = (odr.IsDBNull(odr.GetOrdinal("SD_ImportadorExportador"))) ? "" : odr.GetString(odr.GetOrdinal("SD_ImportadorExportador")).ToString();
                            DateTime Alta = (odr.IsDBNull(odr.GetOrdinal("H_Alta"))) ? DateTime.Now : odr.GetDateTime(odr.GetOrdinal("H_Alta"));
                            DateTime Update = (odr.IsDBNull(odr.GetOrdinal("H_Upd"))) ? DateTime.Now : odr.GetDateTime(odr.GetOrdinal("H_Upd"));
                            String sigea = "";
                            String now = String.Format("{0:s}", DateTime.Now);
                            String fechaHora = now + ".796875-03:00";

                            // Armo la fecha del directorio donde se encuentra el despacho.
                            string day = Update.Day.ToString("00");
                            string month = Update.Month.ToString("00");
                            string year = Update.Year.ToString();
                            
                            String pdf =  configuracion.FileSistem + @"\" + year + @"\" + month + @"\" + day + @"\" + desp + ".PDF";

                            OracleTransaction transaccionDigitalizacion = null;

                            // para testing: 
                            // if (id.Equals("252394"))
                            if (File.Exists(pdf))
                            {
                                string resp = "";
                                try
                                {
                                    // Informo recepcion // Borrar!
                                    resp = AFIP.avisoRecepAcept(desp, CuitDespachante, "30710964277", CuitImportadorExportador, "000", fechaHora, "","");

                                    // Inicio transaccion digitalizacion:
                                    transaccionDigitalizacion = oraConn.BeginTransaction(IsolationLevel.ReadCommitted);
                                    oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate = 2, H_AFIP_DIGITALIZACION=TO_DATE('" + DateTime.Now.ToString("dd/MM/yyyy") + "','dd/MM/yyyy') WHERE IDNS_Documento =" + id;
                                    oraCmd.CommandType = CommandType.Text;
                                    oraCmd.ExecuteNonQuery();

                                    // Encripto la url a informar:
                                    CultureInfo ci = CultureInfo.InvariantCulture;
                                    // Hora / Formato Afip:
                                    string hora = Alta.ToString("dd/MM/yyyy HH:mm:ss", ci);
                                    hora = hora.Substring(11, 8).Replace(":", ""); // Extraigo.
                                    hora = hora + id; // Adjunto

                                    string key = Anio.ToString().Substring(2, 2) + Aduana.ToString() + DocumentoTipo.ToString() + DocumentoNro.ToString() + Letra.ToString() + hora;
                                    Encryption64 enc = new Encryption64();
                                    String encriptionResult = enc.Encrypt(key, enc.getDefaultKey());
                                    String UrlDespacho = "www.sertear.com.ar/srd/getPdf.aspx?qid=" + encriptionResult;

                                    aSchedule.afipDigit.Familia[] fami = getFamilyNumbers(pdf);


                                    // Si no encontro ninguna pag:
                                    if (fami[0].cantidad == 0 && fami[1].cantidad == 0 && fami[2].cantidad == 0 && fami[3].cantidad == 0 && fami[4].cantidad == 0 && desp.Substring(0,2).Equals("09"))
                                    {
                                        fami[0].cantidad = PdfUtils.Instance.cantPaginas(pdf);
                                    }

                                    // Aviso de digitalización
                                    try
                                    {
                                        afipDigit.Recibo errorCode = AFIP.avisoDigitalizacion(desp,
                                                                                                CuitDespachante,
                                                                                                "30710964277",
                                                                                                CuitImportadorExportador,
                                                                                                "",
                                                                                                "000", UrlDespacho,
                                                                                                fami,
                                                                                                DateTime.Now,
                                                                                                "",
                                                                                                Hashing.Instance.GetAfipHash(pdf),
                                                                                                Paginas,
                                                                                                sigea
                                                                                                );

                                        writeTextFile(errorCode.codError + " - " + errorCode.descError);

                                        if (errorCode.codError == 0)
                                        {
                                            transaccionDigitalizacion.Commit();
                                        }
                                        else if (errorCode.codError == 102 && (errorCode.descError.Contains("DIGI") || errorCode.descError.Contains("DIEN") || errorCode.descError.Contains("DEEN") || errorCode.descError.Contains("RELE")))
                                        {
                                            transaccionDigitalizacion.Rollback();
                                            if (errorCode.descError.Contains("DIGI"))
                                            {
                                                oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate = 2 WHERE IDNS_Documento =" + id;
                                                oraCmd.CommandType = CommandType.Text;
                                                oraCmd.ExecuteNonQuery();
                                                tracking.logTrack(Convert.ToInt32(id), "AFIP WS", "23308861279", "", errorCode.codError + " // " + errorCode.descError + " // " + desp);
                                            }
                                            else if (errorCode.descError.Contains("DIEN"))
                                            {
                                                oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate = 4 WHERE IDNS_Documento =" + id;
                                                oraCmd.CommandType = CommandType.Text;
                                                oraCmd.ExecuteNonQuery();
                                                tracking.logTrack(Convert.ToInt32(id), "AFIP WS", "23308861279", "", errorCode.codError + " // " + errorCode.descError + " // " + desp);
                                            }
                                            else if (errorCode.descError.Contains("DEEN"))
                                            {
                                                oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate = 5 WHERE IDNS_Documento =" + id;
                                                oraCmd.CommandType = CommandType.Text;
                                                oraCmd.ExecuteNonQuery();
                                                tracking.logTrack(Convert.ToInt32(id), "AFIP WS", "23308861279", "", errorCode.codError + " // " + errorCode.descError + " // " + desp);
                                            }
                                            else if (errorCode.descError.Contains("RELE"))
                                            {
                                                oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate = 6 WHERE IDNS_Documento =" + id;
                                                oraCmd.CommandType = CommandType.Text;
                                                oraCmd.ExecuteNonQuery();
                                                tracking.logTrack(Convert.ToInt32(id), "AFIP WS", "23308861279", "", errorCode.codError + " // " + errorCode.descError + " // " + desp);
                                            }
                                        }
                                        else if (errorCode.codError == 101)
                                        {
                                            transaccionDigitalizacion.Rollback();
                                            oraCmd.CommandText = "UPDATE SRD_DOCUMENTOS SET AFIPstate = 7 WHERE IDNS_Documento =" + id;
                                            oraCmd.CommandType = CommandType.Text;
                                            oraCmd.ExecuteNonQuery();
                                            tracking.logTrack(Convert.ToInt32(id), "AFIP WS", "23308861279", "", errorCode.codError + " // " + errorCode.descError + " // " + desp);
                                        }
                                        else
                                        {
                                            transaccionDigitalizacion.Rollback();
                                            tracking.logTrack(Convert.ToInt32(id), "AFIP WS", "23308861279", "", errorCode.codError + " // " + errorCode.descError + " // " + desp);
                                        }
                                    }
                                    catch
                                    {
                                        transaccionDigitalizacion.Rollback();
                                    }
                                }
                                catch (Exception ex)
                                {
                                    // Rollback!
                                    transaccionDigitalizacion.Rollback();
                                }
                            }
                            else
                            {
                                writeTextFile("El PDF para el despacho no existe!");
                                emailing.Soporte("AFIP WS DIGITALIZACION - ", "El archivo " + pdf + " no existe.");
                            }
                        }
                        catch (Exception ex)
                        {
                            emailing.Soporte("AFIP WS DIGITALIZACION - ", "NO se pudo realizar la transaccion; " + ex.Message);
                        }
                    }
                }
                finally
                {
                    oraConn.Close();
                    oraConn = null;
                    writeTextFile("Fin del programa.");
                }
            }
            catch (Exception ex){

                emailing.Soporte("AFIP WS DIGITALIZACION - ", "NO se pudo realizar la transaccion; " + ex.Message);
            }

            closeTextFile();

        }
        #endregion   


        TextWriter tw = null;
        public void createTextFile(string fileLogName)
        {

            if (File.Exists(Environment.CurrentDirectory + @"\" + fileLogName + ".log"))
            {
                Console.WriteLine(" -> ELIMINANDO LOG ANTERIOR.");
                File.Delete(Environment.CurrentDirectory + @"\" + fileLogName + ".log");
            }
            
            Console.WriteLine(" -> CREANDO NUEVO LOG.");
            tw = new StreamWriter(Environment.CurrentDirectory + @"\Log.txt");
        }

        public void closeTextFile()
        {
            tw.Close();
        }

        public void writeTextFile(string logLine)
        {
            Console.WriteLine(DateTime.Now + "  -  " + logLine); ;
            tw.WriteLine(DateTime.Now + "  -  " + logLine);
        }


        private void DespachosDegiacomo()
        {
            Console.WriteLine("Iniciando flujo... ");

            try
            {
                countersEnable = false;

                Console.WriteLine("Obteniendo configuración... ");

                string rutaBase = (@"\\clustersrdfs.lacaut.com.ar\").ToUpper();
                string directorio = (@"srd\A Importar Out Source\DeGiacomo\").ToUpper();
                string ruta = rutaBase + directorio; 
                


                Console.WriteLine(ruta);

                if (Directory.Exists(ruta))
                {
                oraConn = Conexion.Instance();

                string[] files = Directory.GetFiles(ruta, "*.pdf");
                    if (files.Length > 0)
                    {
                        foreach (string pdf in files)
                        {
                            try
                            {
                                string despacho = pdf.Replace(ruta, "").Replace("\\", "").ToUpper().Replace(".PDF", "");
                                Console.WriteLine("Obteniendo Despacho: " + despacho);
                                string cuitcliente = "";
                                string cliente = "";
                                string cuitdespachante = "";
                                string despachante = "";
                                string paginas = "";
                                string nrointerno = "0";
                                string tipoOper = "";
                                DateTime fecOfi = DateTime.MinValue;
                                DateTime dateToInsert = DateTime.Now;
                                int bytespdf = 0;
                                aSchedule.Logic.Manager.Guias.GuiaAdapterMngr avisoFacturar = new Logic.Manager.Guias.GuiaAdapterMngr();
                                bool isInSRD = false;

                                if (VerificadorDespacho(despacho))
                                {
                                    if (ValidarDespacho(despacho))
                                    {
                                        /* ************************ NOMRALES ************************ */
                                        #region Normal

                                        FileStream fls = new FileStream(pdf, FileMode.Open, FileAccess.Read);
                                        bytespdf = System.Convert.ToInt32(fls.Length);
                                        fls.Close();

                                        XmlDocument xd = new XmlDocument();
                                        xd.Load(pdf.ToUpper().Replace(".PDF", ".XML"));

                                        string imageneslote = "";
                                        string paginaslote = "";
                                        int caja = 0;

                                        XmlNodeList nodeList = xd.SelectNodes("//root/document/field");
                                        foreach (XmlNode nd in nodeList)
                                            switch (nd.Attributes[1].Value)
                                            {
                                                case "Recuento de imágenes en documento":
                                                    imageneslote = nd.Attributes[2].Value;
                                                    break;
                                                case "Image count in document":
                                                    imageneslote = nd.Attributes[2].Value;
                                                    break;
                                                case "Recuento de páginas en documento":
                                                    paginaslote = nd.Attributes[2].Value;
                                                    break;
                                                case "Page count in document":
                                                    paginaslote = nd.Attributes[2].Value;
                                                    break;
                                                case "Caja Fisica":
                                                    caja = int.Parse(nd.Attributes[2].Value);
                                                    break;
                                            }
                                        xd = null;

                                        // Trato de obtener el despacho de la tabla de DEGIACOMO
                                        Console.WriteLine("Obteniendo Datos de SRD-GUIAS.... ");
                                        try
                                        {
                                            oraCmd = new OracleCommand();
                                            oraCmd.Connection = oraConn;
                                            oraCmd.CommandText = "SCH_P_LOADFROMDEGIACOMO";
                                            oraCmd.CommandType = CommandType.StoredProcedure;
                                            oraCmd.Parameters.Add(new OracleParameter("P_SD_DESPACHO", OracleDbType.Varchar2,200)).Value = despacho;
                                            oraCmd.Parameters.Add(new OracleParameter("O_Cursor", OracleDbType.RefCursor)).Direction = ParameterDirection.Output;

                                            OracleDataReader odr = oraCmd.ExecuteReader();

                                            if (odr.Read())
                                            {
                                                Console.WriteLine("  LEYENDO DATOS DE SRD GUIAS...");
                                                paginas = paginaslote;
                                                nrointerno = (odr.IsDBNull(odr.GetOrdinal("REFERENCIA"))) ? "" : odr.GetOracleString(odr.GetOrdinal("REFERENCIA")).ToString();
                                                cuitcliente = (odr.IsDBNull(odr.GetOrdinal("CUIT"))) ? "" : odr.GetOracleDecimal(odr.GetOrdinal("CUIT")).ToString();
                                                cliente = (odr.IsDBNull(odr.GetOrdinal("TITULAR"))) ? "" : odr.GetOracleString(odr.GetOrdinal("TITULAR")).ToString();
                                                cuitdespachante = "20109331008";
                                                despachante = "DE GIACOMO JUAN CARLOS";
                                                fecOfi = (odr.IsDBNull(odr.GetOrdinal("OFICIALIZADA"))) ? DateTime.MinValue : DateTime.Parse(odr.GetOracleDate(odr.GetOrdinal("OFICIALIZADA")).ToString());
                                                tipoOper = "AUT";
                                                isInSRD = (paginas != null && (Convert.ToInt32(paginas) > 0) && !cliente.Equals(""));
                                            }
                                            else
                                            {
                                                Console.WriteLine("NO ENCONTRADO EN SRD-GUIAS");
                                            }

                                            odr.Close();
                                            odr = null;
                                        }
                                        catch (Exception ex)
                                        {
                                            emailing.Soporte("SRD SChedule - SRD_GUIAS", ex);
                                            isInSRD = false;
                                        }
                                        finally
                                        {
                                            oraCmd = null;
                                        }

                                        // Si se pudo obtener algo, asi sea de SRD o Solobian; continuo...
                                        if (isInSRD)
                                        {
                                            if (cuitcliente.Length == 11)
                                            {
                                                if (paginas != "")
                                                {
                                                    if (ValidaCuit(cuitcliente))
                                                    {

                                                        if ((cuitcliente.Length == 11) && (ValidaCuit(cuitcliente)))
                                                        {
                                                            if ((cuitdespachante.Length == 11) && (ValidaCuit(cuitdespachante)))
                                                            {
                                                                if (tryParse(paginas))
                                                                {
                                                                    Console.WriteLine("  DESPACHO VALIDADO");

                                                                    oraCmd = new OracleCommand();
                                                                    oraCmd.Connection = oraConn;
                                                                    OracleTransaction transaccionAfip = oraConn.BeginTransaction(IsolationLevel.ReadCommitted);
                                                                    try
                                                                    {

                                                                        byte[] saltC = Hashing.GenerateSalt();
                                                                        string saltStrC = Convert.ToBase64String(saltC);
                                                                        string passwordC = Hashing.GetSHA256("SERTEARSRD", saltC);

                                                                        byte[] saltD = Hashing.GenerateSalt();
                                                                        string saltStrD = Convert.ToBase64String(saltD);
                                                                        string passwordD = Hashing.GetSHA256("SERTEARSRD", saltD);

                                                                        Console.WriteLine("  AGREGANDO DOCUMENTO A SISTEMA SRD...");

                                                                        oraCmd.CommandText = "SCH_P_DOCUMENTOS_ADD";
                                                                        oraCmd.CommandType = CommandType.StoredProcedure;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Anio", OracleDbType.Decimal)).Value = "20" + despacho.Substring(0, 2);
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Aduana", OracleDbType.Varchar2, 3)).Value = despacho.Substring(2, 3);
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoTipo", OracleDbType.Varchar2, 4)).Value = despacho.Substring(5, 4).ToUpper();
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_DocumentoNro", OracleDbType.Varchar2, 6)).Value = despacho.Substring(9, 6);
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Letra", OracleDbType.Varchar2, 1)).Value = despacho.Substring(15, 1).ToUpper();
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Caja", OracleDbType.Varchar2, 20)).Value = caja;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_Paginas", OracleDbType.Decimal)).Value = (int.Parse(paginaslote) - 1).ToString(); //paginas
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasLote", OracleDbType.Decimal)).Value = imageneslote;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasPDF", OracleDbType.Decimal)).Value = PdfUtils.Instance.cantPaginas(pdf); ;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_PaginasFacturador", OracleDbType.Decimal)).Value = paginas;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_CuitDespachante", OracleDbType.Varchar2, 11)).Value = cuitdespachante;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_Despachante", OracleDbType.Varchar2, 100)).Value = despachante.ToUpper().Trim();
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_CuitImportadorExportador", OracleDbType.Varchar2, 11)).Value = cuitcliente;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_ImportadorExportador", OracleDbType.Varchar2, 100)).Value = cliente.ToUpper().Trim();
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_BytesPdf", OracleDbType.Decimal)).Value = bytespdf.ToString();
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_PasswordD", OracleDbType.Varchar2, 128)).Value = passwordD;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_SaltD", OracleDbType.Varchar2, 50)).Value = saltStrD;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_PasswordC", OracleDbType.Varchar2, 128)).Value = passwordC;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_SaltC", OracleDbType.Varchar2, 50)).Value = saltStrC;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_NC_NumeroInterno", OracleDbType.Varchar2, 100)).Value = nrointerno.ToString();
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_H_Upd", OracleDbType.Date)).Value = dateToInsert;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_SD_TipoOpe", OracleDbType.Varchar2, 24)).Value = tipoOper;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_H_Oficializacion", OracleDbType.Date)).Value = (fecOfi == DateTime.Parse("01/01/0001")) ? (object)DBNull.Value : fecOfi;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_NS_Digitalizador", OracleDbType.Decimal)).Value = "1";
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_NS_Resguardante", OracleDbType.Decimal)).Value = "3";
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_Resultado", OracleDbType.Varchar2, 100)).Direction = ParameterDirection.Output;
                                                                        oraCmd.Parameters.Add(new OracleParameter("P_BytesExistente", OracleDbType.Varchar2, 100)).Direction = ParameterDirection.Output;

                                                                        oraCmd.ExecuteNonQuery(); Console.WriteLine("  Store ejecutado!");

                                                                        string respuesta = oraCmd.Parameters["P_Resultado"].Value.ToString();
                                                                        string bytesExistente = oraCmd.Parameters["P_BytesExistente"].Value.ToString();

                                                                        if (!respuesta.Equals("0") && !configuracion.DesaMode)
                                                                        {
                                                                            #region MOVE!
                                                                            try
                                                                            {
                                                                                Console.WriteLine("  ************* Moviendo... *************");
                                                                                string destinationFolder = string.Concat(new object[] { @"", dateToInsert.Year, @"\", dateToInsert.Month.ToString("00"), @"\", dateToInsert.Day.ToString("00"), @"\" });

                                                                                Console.WriteLine("  Copiando el archivo: " + pdf);
                                                                                Console.WriteLine(pdf.ToUpper().Replace(directorio, destinationFolder));

                                                                                File.Copy(pdf, pdf.Replace(directorio, destinationFolder), true);
                                                                                // Me fijo si pudo copiarlo
                                                                                if (File.Exists(pdf.Replace(directorio, destinationFolder)))
                                                                                {
                                                                                    Console.WriteLine("  Commit en bd...");
                                                                                    transaccionAfip.Commit();

                                                                                    Console.WriteLine("  Borrando pdf...");
                                                                                    File.Delete(pdf);

                                                                                    Console.WriteLine("  Copiando xml...");

                                                                                    while (!File.Exists(pdf.ToUpper().Replace(".PDF", ".XML").Replace(directorio.ToUpper(), destinationFolder)))
                                                                                        File.Copy(pdf.ToUpper().Replace(".PDF", ".XML"), pdf.ToUpper().Replace(".PDF", ".XML").Replace(directorio.ToUpper(), destinationFolder), true);

                                                                                    if (File.Exists(pdf.ToUpper().Replace(".PDF", ".XML").Replace(directorio.ToUpper(), destinationFolder)))
                                                                                    {
                                                                                        Console.WriteLine("  Borrando xml...");
                                                                                        File.Delete(pdf.ToUpper().Replace(".PDF", ".XML"));
                                                                                    }
                                                                                    Console.WriteLine("  Fin!");

                                                                                    //avisoFacturar.avisoFacturacionWout(despacho, idGuiaDetalle);
                                                                                }
                                                                                else
                                                                                {
                                                                                    Console.WriteLine("  NO SE PUDO MOVER EL ARCHIVO: " + pdf);
                                                                                    emailing.Soporte("SRD SChedule Despacho", "No se pudo copiar el archivo: " + pdf + " Reinforme de afip - intento DIGI.");
                                                                                    transaccionAfip.Rollback();
                                                                                }

                                                                                Console.WriteLine("Procesar proximo?");
                                                                                //Console.ReadLine();
                                                                                Console.WriteLine("OK...");
                                                                                System.Threading.Thread.Sleep(100); // 1000ms = 1s * 60s = 1 m * Cantidad_Minutos 
                                                                            }
                                                                            catch (Exception ex)
                                                                            {
                                                                                try { transaccionAfip.Rollback(); }
                                                                                catch { }
                                                                                Console.WriteLine(ex.Message);
                                                                                Informe("SCHEDULE", "AFIP CATCH, " + ex.Message + "; despacho: " + despacho, caja.ToString(), paginaslote);
                                                                            }
                                                                            #endregion
                                                                        }
                                                                        else
                                                                        {
                                                                            try { transaccionAfip.Rollback(); }
                                                                            catch { }
                                                                            if (bytesExistente.Equals(bytespdf.ToString()))
                                                                                Informe("SCHEDULE", "Existente. La imagen del despacho es idéntica , despacho " + despacho, caja.ToString(), paginaslote);
                                                                            else
                                                                                Informe("SCHEDULE", "Existente. Las imágenes son diferentes , despacho " + despacho, caja.ToString(), paginaslote);
                                                                        }
                                                                    }
                                                                    catch (Exception ex)
                                                                    {
                                                                        try { transaccionAfip.Rollback(); }
                                                                        catch { }
                                                                        Console.WriteLine(ex.Message);
                                                                        Informe("SCHEDULE", ex.Message, "", "");
                                                                    }
                                                                }
                                                                else
                                                                    Informe("SCHEDULE", "Número de Páginas Incorrecto, despacho " + despacho, caja.ToString(), paginaslote);
                                                            }
                                                            else
                                                                Informe("SCHEDULE", "Cuit Incorrecto o Sin datos de Despachante en BAS, despacho " + despacho, caja.ToString(), paginaslote);
                                                        }
                                                        else
                                                            Informe("SCHEDULE", "Cuit Incorrecto o Sin datos de Importador/Exportador en BAS, despacho " + despacho, caja.ToString(), paginaslote);
                                                    }
                                                    else
                                                        Informe("SCHEDULE", "Cuit Incorrecto en BAS (Digito Verificador), despacho " + despacho, caja.ToString(), paginaslote);
                                                }
                                                else
                                                    Informe("SCHEDULE", "No se informo cantidad de Páginas, despacho " + despacho, caja.ToString(), paginaslote);
                                            }
                                            else
                                                Informe("SCHEDULE", "Cuit Incorrecto o Sin datos de Importador/Exportador en BAS, despacho " + despacho, caja.ToString(), paginaslote);
                                        }
                                        else
                                        {
                                            Informe("SCHEDULE", "Despacho inexistente BAS, despacho " + despacho, caja.ToString(), paginaslote);
                                        }
                                        #endregion
                                    }
                                    else
                                        Informe("SCHEDULE", "No es un despacho corecto para De#Giacomo, despacho " + despacho, "", "");
                                }
                                else
                                    Informe("SCHEDULE", "Nro. de Despacho o Adicional personal Incorrecto (DV), despacho " + despacho, "", "");
                            }
                            catch (Exception ex)
                            {
                                Informe("SCHEDULE", ex.Message, "", "");
                                emailing.Soporte("SRD SChedule Despacho", ex);
                                if (sqlConn.State == ConnectionState.Closed)
                                {
                                    sqlConn.Open();
                                }
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {

                if (sqlConn.State == ConnectionState.Closed)
                {
                    sqlConn.Open();
                }
                Informe("SCHEDULE", ex.Message, "", "");
                emailing.Soporte("SRD SChedule Despacho", ex);
            }
            finally
            {
                if ((sqlConn != null) && (sqlConn.State != ConnectionState.Closed)) sqlConn.Close();
                sqlConn = null;

                if ((oraConn != null) && (oraConn.State != ConnectionState.Closed)) oraConn.Close();
                oraConn = null;
            }

        }

        public void DownloadImages()
        {
            // Parametrizar:
            string destinationFolder = @"C:\A importar a la DB\DOWNLOADS\";
            string logFile = destinationFolder + @"\ResultadoDescargas.txt";

            oraConn = Conexion.Instance();
            oraCmd = new OracleCommand();
            oraCmd.Connection = oraConn;

            Console.WriteLine("Cargando Vector...");

            ArrayList despachos = loadVector();
            StreamWriter SW;

            Console.WriteLine("Creando Log: " + logFile);
            if(File.Exists(logFile)) File.Delete(logFile);
            SW = File.CreateText(logFile);

            Console.WriteLine("Comenzando descarga...");

            // Por cada uno de los despachos en el vector de descarga:
            foreach (string despacho in despachos)
            {
                try
                {
                    // Consulta NO PARAMETRIZADA!!! cuidado al REALIZAR con vectores superiores a 100 posiciones.
                    // TODO: realizar con Store Procedure
                    oraCmd.CommandText =
                                        "select " +
                                            " SRD_Documentos.H_Upd" +
                                        " from srd_documentos where " +
                                            " SD_Anio = 20" + despacho.ToString().Substring(0, 2) +
                                            " and SD_Aduana ='" + despacho.ToString().Substring(2, 3) + "'" +
                                            " and SD_DocumentoTipo ='" + despacho.ToString().Substring(5, 4) + "'" +
                                            " and SD_DocumentoNro ='" + despacho.ToString().Substring(9, 6) + "'" +
                                            " and SD_Letra ='" + despacho.ToString().Substring(15, 1) + "'";

                    oraCmd.CommandType = CommandType.Text;
                    OracleDataReader odr = oraCmd.ExecuteReader();

                    if (odr.Read())
                    {
                        try
                        {
                            DateTime pdfUbicationDate = DateTime.Parse(odr.GetOracleDate(odr.GetOrdinal("H_Upd")).ToString());
                            String pdfUbicationKey = @"\\clustersrdfs.lacaut.com.ar\" + pdfUbicationDate.Year + @"\" + pdfUbicationDate.Month.ToString("00") + @"\" + pdfUbicationDate.Day.ToString("00") + @"\";
                            pdfUbicationKey += despacho.ToString() + ".PDF";

                            if (File.Exists(pdfUbicationKey))
                            {
                                File.Copy(pdfUbicationKey, destinationFolder + despacho + ".PDF");
                                SW.WriteLine("Descarga completa " + pdfUbicationKey);
                            }
                        }
                        catch (Exception ex)
                        {
                            SW.WriteLine("Error " + ex.Message);
                            Console.WriteLine("Error > Se quiso descargar: " + despacho.ToString() + "Produciendo la excepcion: ");
                            Console.WriteLine(ex.Message);
                            Console.Read();
                        }

                    }
                    else
                    {
                        Console.WriteLine("Sin datos en DB para el despacho: " + despacho + " , El despacho no existe en las Bases del sistema");
                        SW.WriteLine("Sin datos en DB para el despacho: " + despacho + " , El despacho no existe en las Bases del sistema");
                    }
                }
                catch (Exception ex)
                {
                    SW.WriteLine("Error : " + despacho + " " + despacho + " Descripcion: " + ex.Message);
                }
            }

            SW.Close();
        }

        private ArrayList loadVector()
        {
            ArrayList array = new ArrayList();

            array.Add("10073IC04002468R");
            array.Add("10073IC04075574C");
            array.Add("10073IC04090950U");
            array.Add("10073IC04091001X");
            array.Add("10073IC04115679D");
            array.Add("10073IC04118326S");
            array.Add("10073IC04118967G");
            array.Add("10073IC04163991D");
            array.Add("10073IC04182908C");
            array.Add("10073IC04226365V");
            array.Add("10073IC04228357B");
            array.Add("10073IC04231730N");
            array.Add("10073IC04252480S");
            array.Add("10073IC05000486Z");
            array.Add("10073IC05000731J");
            array.Add("10073IC05002315J");
            array.Add("10073IC05003129N");
            array.Add("10073IC05003815P");
            array.Add("10073IC05004398W");
            array.Add("10073IC05006063N");
            array.Add("10073IC05006485V");
            array.Add("10073IC05006748A");
            array.Add("10073IC24001239Y");
            array.Add("10073IC24001586T");
            array.Add("10073IC25000003D");
            array.Add("10073IC55000226N");
            array.Add("10073IC55000250K");
            array.Add("10073IC55000256Z");
            array.Add("10073IC55000262N");
            array.Add("10073IC55000263Y");
            array.Add("10073IC55000264P");
            array.Add("10073IC55000274Z");
            array.Add("10073IC55000275R");
            array.Add("10073IC55000492S");
            array.Add("10073IC55001224M");
            array.Add("10073IT04001591H");
            array.Add("10073IT04001770G");
            array.Add("10073IT14001362E");
            array.Add("10073IT14001484J");
            array.Add("10073TR04005238S");
            array.Add("10073IC04099610W");
            array.Add("10073IC04123804P");
            array.Add("10073IC04238163U");
            array.Add("10073IC04238859J");
            array.Add("10073IC04035874B");
            array.Add("10073IC04115488B");
            array.Add("10073IC04128640S");
            array.Add("10073IC04150714P");
            array.Add("10073IC04226505R");
            array.Add("10073IC04236227T");
            array.Add("10073IC05000954Z");
            array.Add("10073IC05000977V");
            array.Add("10073IC05001282L");
            array.Add("10073IC05001447Y");
            array.Add("10073IC05002421H");
            array.Add("10073IC05003020D");
            array.Add("10073IC05003896B");
            array.Add("10073IC05005029Y");
            array.Add("10073IC05005741P");
            array.Add("10073IC05006123K");
            array.Add("10073IG05003363R");
            array.Add("10073IT14001816X");
            array.Add("10073IT14002206C");
            array.Add("10073IT14002587Y");
            array.Add("10073TR04000883T");
            array.Add("10073TR04001087Z");
            array.Add("10073TR04003198V");
            array.Add("10073TR04004307Y");
            array.Add("10073TR04004389B");
            array.Add("10073TR04005111X");
            array.Add("10073TR04005118P");
            array.Add("10073TR04005193S");
            array.Add("10073IC04102059Y");
            array.Add("10073TR04001214X");
            array.Add("10073TR04004246Z");
            array.Add("10073TR04004371P");
            array.Add("10073TR04004406Y");
            array.Add("10073TR04004411K");
            array.Add("10073TR04001536P");

            return array;
        }


    }

 

}