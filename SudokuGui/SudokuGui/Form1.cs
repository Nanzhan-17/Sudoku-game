using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SudokuGui
{
    public partial class Form1 : Form
    {
        sudoku sudoku = new sudoku();
        TextBox[,] textbox = new TextBox[9, 9];  //九宫格棋盘
        public int flag_mid = 1, flag_end = 1;  //判断中间、末尾处于哪种变换，共6种
        int[] array = new int[9];  //随机的第一行
        int flag_tips = 0;  //flag_tips == 1，证明用了提示
        public Form1()
        {
            InitializeComponent();
            Init();

            //提交、提示、重新开始按钮不可用
            Submit.Enabled = false;
            Restart.Enabled = false;
            Tips.Enabled = false;

            //初始化计时器
            label_h.Text = "0";
            label_m.Text = "0";
            label_s.Text = "0";
            timer1.Interval = 1000;

            label_tips.Text = "tips：" + "\n\n" + "每使用一次提示" + "\n\n" + "总用时增加五秒";
        }

        private void Txt_KeyPress(object sender, KeyPressEventArgs e)
        {
            //仅能在棋盘上输入空格或者数字1-9
            if (e.KeyChar != 8)
            {
                e.Handled = (e.KeyChar < '1') || (e.KeyChar > '9');
            }
        }

        //初始化整个棋盘
        private void Init()
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    TextBox cell = new TextBox
                    {
                        //设置 9*9 棋盘
                        MaxLength = 1,
                        Top = 8 + i * 50,
                        Left = 80 + j * 45,
                        Width = 40,
                        Height = 40,
                        Visible = true,
                        Tag = i * 9 + j
                    };

                    cell.Font = new Font("宋体", 25);
                    cell.TextAlign = HorizontalAlignment.Center;
                    cell.KeyPress += Txt_KeyPress;
                    textbox[i, j] = cell;
                    this.Controls.Add(cell);
                }
            }

                
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //每点击一次新游戏，都重新开始计时
            label_h.Text = "0";
            label_m.Text = "0";
            label_s.Text = "0";

            //提交、提示、重新开始按钮不可用
            Submit.Enabled = true;
            Restart.Enabled = true;
            Tips.Enabled = true;

            //生成数独第一行1-9随机数，每个数字各不重复
            Random r = new Random();
            for (int i = 0; i < array.Length; i++)
            {
                array[i] = r.Next(1, 10);
                if (i > 0)
                {
                    for (int j = 0; j < i; j++)
                    {
                        if (array[i] == array[j])
                        {
                            i--;
                            break;
                        }
                    }
                }
            }

            /*  Debug: 测试第一行是否可以随机生成
            for(int i = 0; i < 9; i++)
            {
                textbox[0, i].Text = array[i].ToString();
            }
            */

            //生成数独题目并挖空，将题目填入txetbox
            sudoku.create(array);         
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    textbox[i, j].Text = "";  //每点击一次新游戏，都要归零每一个空格
                    textbox[i, j].BackColor = Color.White;
                    textbox[i, j].ReadOnly = false;
                    if (sudoku.question[i, j] != 0)
                    {
                        textbox[i, j].Text = sudoku.question[i, j].ToString();
                        textbox[i, j].ReadOnly = true;
                        textbox[i, j].BackColor = Color.FromArgb(220,220,220);
                    }
                }
            }

            //开始新游戏时，重新开始计时
            if (timer1.Enabled == true)
            {
                timer1.Enabled = false;
                label_h.Text = "0";
                label_m.Text = "0";
                label_s.Text = "0";

            }
                
            timer1.Enabled = true;

        }

        private void Quit_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void Submit_Click(object sender, EventArgs e)
        {
            int f_flag = 0;  //flag == 0 为数独填满，flag == 1为未填满，flag == 2为出现错误
            for (int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    if(textbox[i, j].Text == "")
                    {
                        MessageBox.Show("您还未完成数独！", "提示");
                        f_flag = 1;
                        break;
                    }
                }
                if (f_flag == 1) break;
            }
            if (f_flag == 0)
            {
                for (int i = 0; i < 9; i++)
                {
                    for (int j = 0; j < 9; j++)
                    {
                        if (textbox[i, j].Text != sudoku.answer[i,j].ToString())
                        {
                            MessageBox.Show("很遗憾，您的数独含有错误！", "提示");
                            f_flag = 2;
                            break;
                        }
                    }
                    if (f_flag == 2) break;
                }
            }
            if (f_flag == 0)
            {
                //完成数独后停止计时
                timer1.Enabled = false;
                string hhour = label_h.Text;
                string mmin = label_m.Text;
                string ssec = label_s.Text;
                string str = "恭喜您，成功完成数独，您花费的时间为" + hhour + "时" + mmin + "分" + ssec + "秒！";
                MessageBox.Show(str, "恭喜");

            }
        }

        private void Tips_Click(object sender, EventArgs e)
        {
            flag_tips = 1;
            int e_flag = 0;  //e_flag == 1 为提示完毕
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    //有空的地方则填上
                    if(textbox[i, j].Text == "")
                    {
                        textbox[i, j].Text = sudoku.answer[i, j].ToString();
                        e_flag = 1;
                        break;
                    }

                    //有错误则提示
                    if(textbox[i, j].Text != "" && textbox[i, j].Text != sudoku.answer[i, j].ToString())
                    {
                        textbox[i, j].BackColor = Color.Red;
                        MessageBox.Show("标红地方填写错误！", "提示");
                        textbox[i, j].BackColor = Color.White;
                        e_flag = 1;
                        break;
                    }
                }
                if (e_flag == 1) break;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            int hour = Int32.Parse(label_h.Text);
            int min = Int32.Parse(label_m.Text);
            int sec = Int32.Parse(label_s.Text);
            sec++;
            
            //如果使用了提示，时间额外加5s
            if (flag_tips == 1)
            {
                sec += 5;
                flag_tips = 0;
            }

            //计算小时
            if (min == 60)
            {
                hour++;
                label_h.Text = hour.ToString();
                label_m.Text = "0";
                if (hour == 100)
                {
                    timer1.Enabled = false;
                    MessageBox.Show("计时器已达到上限", "提示");
                    return;
                }
            }
            //计算分钟
            if (sec >= 60)
            {
                min++;
                label_m.Text = min.ToString();
            }
            //计算秒
            sec = sec % 60;
            label_s.Text = sec.ToString();

        }

        private void Restart_Click(object sender, EventArgs e)
        {
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    if (textbox[i, j].ReadOnly == false) textbox[i, j].Text = "";
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.Text = "数独游戏";
        }
    }
}
