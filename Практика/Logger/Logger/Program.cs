using System;
using System.IO; // для работы с файлами

namespace Logger
{  
    class Loger : IDisposable
    {
        StreamWriter writer;
        public Loger(string path)
        {
            try
            {
                FileInfo fInfo = new FileInfo(path);
                writer = new StreamWriter(path);
            }
            catch (Exception ex)
            {
                Console.WriteLine("{0}", ex.Message);
                throw ex;
            }
        }

        ~Loger()
        {
            writer.Close();
            writer.Dispose();
        }

        public bool Log(string data, severity sv)
        {
            writer.WriteLine($"[{DateTime.Now}][{SVtostr(sv)}]: {data} ");
            return true;
        }

        public void Dispose()
        {
            writer.Close();
            writer.Dispose();
        }

        public string SVtostr(severity sv)
        {
            string str;
            int tmp = Convert.ToInt32(sv);
            switch (tmp)
            {
                case 0: str = "trace"; break;
                case 1: str = "debug"; break;
                case 2: str = "information"; break;
                case 3: str = "warning"; break;
                case 4: str = "error"; break;
                case 5: str = "critical"; break;
                default: str = "Smth goes wrong :( "; break;
            }
            return str;
        }
    }

    public enum severity { trace, debug, information, warning, error, critical };

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter path to file: ");
            string path = Console.ReadLine();
            Console.WriteLine($"Entered path: {path}");

            if (!File.Exists(path)) {
                Console.WriteLine($"No file on the entered path: {path}\nNew file will be created!");
                try
                { 
                    File.Create(path); 
                }
                catch (AggregateException ex)
                {
                    Console.WriteLine("[ERROR]: ", ex.Message);
                } 
            }

            Loger lg = new Loger(path);
            lg.Log("Hello world!", severity.trace);
            lg.Dispose();
            //Console.ReadLine();
            //File.Delete(path);
        }
    }
}
