
namespace SDKLib
{
    partial class ExceptionForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox = new System.Windows.Forms.TextBox();
            this.msgLabel = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // textBox
            // 
            this.textBox.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox.CausesValidation = false;
            this.textBox.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.textBox.Location = new System.Drawing.Point(0, 52);
            this.textBox.Multiline = true;
            this.textBox.Name = "textBox";
            this.textBox.ReadOnly = true;
            this.textBox.Size = new System.Drawing.Size(395, 158);
            this.textBox.TabIndex = 0;
            // 
            // msgLabel
            // 
            this.msgLabel.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.msgLabel.AutoSize = true;
            this.msgLabel.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.msgLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.msgLabel.Location = new System.Drawing.Point(80, 21);
            this.msgLabel.Name = "msgLabel";
            this.msgLabel.Size = new System.Drawing.Size(68, 12);
            this.msgLabel.TabIndex = 1;
            this.msgLabel.Text = "Exception";
            this.msgLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::SDKLib.Properties.Resources.Exception;
            this.pictureBox1.Location = new System.Drawing.Point(12, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(48, 48);
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // ExceptionForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(395, 210);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.msgLabel);
            this.Controls.Add(this.textBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ExceptionForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Exception";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox;
        private System.Windows.Forms.Label msgLabel;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}