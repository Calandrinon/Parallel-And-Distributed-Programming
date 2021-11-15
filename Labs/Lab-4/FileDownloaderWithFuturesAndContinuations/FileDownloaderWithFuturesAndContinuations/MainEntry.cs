// See https://aka.ms/new-console-template for more information

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FileDownloaderWithFuturesAndContinuations
{
    class MainEntry
    {
        public static void Main(String[] args)
        {
            int limit = (int) 1e6;
            List<int> listOfNumbers = Enumerable.Range(0, limit).ToList();
            int maximumNumberOfThreads = Environment.ProcessorCount;
            int amountOfNumbersForOneTask = limit / maximumNumberOfThreads;
            List<Task> tasks = new List<Task>();

            for (int taskIndex = 0; taskIndex < maximumNumberOfThreads; taskIndex++)
            {
                Task task = Task.Run(() => {Console.WriteLine("Task {0}", taskIndex + 1);});
                tasks.Add(task);
            }

            Task.WaitAll(tasks.ToArray());
            Console.WriteLine("Tasks done.");
        }
    }
}