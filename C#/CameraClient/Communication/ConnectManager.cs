using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Communication
{
    public class ConnectManager
    {
        internal static ConnectManager _manager = new ConnectManager();
        private static TcpConnect tcp = null;
        private string strSeverIP = null;
        private int intPort = 8888;

        private event Action<Image> _event = null;
        public static bool IsConnected { get { return tcp == null ? false : tcp.IsConnected; } }

        public static string IP
        {
            set { _manager.strSeverIP = value; }
            get { return _manager.strSeverIP; }
        }
        public static int Port
        {
            set { _manager.intPort = value; }
            get { return _manager.intPort; }
        }

        public static void Initialize()
        {
            tcp = new TcpConnect();
            tcp.ReciveDataChange += new TcpConnect.ReciveDataHandler(_manager.GetImg);
            _manager.ReadSettingFromFile();
        }

        public static void Release()
        {
            if (tcp != null)
            {
                if(tcp.IsConnected)
                    tcp.DisConnect();
            }
        }

        public static bool WriteSettingToFile()
        {
            string path = @"./config/setting.ini";
            StreamWriter sw;
            if (!File.Exists(path))
            {
                sw = File.CreateText(path);
            }
            else
            {
                sw = new StreamWriter(path);
            }
            sw.WriteLine("server={0}", _manager.strSeverIP);
            sw.WriteLine("port={0}", _manager.intPort);
            sw.Close();

            return true;
        }
        private bool ReadSettingFromFile()
        {
            string path = @"./config/setting.ini"; 
            if (!File.Exists(path))
            {
                using (StreamWriter sw = File.CreateText(path))
                {
                    sw.WriteLine("server=127.0.0.1");
                    sw.WriteLine("port=8081");
                    sw.Close();
                }
                return false;
            }
            else
            {
                using (StreamReader sr = File.OpenText(path))
                {
                    int index = 0;
                    string s;
                    while ((s = sr.ReadLine()) != null)
                    {
                        string[] value = s.Split('=');
                        if (value.Length > 1)
                        {
                            if(value[0] == "server")
                            {
                                strSeverIP = value[1];
                            }
                            else if(value[0] == "port")
                            {
                                intPort = Convert.ToInt32(value[1]);
                            }
                            else
                            {

                            }
                        }
                        index++;
                    }
                    sr.Close();
                }
            }
            return true;
        }

        public static bool ConnectToServer(string ip = null, int port = 0)
        {
            if (ip == null)
            {
                ip = _manager.strSeverIP;
            }
            if (port == 0)
            {
                port = _manager.intPort;
            }
            if (tcp.Connect(ip, port))
            {
                _manager.strSeverIP = ip;
                _manager.intPort = port;
                WriteSettingToFile();
                return true;
            }
            return false;
        }

        public static void DisConnect()
        {
            if (tcp == null)
            {
                return ;
            }
            tcp.DisConnect();
        }

        public static bool StartRead()
        {
            if (tcp == null)
            {
                return false;
            }
            return tcp.StartRead();
        }
        public static void StopRead()
        {
            if (tcp == null)
            {
                return;
            }
            tcp.StopRead();
        }

        public void GetImg(object sender, Image img)
        {
            //TransmitHandler(this, img);
            _event.Invoke(img);
        }

        public static void SetEvent(Action<Image> e)
        {
            _manager._event = e;
        }
    }
}
