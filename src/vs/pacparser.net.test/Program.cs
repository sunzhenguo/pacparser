using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using PacParserDotNet;
namespace pacparser.net.test
{
    class Program
    {
        static void Main(string[] args)
        {
            var v = PacParser.PacParserVersion;
            Console.WriteLine(v);
            var i = PacParser.Initialize();
            Console.WriteLine(i);
            var pacString = File.ReadAllText("proxy.pac");
            Console.WriteLine(pacString);
            var y = PacParser.ParsePacString(pacString);
            Console.WriteLine(y);
            var val = PacParser.FindProxy("http://news.manugarg.com", "news.manugarg.com");
            Console.WriteLine(val);
            PacParser.Cleanup();
            var foo = PacParser.JustFindProxyFromFileMS("http://news.manugarg.com", "news.manugarg.com", "proxy.pac");
            Console.WriteLine(foo);
            while(String.IsNullOrEmpty(Console.ReadLine()))
                ;
        }
    }
}
