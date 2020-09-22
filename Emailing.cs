using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;

using aSchedule.Logic.DAL;
using aSchedule.Logic.Entity;
using aSchedule.Logic.Manager;

namespace aSchedule.Logic.Secure
{
    class Emailing
    {
        Config configuracion = null;
        ConfigMngr cnfgMngr = null;
        String lastMessage = "X";
        String error;
        String to;
        String from;
        ArrayList toX = new ArrayList();

        // Singleton
        private static Emailing instance = new Emailing();
        private Emailing()
        {
            try
            {
                configuracion = new Config();
                cnfgMngr = new ConfigMngr();
                configuracion = cnfgMngr.getConfig();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        public static Emailing Instance
        {
            get
            {
                return instance;
            }
        }

        public void Soporte(string asunto, Exception ex)
        {
            if (!lastMessage.StartsWith(ex.Message))
            {
                lastMessage = ex.Message;
                try
                {
                    System.Net.Mail.MailMessage correo = new System.Net.Mail.MailMessage();
                    correo.From = new System.Net.Mail.MailAddress("webmaster@lakaut.com.ar");
                    correo.To.Add(configuracion.MailSoporte);
                    correo.Subject = asunto;
                    correo.Body = ex.Message + "<br />" + ex.ToString();
                    correo.IsBodyHtml = true;
                    correo.Priority = System.Net.Mail.MailPriority.Normal;
                    System.Net.Mail.SmtpClient smtp = new System.Net.Mail.SmtpClient();
                    //smtp.ClientCertificates.Add(
                    smtp.Host = configuracion.Mail;
                    smtp.Credentials = new System.Net.NetworkCredential(configuracion.MailUser, configuracion.MailPwd);
                    smtp.Send(correo);
                }
                catch { }
            }
        }

        public void Soporte(string asunto, string mensaje)
        {
            if (!lastMessage.StartsWith(mensaje))
            {
                lastMessage = mensaje;
                try
                {
                    System.Net.Mail.MailMessage correo = new System.Net.Mail.MailMessage();
                    correo.From = new System.Net.Mail.MailAddress("webmaster@lakaut.com.ar");
                    correo.To.Add(configuracion.MailSoporte);
                    correo.Subject = asunto;
                    correo.Body = mensaje;
                    correo.IsBodyHtml = true;
                    correo.Priority = System.Net.Mail.MailPriority.High;
                    System.Net.Mail.SmtpClient smtp = new System.Net.Mail.SmtpClient();
                    smtp.Host = configuracion.Mail;
                    smtp.Credentials = new System.Net.NetworkCredential(configuracion.MailUser, configuracion.MailPwd);
                    smtp.Send(correo);
                }
                catch(Exception ex) 
                {
                    Console.WriteLine(configuracion.MailSoporte);
                    Console.WriteLine(configuracion.Mail);
                    Console.WriteLine(ex.StackTrace);
                    Console.WriteLine(ex.Message);
                    Console.WriteLine(ex.ToString());
                }
            }
        }

        public void TestMail(string asunto, string mensaje, string from, string to)
        {
            Console.WriteLine("Iniciando...");
            if (!lastMessage.StartsWith(mensaje))
            {
                lastMessage = mensaje;
                try
                {
                    Console.WriteLine("Asunto: " + asunto);
                    Console.WriteLine("Mensaje: " + mensaje);
                    Console.WriteLine("De: " + from);
                    Console.WriteLine("Para: " + to);
                    Console.WriteLine("Host: " + configuracion.Mail);
                    Console.WriteLine("Usuario SMTP: " + configuracion.MailUser);

                    System.Net.Mail.MailMessage correo = new System.Net.Mail.MailMessage();
                    correo.From = new System.Net.Mail.MailAddress(from);
                    correo.To.Add(to);
                    correo.Subject = asunto;
                    correo.Body = mensaje;
                    correo.IsBodyHtml = true;
                    correo.Priority = System.Net.Mail.MailPriority.High;
                    System.Net.Mail.SmtpClient smtp = new System.Net.Mail.SmtpClient();
                    smtp.Host = configuracion.Mail;
                    smtp.Credentials = new System.Net.NetworkCredential(configuracion.MailUser, configuracion.MailPwd);
                    Console.WriteLine("Enviando...");
                    smtp.Send(correo);
                    Console.WriteLine("Enviado.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine(configuracion.MailSoporte);
                    Console.WriteLine(configuracion.Mail);
                    Console.WriteLine(ex.StackTrace);
                    Console.WriteLine(ex.Message);
                    Console.WriteLine(ex.ToString());
                }
            }
        }

        public void SoporteEndo(string asunto, string mensaje)
        {
            if (!lastMessage.StartsWith(mensaje))
            {
                lastMessage = mensaje;
                try
                {
                    System.Net.Mail.MailMessage correo = new System.Net.Mail.MailMessage();
                    correo.From = new System.Net.Mail.MailAddress("webmaster@lakaut.com.ar");
                    correo.To.Add(configuracion.MailSoporte);
                    correo.Subject = asunto;
                    correo.Body = mensaje;
                    correo.IsBodyHtml = true;
                    correo.Priority = System.Net.Mail.MailPriority.Normal;
                    System.Net.Mail.SmtpClient smtp = new System.Net.Mail.SmtpClient();
                    smtp.Host = configuracion.Mail;
                    smtp.Credentials = new System.Net.NetworkCredential(configuracion.MailUser, configuracion.MailPwd);
                    smtp.Send(correo);
                }
                catch { }
            }
        }

        public void SoporteOutSource(string asunto, string mensaje)
        {
            try
            {
                System.Net.Mail.MailMessage correo = new System.Net.Mail.MailMessage();
                correo.From = new System.Net.Mail.MailAddress("webmaster@lakaut.com.ar");
                correo.To.Add(configuracion.MailSoporte);
                correo.Subject = asunto;
                correo.Body = mensaje;
                correo.IsBodyHtml = true;
                correo.Priority = System.Net.Mail.MailPriority.Normal;
                System.Net.Mail.SmtpClient smtp = new System.Net.Mail.SmtpClient();
                smtp.Host = configuracion.Mail;
                smtp.Credentials = new System.Net.NetworkCredential(configuracion.MailUser, configuracion.MailPwd);
                smtp.Send(correo);
            }
            catch { }
        }

        public void mailerrorAdd(string Error)
        {
            error += "<BR> " + Error;
        }

        public void mailerrorClear()
        {
            toX.Clear();
            from = "";
            error = "";
        }

        public void mailerrorConfig(string To, string From)
        {
            to = To;
            from = From;
            error = "";
        }

        public void mailerrorConfig(ArrayList To, string From)
        {
            toX = To;
            from = From;
            error = "";
        }

        public void mailerrorSend()
        {
            if (!error.Replace("<BR>","").Equals(""))
            {
                try
                {
                    System.Net.Mail.MailMessage correo = new System.Net.Mail.MailMessage();
                    correo.From = new System.Net.Mail.MailAddress(from);
                    foreach(string toSend in toX)
                    {
                        correo.To.Add(toSend);
                    }
                    correo.To.Add(configuracion.MailSoporte);
                    correo.Subject = "Informe de proceso.";
                    correo.Body = "Se le informan los errores arrojados como resultado del proceso: <br>" + error + " <br><br> Sistema de resguardo documental - SRD."; 
                    correo.IsBodyHtml = true;
                    correo.Priority = System.Net.Mail.MailPriority.Normal;
                    System.Net.Mail.SmtpClient smtp = new System.Net.Mail.SmtpClient();
                    smtp.Host = configuracion.Mail;
                    smtp.Credentials = new System.Net.NetworkCredential(configuracion.MailUser, configuracion.MailPwd);
                    smtp.Send(correo);
                }
                catch (Exception ex) { }
            }
        }
    }
}
