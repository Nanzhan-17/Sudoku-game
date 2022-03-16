
namespace SudokuGui
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
            this.components = new System.ComponentModel.Container();
            this.Start = new System.Windows.Forms.Button();
            this.Quit = new System.Windows.Forms.Button();
            this.Tips = new System.Windows.Forms.Button();
            this.Submit = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label_h = new System.Windows.Forms.Label();
            this.label_m = new System.Windows.Forms.Label();
            this.label_s = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.Restart = new System.Windows.Forms.Button();
            this.label_tips = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // Start
            // 
            this.Start.Location = new System.Drawing.Point(789, 109);
            this.Start.Name = "Start";
            this.Start.Size = new System.Drawing.Size(139, 59);
            this.Start.TabIndex = 0;
            this.Start.Text = "新游戏";
            this.Start.UseVisualStyleBackColor = true;
            this.Start.Click += new System.EventHandler(this.button1_Click);
            // 
            // Quit
            // 
            this.Quit.Location = new System.Drawing.Point(789, 471);
            this.Quit.Name = "Quit";
            this.Quit.Size = new System.Drawing.Size(139, 59);
            this.Quit.TabIndex = 1;
            this.Quit.Text = "退出";
            this.Quit.UseVisualStyleBackColor = true;
            this.Quit.Click += new System.EventHandler(this.Quit_Click);
            // 
            // Tips
            // 
            this.Tips.Location = new System.Drawing.Point(789, 288);
            this.Tips.Name = "Tips";
            this.Tips.Size = new System.Drawing.Size(139, 59);
            this.Tips.TabIndex = 2;
            this.Tips.Text = "提示";
            this.Tips.UseVisualStyleBackColor = true;
            this.Tips.Click += new System.EventHandler(this.Tips_Click);
            // 
            // Submit
            // 
            this.Submit.Location = new System.Drawing.Point(789, 380);
            this.Submit.Name = "Submit";
            this.Submit.Size = new System.Drawing.Size(139, 59);
            this.Submit.TabIndex = 3;
            this.Submit.Text = "提交";
            this.Submit.UseVisualStyleBackColor = true;
            this.Submit.Click += new System.EventHandler(this.Submit_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label_h
            // 
            this.label_h.AutoSize = true;
            this.label_h.Location = new System.Drawing.Point(782, 56);
            this.label_h.Name = "label_h";
            this.label_h.Size = new System.Drawing.Size(17, 18);
            this.label_h.TabIndex = 4;
            this.label_h.Text = "0";
            // 
            // label_m
            // 
            this.label_m.AutoSize = true;
            this.label_m.Location = new System.Drawing.Point(854, 56);
            this.label_m.Name = "label_m";
            this.label_m.Size = new System.Drawing.Size(17, 18);
            this.label_m.TabIndex = 5;
            this.label_m.Text = "0";
            // 
            // label_s
            // 
            this.label_s.AutoSize = true;
            this.label_s.Location = new System.Drawing.Point(925, 56);
            this.label_s.Name = "label_s";
            this.label_s.Size = new System.Drawing.Size(17, 18);
            this.label_s.TabIndex = 6;
            this.label_s.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(818, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 18);
            this.label1.TabIndex = 7;
            this.label1.Text = ":";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(891, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(17, 18);
            this.label2.TabIndex = 8;
            this.label2.Text = ":";
            // 
            // Restart
            // 
            this.Restart.Location = new System.Drawing.Point(789, 197);
            this.Restart.Name = "Restart";
            this.Restart.Size = new System.Drawing.Size(139, 59);
            this.Restart.TabIndex = 9;
            this.Restart.Text = "重新开始";
            this.Restart.UseVisualStyleBackColor = true;
            this.Restart.Click += new System.EventHandler(this.Restart_Click);
            // 
            // label_tips
            // 
            this.label_tips.AutoSize = true;
            this.label_tips.Location = new System.Drawing.Point(786, 560);
            this.label_tips.Name = "label_tips";
            this.label_tips.Size = new System.Drawing.Size(62, 18);
            this.label_tips.TabIndex = 10;
            this.label_tips.Text = "tips：";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1014, 699);
            this.Controls.Add(this.label_tips);
            this.Controls.Add(this.Restart);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label_s);
            this.Controls.Add(this.label_m);
            this.Controls.Add(this.label_h);
            this.Controls.Add(this.Submit);
            this.Controls.Add(this.Tips);
            this.Controls.Add(this.Quit);
            this.Controls.Add(this.Start);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.Button Quit;
        private System.Windows.Forms.Button Tips;
        private System.Windows.Forms.Button Submit;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label_h;
        private System.Windows.Forms.Label label_m;
        private System.Windows.Forms.Label label_s;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button Restart;
        private System.Windows.Forms.Label label_tips;
    }
}

