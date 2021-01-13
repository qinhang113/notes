using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CameraClient
{
    public partial class SystemConfig : Form
    {
        public SystemConfig()
        {
            InitializeComponent();
        }
        protected override void OnLoad(EventArgs e)
        {
            this.button1.PerformClick();
            base.OnLoad(e);
        }
        private void button_Click(object sender, EventArgs e)
        {
            this.panel1.Controls.Clear();
            ConnectConfig connectForm = new ConnectConfig();
            int h1 = connectForm.Height;
            connectForm.Dock = System.Windows.Forms.DockStyle.Fill;
            connectForm.FormBorderStyle = FormBorderStyle.None;
            connectForm.TopLevel = false;
            this.panel1.Controls.Add(connectForm);
            connectForm.Show();

            int h2 = panel1.Height;
            if (h1 > h2)
            {
                panel1.AutoScrollMinSize = new Size(panel1.Width - 20, h1);
            }
        }
    }
}
