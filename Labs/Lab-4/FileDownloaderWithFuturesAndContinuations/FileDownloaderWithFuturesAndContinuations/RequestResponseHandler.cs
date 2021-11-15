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
            ConnectionState connectionState = (ConnectionState) asyncResult.AsyncState;
            connectionState.Socket.EndSend(asyncResult);
            Console.WriteLine("Sent the message.");

            connectionState.Socket.BeginReceive(connectionState.Buffer, 0, connectionState.Buffer.Length,
                0, ResponseCallback, connectionState);
        }
        
        private void ResponseCallback(IAsyncResult asyncResult)
        {
            Console.WriteLine("In the ResponseCallback...");
            ConnectionState connectionState = (ConnectionState) asyncResult.AsyncState;

            try
            {
                int numberOfBytesReceived = connectionState.Socket.EndReceive(asyncResult);
                String response = Encoding.ASCII.GetString(connectionState.Buffer, 0, numberOfBytesReceived);
                connectionState.Response += response;
                
                Console.WriteLine("Accumulated response:");
                Console.WriteLine(connectionState.Response);

                if (connectionState.Response.Contains("\r\n\r\n"))
                {
                    Console.WriteLine("========= The response contains rnrn pattern =========");
                    (String responseHeader, int contentLength) = parseResponse(connectionState.Response);

                    int patternIndex = connectionState.Response.IndexOf("\r\n\r\n");
                    Console.WriteLine("RNRN pattern index:");
                    Console.WriteLine(patternIndex);
                    Console.WriteLine("===================================================");
                    Console.WriteLine("Response header:");
                    Console.WriteLine(responseHeader);
                    Console.WriteLine("Obtained content length: {0}", contentLength);
                    Console.WriteLine("===================================================");
                    Console.WriteLine("Currently receiving the response...");
                    Console.WriteLine("This is the received message: {0}", response);
                    Console.WriteLine("Received the response: {0} bytes", numberOfBytesReceived);
                }
                else
                {
                    Console.WriteLine("========= The response doesn't contain rnrn pattern yet =========");
                    connectionState.Socket.BeginReceive(connectionState.Buffer, 0, connectionState.Buffer.Length,
                0, ResponseCallback, connectionState);
                }
            }
            catch (Exception exception)
            {
                Console.WriteLine("An exception has occured: {0}", exception.ToString());
            }
        }

        private void HandleConnection(IAsyncResult asyncResult)
        {
            
            ConnectionState connectionState = (ConnectionState)asyncResult.AsyncState;
            connectionState.Socket.EndConnect(asyncResult);

            String httpHeader = String.Format("GET {0}/ HTTP/1.1\r\nHost: {1}\r\nContent-Length: 0\r\n\r\n", connectionState.Resource, connectionState.Host);
            Console.WriteLine(httpHeader);

            byte[] httpHeaderBuffer = Encoding.ASCII.GetBytes(httpHeader);
            connectionState.Socket.BeginSend(httpHeaderBuffer, 0, httpHeaderBuffer.Length,
                0, RequestSendingCallback, connectionState);
        }

        public void MakeRequest(String url)
        {
            List<String> urlTokens = url.Split('/').ToList().Where(x => !String.IsNullOrEmpty(x)).ToList();
            ConnectionState connectionState = new ConnectionState();

            connectionState.Host = urlTokens[0];
            IPHostEntry dnsResolvedAddress = Dns.GetHostEntry(connectionState.Host);
            List<IPAddress> addresses = dnsResolvedAddress.AddressList.ToList();
            IPEndPoint endpoint = new IPEndPoint(dnsResolvedAddress.AddressList[0], 80);
            connectionState.Buffer = new byte[128];
            connectionState.Socket = new Socket(endpoint.Address.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            connectionState.Host = urlTokens[0];
            connectionState.Resource = url.Substring(url.IndexOf("/"));
            connectionState.Address = addresses[0];
            
            IAsyncResult asyncResult = connectionState.Socket.BeginConnect(endpoint, HandleConnection, connectionState);
            while (!asyncResult.IsCompleted) { }
            Console.WriteLine("Connection has been established.");
        }

    }
}