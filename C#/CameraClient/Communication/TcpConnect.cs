using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Data;
using System.IO;
using System.Drawing;
using SDKLib;

namespace Communication
{
    internal class TcpConnect
    {
        private const int MaxDataSize = 3147274;
        private bool CloseThread = false;
        private TcpClient client = null;
        public ManualResetEvent connectDone = new ManualResetEvent(false);

        public delegate void ReciveDataHandler(object sender, Image e);
        public event ReciveDataHandler ReciveDataChange;

        public bool IsConnected { get { return client == null ? false : client.Connected; } }

        public TcpConnect()
        {
        }
        ~TcpConnect()
        {
            DisConnect();
        }
        public bool Connect(string host,int port)
        {
            client = new TcpClient();
            client.ReceiveTimeout = 100;
            client.SendTimeout = 100;
            connectDone.Reset();
            client.BeginConnect(host, port, new AsyncCallback(AsyncConnect), client); 
            
            connectDone.WaitOne();
            if ((client != null) && (client.Connected))
            {
                //workStream = client.GetStream();
                //AsyncRead(client);
                return true;
            }
            return false;
        }
        private void ReadThread()
        {
            bool isOneRateOver = false;
            int w = 0;
            int h = 0;

            byte[] buffer = new byte[MaxDataSize]; 
            while (client.Connected && !CloseThread)
            {
                NetworkStream stream = client.GetStream();
                if (stream.CanRead)
                {
                    if (!isOneRateOver)
                    {
                        try
                        {
                            int len = stream.Read(buffer, 0, 4);
                            if(len == 4)
                            {
                                h = (buffer[0] << 8) + buffer[1];
                                w = (buffer[2] << 8) + buffer[3];
                                isOneRateOver = true;
                            }
                            else
                            {
                                break;
                            }
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine(e.ToString());
                        }
                    }
                    else
                    {
                        try
                        {
                            int imgSize = h * w * 3;
                            int len = stream.Read(buffer, 0, imgSize);
                            if (len > 0)
                            {
                                byte[] dd = new byte[len];
                                Array.Copy(buffer, 0, dd, 0, len);
                                Image img = AddHeader(dd, w, h);
                                ReciveDataChange(this, img);
                                isOneRateOver = false;
                            }
                            else
                            {
                                break;
                            }
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine(e.ToString());
                        }
                    }
                }
                Thread.Sleep(10);
            }
        }

        public bool StartRead()
        {
            if(client.Connected)
            {
                ThreadStart ts = new ThreadStart(ReadThread);
                Thread readThread = new Thread(ts);
                readThread.Start();
                return true;
            }
            return false;
        }
        public void StopRead()
        {
            CloseThread = true;
        }
        private void AsyncConnect(IAsyncResult iar)
        {
            connectDone.Set();
            try
            {
                TcpClient client = (TcpClient)iar.AsyncState;
                //
                client.EndConnect(iar);
                Console.WriteLine("与服务器{0}连接成功", client.Client.RemoteEndPoint);
            }
            catch (Exception e)
            {
                Framework.ShowException(e);
            }
            finally
            {

            }
        }
        public void DisConnect()
        {
            if ((client != null) && (client.Connected))
            {
                client.Close();
            }
        }
        public bool GetConnect()
        {
            return client != null ? client.Connected : false;
        }
        private Bitmap AddHeader(byte[] imageDataDetails ,int width, int heigth)
        {
            Bitmap bitmap = null;
            int length = imageDataDetails.GetLength(0);
            using (MemoryStream stream = new MemoryStream(length + 54))//为头腾出54个长度的空间
            {
                byte[] buffer = new byte[4];
                buffer[0] = 0x42;//Bitmap固定常数
                buffer[1] = 0x4d;//Bitmap固定常数
                stream.Write(buffer, 0, 2);//先写入头的前两个字节

                byte[] bytes = BitConverter.GetBytes(length + 54);
                stream.Write(bytes, 0, 4);//把这个长度写入头中去
                buffer[0] = 0;
                buffer[1] = 0;
                buffer[2] = 0;
                buffer[3] = 0;
                stream.Write(buffer, 0, 4);//在写入4个字节长度的数据到头中去
                int num2 = 0x36;//Bitmap固定常数
                bytes = BitConverter.GetBytes(num2);
                stream.Write(bytes, 0, 4);

                int num3 = 0x28;//继续写40个字节
                bytes = BitConverter.GetBytes(num3);
                stream.Write(bytes, 0, 4);

                int num4 = width;//写入宽度
                bytes = BitConverter.GetBytes(num4);
                stream.Write(bytes, 0, 4);

                int num5 = heigth;//写入高度
                bytes = BitConverter.GetBytes(num5);
                stream.Write(bytes, 0, 4);

                byte[] buffer2 = { 0x01, 0x00 };//0x01,0x00
                stream.Write(buffer2, 0, 2);

                short num6 = 0x18;//24位位图
                bytes = BitConverter.GetBytes(num6);
                stream.Write(bytes, 0, 2);

                int num7 = 0;//BI_RGB， 说明本图像不压缩
                bytes = BitConverter.GetBytes(num7);
                stream.Write(bytes, 0, 4);

                bytes = BitConverter.GetBytes(length);//写入图像大小
                stream.Write(bytes, 0, 4);

                int placeholder = 0;
                bytes = BitConverter.GetBytes(placeholder);//
                for (int i=0; i<4; i++)
                {
                    stream.Write(bytes, 0, 4);
                }

                stream.Write(imageDataDetails, 0, length);//把实际的图像数据全部追加到头的后面

                //FileStream fs = new FileStream(@"E://1.bmp", FileMode.Create);
                //fs.Write(stream.GetBuffer(), 0, length + 54);
                bitmap = new Bitmap(stream);//用内存流构造出一幅bitmap的图片
                bitmap.RotateFlip(RotateFlipType.Rotate180FlipX);
                //fs.Close();
                stream.Close();
                //writefile = true;
                return bitmap;//最后就得到了我们想要的图片了
            }
        }
    }
}
