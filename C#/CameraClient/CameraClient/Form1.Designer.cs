namespace CameraClient
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_Start_LinkToServer = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_Start_Disconnect = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.Menu_Start_Receive = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_Start_StopReceive = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.Menu_Start_ExitApp = new System.Windows.Forms.ToolStripMenuItem();
            this.设置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_Set_System = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_Set_Link = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_Set_Save = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_Set_ImgAnalyse = new System.Windows.Forms.ToolStripMenuItem();
            this.帮助ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_Help_About = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Location = new System.Drawing.Point(0, 25);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(925, 670);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.设置ToolStripMenuItem,
            this.帮助ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(925, 25);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Menu_Start_LinkToServer,
            this.Menu_Start_Disconnect,
            this.toolStripSeparator1,
            this.Menu_Start_Receive,
            this.Menu_Start_StopReceive,
            this.toolStripSeparator2,
            this.Menu_Start_ExitApp});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(44, 21);
            this.toolStripMenuItem1.Text = "开始";
            // 
            // Menu_Start_LinkToServer
            // 
            this.Menu_Start_LinkToServer.Name = "Menu_Start_LinkToServer";
            this.Menu_Start_LinkToServer.Size = new System.Drawing.Size(136, 22);
            this.Menu_Start_LinkToServer.Text = "连接服务器";
            this.Menu_Start_LinkToServer.Click += new System.EventHandler(this.Menu_Start_LinkToServer_Click);
            // 
            // Menu_Start_Disconnect
            // 
            this.Menu_Start_Disconnect.Name = "Menu_Start_Disconnect";
            this.Menu_Start_Disconnect.Size = new System.Drawing.Size(136, 22);
            this.Menu_Start_Disconnect.Text = "断开连接";
            this.Menu_Start_Disconnect.Click += new System.EventHandler(this.Menu_Start_Disconnect_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(133, 6);
            // 
            // Menu_Start_Receive
            // 
            this.Menu_Start_Receive.Name = "Menu_Start_Receive";
            this.Menu_Start_Receive.Size = new System.Drawing.Size(136, 22);
            this.Menu_Start_Receive.Text = "开始接收";
            this.Menu_Start_Receive.Click += new System.EventHandler(this.Menu_Start_Receive_Click);
            // 
            // Menu_Start_StopReceive
            // 
            this.Menu_Start_StopReceive.Name = "Menu_Start_StopReceive";
            this.Menu_Start_StopReceive.Size = new System.Drawing.Size(136, 22);
            this.Menu_Start_StopReceive.Text = "暂停接收";
            this.Menu_Start_StopReceive.Click += new System.EventHandler(this.Menu_Start_StopReceive_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(133, 6);
            // 
            // Menu_Start_ExitApp
            // 
            this.Menu_Start_ExitApp.Name = "Menu_Start_ExitApp";
            this.Menu_Start_ExitApp.Size = new System.Drawing.Size(136, 22);
            this.Menu_Start_ExitApp.Text = "退出";
            this.Menu_Start_ExitApp.Click += new System.EventHandler(this.Menu_Start_ExitApp_Click);
            // 
            // 设置ToolStripMenuItem
            // 
            this.设置ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Menu_Set_System,
            this.Menu_Set_Link,
            this.Menu_Set_Save,
            this.Menu_Set_ImgAnalyse});
            this.设置ToolStripMenuItem.Name = "设置ToolStripMenuItem";
            this.设置ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.设置ToolStripMenuItem.Text = "设置";
            // 
            // Menu_Set_System
            // 
            this.Menu_Set_System.Name = "Menu_Set_System";
            this.Menu_Set_System.Size = new System.Drawing.Size(148, 22);
            this.Menu_Set_System.Text = "系统设置";
            this.Menu_Set_System.Click += new System.EventHandler(this.Menu_Set_System_Click);
            // 
            // Menu_Set_Link
            // 
            this.Menu_Set_Link.Name = "Menu_Set_Link";
            this.Menu_Set_Link.Size = new System.Drawing.Size(148, 22);
            this.Menu_Set_Link.Text = "连接设置";
            this.Menu_Set_Link.Click += new System.EventHandler(this.Menu_Set_Link_Click);
            // 
            // Menu_Set_Save
            // 
            this.Menu_Set_Save.Name = "Menu_Set_Save";
            this.Menu_Set_Save.Size = new System.Drawing.Size(148, 22);
            this.Menu_Set_Save.Text = "保存设置";
            this.Menu_Set_Save.Click += new System.EventHandler(this.Menu_Set_Save_Click);
            // 
            // Menu_Set_ImgAnalyse
            // 
            this.Menu_Set_ImgAnalyse.Name = "Menu_Set_ImgAnalyse";
            this.Menu_Set_ImgAnalyse.Size = new System.Drawing.Size(148, 22);
            this.Menu_Set_ImgAnalyse.Text = "图像分析设置";
            this.Menu_Set_ImgAnalyse.Click += new System.EventHandler(this.Menu_Set_ImgAnalyse_Click);
            // 
            // 帮助ToolStripMenuItem
            // 
            this.帮助ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Menu_Help_About});
            this.帮助ToolStripMenuItem.Name = "帮助ToolStripMenuItem";
            this.帮助ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.帮助ToolStripMenuItem.Text = "帮助";
            // 
            // Menu_Help_About
            // 
            this.Menu_Help_About.Name = "Menu_Help_About";
            this.Menu_Help_About.Size = new System.Drawing.Size(100, 22);
            this.Menu_Help_About.Text = "关于";
            this.Menu_Help_About.Click += new System.EventHandler(this.Menu_Help_About_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(925, 695);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem Menu_Start_LinkToServer;
        private System.Windows.Forms.ToolStripMenuItem Menu_Start_Disconnect;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem Menu_Start_Receive;
        private System.Windows.Forms.ToolStripMenuItem Menu_Start_StopReceive;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem Menu_Start_ExitApp;
        private System.Windows.Forms.ToolStripMenuItem 设置ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Menu_Set_System;
        private System.Windows.Forms.ToolStripMenuItem Menu_Set_Link;
        private System.Windows.Forms.ToolStripMenuItem Menu_Set_Save;
        private System.Windows.Forms.ToolStripMenuItem Menu_Set_ImgAnalyse;
        private System.Windows.Forms.ToolStripMenuItem 帮助ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Menu_Help_About;
    }
}

