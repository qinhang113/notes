using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SDKLib;
using Communication;
namespace CameraClient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            ConnectManager.Initialize();
            ConnectManager.SetEvent(ImageChanged);
            Framework.Initialize(Application.StartupPath);
        }

        protected void ImageChanged(Image img)
        {
            pictureBox1.Image = img;
        }

        protected override void OnClosed(EventArgs e)
        {
            ConnectManager.Release();
            Framework.Release();
            base.OnClosed(e);
        }

        private void Menu_Start_LinkToServer_Click(object sender, EventArgs e)
        {
            if (!ConnectManager.ConnectToServer())
            {
                MessageBox.Show(this, "连接服务器失败！", "WARNNING", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                Logger.LogError("连接失败!");
            }
            else
            {
                MessageBox.Show(this, "连接服务器成功！", "SUCCEED", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void Menu_Start_Disconnect_Click(object sender, EventArgs e)
        {

        }

        private void Menu_Start_Receive_Click(object sender, EventArgs e)
        {
            ConnectManager.StartRead();
            //string path = @".//test.bmp";
            //FileStream fs = new FileStream(path, FileMode.Open);//可以是其他重载方法 
            //byte[] byData = new byte[fs.Length];
            //fs.Read(byData, 0, byData.Length);
            //fs.Close();

            //MemoryStream ms = new MemoryStream(byData);
            //Image img = Image.FromStream(ms);
            //pictureBox1.Image = img;
        }

        private void Menu_Start_StopReceive_Click(object sender, EventArgs e)
        {
            ConnectManager.StopRead();
        }

        private void Menu_Start_ExitApp_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        //系统设置
        private void Menu_Set_System_Click(object sender, EventArgs e)
        {
            SystemConfig config = new SystemConfig();
            config.ShowDialog();
        }
        //连接设置
        private void Menu_Set_Link_Click(object sender, EventArgs e)
        {

        }
        //保存设置
        private void Menu_Set_Save_Click(object sender, EventArgs e)
        {

        }
        //图像分析设置
        private void Menu_Set_ImgAnalyse_Click(object sender, EventArgs e)
        {

        }
        //关于
        private void Menu_Help_About_Click(object sender, EventArgs e)
        {

        }
    }
}
