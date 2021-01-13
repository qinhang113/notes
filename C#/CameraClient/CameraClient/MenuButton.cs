using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CameraClient
{
    class MenuButton : System.Windows.Forms.Button
    {
        private static int btnId;

        private Color backColor;
        public MenuButton()
        {
            backColor = Color.FromArgb(0xf0, 0xf0, 0xf0);
            ForeColor = Color.Black;
        }
        protected override void OnPaint(PaintEventArgs pevent)
        {
            Graphics g = pevent.Graphics;
            Rectangle myRec;
            myRec = new Rectangle(0, 0, Width, Height);

            SolidBrush b = new SolidBrush(backColor);
            g.FillRectangle(b, myRec);
            if (btnId == this.GetHashCode())
            {
                Rectangle tag = new Rectangle(0, Height / 4, 5, Height / 2);
                g.FillRectangle(new SolidBrush(Color.FromArgb(0, 120, 215)), tag);
            }

            SolidBrush txtbrush = new SolidBrush(ForeColor);
            StringFormat stringFormat = new StringFormat();
            stringFormat.LineAlignment = StringAlignment.Center;
            stringFormat.Alignment = StringAlignment.Center;

            g.DrawString(Text, Font, txtbrush, new Rectangle(0, 0, Width, Height), stringFormat);
            //g.Dispose();
        }
        protected override void OnMouseEnter(EventArgs e)
        {
            backColor = Color.LightGray;
            Invalidate();
        }
        protected override void OnMouseLeave(EventArgs e)
        {
            backColor = Color.FromArgb(0xf0, 0xf0, 0xf0);
            Invalidate();
        }
        protected override void OnClick(EventArgs e)
        {
            int oldId = btnId;
            if (oldId != 0)
            {
                foreach (Control ct in Parent.Controls)
                {
                    if (ct.GetHashCode() == oldId)
                        ct.Invalidate();
                }
            }

            btnId = this.GetHashCode();
            Invalidate();
            base.OnClick(e);
        }
    }
}
