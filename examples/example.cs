using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using PacParserDotNet;


namespace pacparser.net.example
{
    class Program
    {
        static void Main(string[] args)
        {
			// call pacparser.net piece-by-piece
			if(PacParser.Initialize() &&
				PacParser.ParsePacFile("proxy.pac"))
			{
				var proxy = PacParser.FindProxy("http://news.manugarg.com", "news.manugarg.com");
				Console.WriteLine("FindProxy returned: " + proxy);

				PacParser.Cleanup();
			}

            while (String.IsNullOrEmpty(Console.ReadLine()))
                ;
        }
    }

}
