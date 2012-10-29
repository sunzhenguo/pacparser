using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using PacParser;
namespace pacparser.net.test
{
    class Program
    {
        static void Main(string[] args)
        {
            var v = PacParser.PacParser.PacParserVersion;
            Console.WriteLine(v);
            var i = PacParser.PacParser.Initialize();
            Console.WriteLine(i);
            var pacString = File.ReadAllText("proxy.pac");
            Console.WriteLine(pacString);
            var y = PacParser.PacParser.ParsePacString(pacString);
            Console.WriteLine(y);
            var val = PacParser.PacParser.FindProxy("http://news.manugarg.com", "news.manugarg.com");
            Console.WriteLine(val);
            while(String.IsNullOrEmpty(Console.ReadLine()))
                ;
            PacParser.PacParser.Cleanup();
        }
    }
}
