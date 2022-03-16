using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SudokuGui
{
    public class sudoku
    {
        public int[] shift = new int[8] { 3, 6, 1, 4, 7, 2, 5, 8 };  //第一行后移的位置，变成数独矩阵
        //public int[] first = new int[8] { 2, 3, 4, 5, 6, 7, 8, 9 };  //第一行后八个数字，排列组合用
        public int[] mid = new int[3];
        public int[] end = new int[3];  //中间三行、末尾三行变换的顺序
        //public int f = 0;  //f = 0时是第一个数独，f = 1时是第二个数独
        public int[,] sudo = new int[9, 9];  //储存基础数独        
        public int[,] question = new int[9, 9];  //储存经过行变换后用于题目的数独
        public int[,] answer = new int[9, 9];  //储存经过行变换后用于题目的数独答案
        int flag_mid = 1, flag_end = 1;

        public sudoku()
        {

        }

        //中间和末尾三行的变换
        public void flag(int f1, int f2)
        {
            if (f1 == 1) { mid[0] = 3; mid[1] = 4; mid[2] = 5; }
            if (f1 == 2) { mid[0] = 3; mid[1] = 5; mid[2] = 4; }
            if (f1 == 3) { mid[0] = 4; mid[1] = 3; mid[2] = 5; }
            if (f1 == 4) { mid[0] = 4; mid[1] = 5; mid[2] = 3; }
            if (f1 == 5) { mid[0] = 5; mid[1] = 3; mid[2] = 4; }
            if (f1 == 6) { mid[0] = 5; mid[1] = 4; mid[2] = 3; }

            if (f2 == 1) { end[0] = 6; end[1] = 7; end[2] = 8; }
            if (f2 == 2) { end[0] = 6; end[1] = 8; end[2] = 7; }
            if (f2 == 3) { end[0] = 7; end[1] = 6; end[2] = 8; }
            if (f2 == 4) { end[0] = 7; end[1] = 8; end[2] = 6; }
            if (f2 == 5) { end[0] = 8; end[1] = 6; end[2] = 7; }
            if (f2 == 6) { end[0] = 8; end[1] = 7; end[2] = 6; }
        }


        //把生成的数独根据变换写入question[,]，answer[,]
        void output(int flag_mid, int flag_end)
        {
            flag(flag_mid, flag_end);
            for (int i = 0; i < 9; i++)
            {
                //int row = i;
                int row = 0;  //判断在变换后下一个要输出的行
                if (i < 3) row = i;
                if (i >= 3 && i <= 5) row = mid[i - 3];
                if (i > 5) row = end[i - 6];
                for (int j = 0; j < 9; j++)
                {
                    question[i, j] = sudo[row, j];
                    answer[i, j] = sudo[row, j];
                }
            }

            b_blank();
        }

        //给数独题目question[,]挖空
        public void b_blank()
        {
            Random rdm = new Random();
            int blank = rdm.Next(30, 61);  //生成30 - 60 个空

            //9个3X3，每个3X3的小棋盘中挖空不少于2个。
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    int position = rdm.Next(9);   //选择3X3里空的位置
                    int x = i / 3 * 3 + position / 3;
                    int y = i % 3 * 3 + position % 3;

                    //如果这个位置没被挖空，则挖空，反之，再随机一个数
                    if (question[x, y] != 0)   
                    {
                        question[x, y] = 0;
                        blank--;
                    }
                    else
                    {
                        j--;
                        continue;
                    }
                }
            }

            //空还有剩余
            while (blank > 0)  
            {
                int i = rdm.Next(9);
                int j = rdm.Next(9);
                if (question[i, j] != 0)  //没有被挖空
                {
                    question[i, j] = 0;
                    blank--;
                }
            }
        }

        //生成初始数独终局并写入question[,]，answer[,]
        public void create(int[] first)
        {
            //初始化三个数独数组
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    question[i, j] = 0;
                    answer[i, j] = 0;
                    if (i == 0)
                        sudo[i,j] = first[j];
                    else
                        sudo[i,j] = 0;
                }
            }

            //第j行为第一行左移shift[j]，变换出完整的数独
            for (int j = 1; j < 9; j++)
            {
                for (int k = 0; k < 9; k++)
                {
                    sudo[j, k] = sudo[0, ((k + shift[j - 1]) % 9)];
                }
            }          

            Random rand = new Random();
            flag_mid = rand.Next(1, 7);
            flag_end = rand.Next(1, 7);
            output(flag_mid, flag_end);
            //b_blank();
        }









    }


}
