using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;

namespace FileDownloaderWithFuturesAndContinuations
{
    public class RequestResponseHandler
    {
        private List<String> listOfUrls; 
        public RequestResponseHandler(List<String> listOfUrls)
        {
            this.listOfUrls = listOfUrls;
            this.MakeRequest(listOfUrls[0]);
        }

        private static Tuple<String, int> parseResponse(String response)
        {
            String header = response.Substring(0, response.IndexOf("<"));
            int contentLengthStartIndex = header.IndexOf("Content-Length:") + "Content-Length:".Length;
            int contentLengthEndIndex = header.IndexOf("\n");
            String contextLengthSubstring = response.Substring(contentLengthStartIndex, contentLengthEndIndex);
            Regex regexPattern = new Regex(@"[0-9]+");
            String contextLengthValue = Regex.Match(contextLengthSubstring, @"\d+").Value;
            return new Tuple<String, int>(header, int.Parse(contextLengthValue));
        }

        private void RequestSendingCallback(IAsyncResult asyncResult)
        {
            Socket socket = (Socket)asyncResult.AsyncState;
            socket.EndSend(asyncResult);
            Console.WriteLine("Sent the message.");

            byte[] responseBuffer = new byte[50000];
            socket.BeginReceive(responseBuffer, 0, responseBuffer.Length,
                0, ResponseCallback, new Tuple<Socket, byte[]>(socket, responseBuffer));
        }
        
        private void ResponseCallback(IAsyncResult asyncResult)
        {
            Console.WriteLine("In the ResponseCallback...");
            (Socket socket, byte[] responseBuffer) = (Tuple<Socket, byte[]>) asyncResult.AsyncState;
            
            try
            {
                int numberOfBytesReceived = socket.EndReceive(asyncResult);
                String response = Encoding.ASCII.GetString(responseBuffer, 0, numberOfBytesReceived);
                (String responseHeader, int contentLength) = parseResponse(response);
                
                Console.WriteLine("===================================================");
                Console.WriteLine("Response header:");
                Console.WriteLine(responseHeader);
                Console.WriteLine("Obtained content length: {0}", contentLength);
                Console.WriteLine("===================================================");
                
                if (numberOfBytesReceived == 0)
                {
                    socket.BeginReceive(responseBuffer, 0, responseBuffer.Length,
                        0, ResponseCallback, new Tuple<Socket, byte[]>(socket, responseBuffer));
                }
                else
                {
                    Console.WriteLine("Currently receiving the response...");
                    Console.WriteLine("This is the received message: {0}", response);
                    Console.WriteLine("Received the response: {0} bytes", numberOfBytesReceived);
                }
            }
            catch (Exception exception)
            {
                Console.WriteLine("An exception has occured: {0}", exception.ToString());
            }
        }

        private void HandleConnection(IAsyncResult asyncResult)
        {
            Console.WriteLine("From handleResponse()");
            (Socket socket, IPAddress ipAddress, String hostName, String fileName) 
                = (Tuple<Socket, IPAddress, String, String>)asyncResult.AsyncState;
            socket.EndConnect(asyncResult);

            String httpHeader = String.Format("GET {0}/ HTTP/1.1\r\nHost: {1}\r\nContent-Length: 0\r\n\r\n", fileName, hostName);
            Console.WriteLine(httpHeader);

            byte[] httpHeaderBuffer = Encoding.ASCII.GetBytes(httpHeader);
            socket.BeginSend(httpHeaderBuffer, 0, httpHeaderBuffer.Length,
                0, RequestSendingCallback, socket);
        }

        public void MakeRequest(String url)
        {
            List<String> urlTokens = url.Split('/').ToList().Where(x => !String.IsNullOrEmpty(x)).ToList();
            String hostName = urlTokens[0], fileName = url.Substring(url.IndexOf("/"));
            
            IPHostEntry dnsResolvedAddress = Dns.GetHostEntry(hostName);
            List<IPAddress> addresses = dnsResolvedAddress.AddressList.ToList();
            IPEndPoint endpoint = new IPEndPoint(dnsResolvedAddress.AddressList[0], 80);
            Socket socket = new Socket(endpoint.Address.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            IAsyncResult asyncResult = socket.BeginConnect(endpoint, HandleConnection, new Tuple<Socket, IPAddress, String, String>(socket, addresses[0], hostName, fileName));
            while (!asyncResult.IsCompleted) { }
            Console.WriteLine("Connection has been established.");
        }

    }
}