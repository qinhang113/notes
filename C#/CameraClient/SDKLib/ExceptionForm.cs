using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SDKLib
{
    public partial class ExceptionForm : Form
    {
        public ExceptionForm()
        {
            InitializeComponent();
            msgLabel.Text = "异常";
        }

        public void SetModal(Exception e)
        {
            if (e != null)
            {
                string str = String.Format("[{0}] {1}\r\n{2}\r\n{3}",
                    DateTime.Now.ToString(), e.GetType().Name, e.Message, e.StackTrace);
                textBox.Text = str;
                textBox.Select(textBox.TextLength, 0);
            }
            ShowDialog();
        }
    }
}
