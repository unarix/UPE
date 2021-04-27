using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Data;
using System.Data.SqlClient;
using System.IO;
using System.Net.Mail;
using aSchedule.Logic;
using aSchedule.Logic.WS;
using aSchedule.Logic.Secure;
using System.Collections;
using System.Collections.Generic;


namespace aSchedule
{
    class Program
    {
        /// <summary>
        /// Batch
        /// </summary>
        [STAThread]
        void Main()
        {
            Console.WriteLine("Iniciado");

            switch (Configuracion.Default.Proceso)
            {
                /* *********************************** */
                /* ***********     PROD    *********** */
                /* *********************************** */
                case "MailTest":
                    Emailing emailing = Emailing.Instance;
                    emailing.TestMail("TEST", "Testeo de envio de Email", "webmaster@lakaut.com.ar", "msn@unarix.com.ar");

                    break;
                case "Clima":
                    Clima clima = new Clima();
                    clima.Current();
                    clima.Current5Day();
                    clima = null;
                    break;
                case "CTA":
                    CTA cta = new CTA();
                    cta.Iniciar();
                    cta = null;
                    break;
                case "SMS":
                    SMS sms = new SMS();
                    sms.Iniciar();
                    sms = null;
                    break;
                case "Creditos":
                    Creditos creditos = new Creditos();
                    creditos.Iniciar();
                    creditos = null;
                    break;
                case "SRD": // Incia el proceso de importacion solo una vez
                    SRD.Instance.Iniciar(); 
                    break;
                case "SRD_DeGiacomo": // Incia el proceso de importacion solo una vez
                    SRD.Instance.IniciarDegiacomo();
                    break;
                case "SRD_Recursive": // Incia el proceso de importacion recursivo
                    SRD.Instance.DespachosRecursive();
                    break;
                case "SRD_OutSrce": // Incia la importacion de despachos OUTSOURCE
                    SRDOutSource.Instance.DespachosOutSource();
                    break;
                case "SRD_IRON": // Incia la importacion de despachos DE IRON MOUNTAIN
                    SRDOutSource.Instance.DespachosRecursiveIM();
                    break;
                case "SRD_Afip": // Inicia el informe a Afip de los despachos no informados o con errores.
                    SRD.Instance.iniciarAvisoAfip();
                    break;
                case "SRD_LogDig": // Loguea el flujo de el proceso de digitalizacion.
                    aSchedule.Logic.LogDigFlow.Instance.LogXMLs();
                    break;
                case "SRD_Contratos": // Inicia la importacion de contratos.
                    SRDcontratos.Instance.contratos();
                    break;
                case "SRD_Aranceles":
                    SRDAranceles srdAranceles = new SRDAranceles();
                    srdAranceles.Init();
                    srdAranceles = null;
                    break;
                case "SRD_Arreglos":
                    SRD.Instance.Arreglar();
                    break;
                case "SRD_Facturacion":
                    SRDadviceGuias.Instance.avisarGuiasWout();
                    break;
                case "SRD_Despachos_ENDO_AFIP": // Inicia la importacion de despachos de AFIP en estado ENDO
                    SRDDespachosAFIP.Instance.ProcesarDespachosENDOWsAFIP();
                    break;
                case "SRD_Despachos_ENDO_AFIP_Desatendido": // Inicia la importacion de despachos de AFIP en estado ENDO
                    SRDDespachosAFIP.Instance.consDesatendidaAfip();
                    break;
                /* *********************************** */
                /* ***********     DESA    *********** */
                /* *********************************** */
                case "SRD_IRON_DESA": // Incia la importacion de despachos DE IRON MOUNTAIN DESARROLLO
                    SRDOutSource.InstanceDesa.DespachosRecursiveIM();
                    break;
                case "SRD_Recursive_DESA": // Incia el proceso de importacion DE IRON MOUNTAIN DESARROLLO
                    SRD.InstanceDesa.DespachosRecursive();
                    break;
                case "SRD_AfipTestWS": // Clase de testeo para webservices de AFIP.
                    afip tst = new afip();
                    ar.gov.afip.testdia.RtaPndListaEndo rta = tst.consultarPndListaEndo("30638406167", "20040410024","000", DateTime.Parse("01/01/2010"), DateTime.Parse("01/12/2010"));
                    break;
                case "SRD_AfipWS2": // Clase de testeo para webservices de AFIP.
                    afipTest tst2 = new afipTest();
                    tst2.testDigDepFielV2();
                    break;
                case "SRD_Contratos_DESA": // Inicia la importacion de contratos modo desarrollo.
                    SRDcontratos.InstanceDesa.contratos();
                    break;
                case "SRD_Despachos_ENDO_AFIP_DESA": // Inicia la importacion de contratos modo desarrollo.
                    SRDDespachosAFIP.InstanceDesa.ProcesarDespachosENDOWsAFIP();
                    break;
                case "AvisoPSADguias": // Solo ejecucion para FIXES.
                    SRDadviceGuias.Instance.PSADadvice();
                    break;
               /* case "DownloadImages": // Descarga de archivos PDF a pedido especifico
                    SRD.Instance.DownloadImages();
                    break;*/
            }

            Main();
        }
    }
}