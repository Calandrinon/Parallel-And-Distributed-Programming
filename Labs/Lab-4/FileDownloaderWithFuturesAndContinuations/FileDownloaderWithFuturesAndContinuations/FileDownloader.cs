// See https://aka.ms/new-console-template for more information

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;

namespace FileDownloaderWithFuturesAndContinuations
{
    class FileDownloader
    {
        private static List<String> ReadUrlList(String filename)
        {
            List<String> listOfUrls = new List<string>();
            string[] lines = System.IO.File.ReadAllLines(filename);
            
            foreach (string line in lines)
                listOfUrls.Add(line);

            return listOfUrls;
        } 
        
        public static void Main(String[] args)
        {
            // The filepath contains the .. pattern for backwards directory navigation, because Jetbrains Rider 
            // apparently reads files from the bin/ directory where the compiled executables are saved.
            List<String> urls = ReadUrlList("../../../URLs.txt");

            foreach (var url in urls)
            {
                Console.WriteLine(url); 
            }
        }
    }
}