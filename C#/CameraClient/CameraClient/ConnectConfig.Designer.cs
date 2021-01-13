namespace CameraClient
{
    partial class ConnectConfig
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
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.Connect = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.IpTextBox = new System.Windows.Forms.TextBox();
            this.PortTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(362, 269);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(36, 36);
            this.pictureBox1.TabIndex = 4;
            this.pictureBox1.TabStop = false;
            // 
            // Connect
            // 
            this.Connect.Location = new System.Drawing.Point(251, 271);
            this.Connect.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Connect.Name = "Connect";
            this.Connect.Size = new System.Drawing.Size(88, 32);
            this.Connect.TabIndex = 5;
            this.Connect.Text = "连接";
            this.Connect.UseVisualStyleBackColor = true;
            this.Connect.Click += new System.EventHandler(this.Connect_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(150, 109);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 19);
            this.label1.TabIndex = 6;
            this.label1.Text = "服务器IP:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(150, 185);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 19);
            this.label2.TabIndex = 6;
            this.label2.Text = "端口号:";
            // 
            // IpTextBox
            // 
            this.IpTextBox.Location = new System.Drawing.Point(225, 109);
            this.IpTextBox.Name = "IpTextBox";
            this.IpTextBox.Size = new System.Drawing.Size(114, 25);
            this.IpTextBox.TabIndex = 7;
            // 
            // PortTextBox
            // 
            this.PortTextBox.Location = new System.Drawing.Point(225, 185);
            this.PortTextBox.Name = "PortTextBox";
            this.PortTextBox.Size = new System.Drawing.Size(114, 25);
            this.PortTextBox.TabIndex = 7;
            // 
            // ConnectConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 19F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(530, 405);
            this.Controls.Add(this.PortTextBox);
            this.Controls.Add(this.IpTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Connect);
            this.Controls.Add(this.pictureBox1);
            this.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "ConnectConfig";
            this.Text = "ConnectConfig";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button Connect;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox IpTextBox;
        private System.Windows.Forms.TextBox PortTextBox;
    }
}