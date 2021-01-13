using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using Communication;

namespace CameraClient
{
    public partial class ConnectConfig : Form
    {
        public ConnectConfig()
        {
            InitializeComponent();

            this.IpTextBox.Text = ConnectManager.IP;
            this.PortTextBox.Text = ConnectManager.Port.ToString();
        }

        private void Connect_Click(object sender, EventArgs e)
        {
            string ipstr = this.IpTextBox.Text;
            int port = Convert.ToInt32(this.PortTextBox.Text);

            if (ConnectManager.IsConnected)
            {
                if (MessageBox.Show(this, "当前已连接至服务器，是否断开连接使用新连接?", "WARNNING", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) == DialogResult.OK)
                {
                    ConnectManager.DisConnect();
                }
                else
                {
                    return;
                }
            }
            else
            {
                if (ConnectManager.ConnectToServer(ipstr, port))
                {
                    MessageBox.Show("连接成功!");
                }
                else
                {
                    MessageBox.Show("连接失败!");
                }
            }
        }
    }
}
