using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using PacParserDotNet;
using System.Runtime.InteropServices;
namespace pacparser.net.test
{
    class Program
    {

        static void Main(string[] args)
        {
            var i = 0;
            try
            {
                do
                {
                    var ver = PacParser.Version;
                    Console.WriteLine("pacparser version: " + ver);

                    // call pacparser.net piece-by-piece
                    var intd = PacParser.Initialize();
                    Console.WriteLine(intd);

                    var pacString = File.ReadAllText("proxy.pac");
                    Console.WriteLine(pacString);

                    var wasStrParsed = PacParser.ParsePacString(pacString);
                    Console.WriteLine("ParsePacString invoked: " + wasStrParsed);

                    var proxy = PacParser.FindProxy("http://news.manugarg.com", "news.manugarg.com");
                    Console.WriteLine(proxy);

                    PacParser.Cleanup();

                    // try aggregator function
                    var res = PacParser.JustFindProxyFromFileMS("http://news.manugarg.com", "news.manugarg.com", "proxy.pac");
                    Console.WriteLine("Aggregator result: " + res);
                }
                while (++i < 1000);
            }
            catch (Exception ex) { MessageBox(IntPtr.Zero, ex.StackTrace, "Error", 0); }

            while (String.IsNullOrEmpty(Console.ReadLine()))
                ;
        }


        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern MessageBoxResult MessageBox(IntPtr hWnd, String text, String caption, int options);


        /// <summary>
        /// Represents possible values returned by the MessageBox function.
        /// </summary>
        public enum MessageBoxResult : uint
        {
            Ok = 1,
            Cancel,
            Abort,
            Retry,
            Ignore,
            Yes,
            No,
            Close,
            Help,
            TryAgain,
            Continue,
            Timeout = 32000
        }
    }

}
