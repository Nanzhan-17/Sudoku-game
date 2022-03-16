#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "sudoku.h"
int s_sudo[9][9];
int blank[9];  //记录每一行空白的个数
int isOK = 0;  //isOK == 1，则整个数独求解完毕
int num_sudo = 0;  //记录输入到输出文件的是第几个数独

//判断行、列、九宫格是否有重复
bool isValid(int row, int col) {
    int num = s_sudo[row][col];
    for (int i = 0; i < 9; i++) {
        if (s_sudo[i][col] == num && i != row)return false;
    }
    for (int j = 0; j < 9; j++) {
        if (s_sudo[row][j] == num && j != col)return false;
    }
    int x = (row / 3) * 3;
    int y = (col / 3) * 3;
    for (int i = x; i < x + 3; i++) {
        for (int j = y; j < y + 3; j++) {
            if (s_sudo[i][j] == num && i != row && j != col)return false;
        }
    }
    return true;
}

//求解数独的dfs
void resolve(int row, int col) {
    if (isOK == 1)return;
    blank[row]--;
    for (int i = 1; i < 10; i++) {
        s_sudo[row][col] = i;
        if (isValid(row, col)) {
            //这一行还有空格
            if (blank[row] > 0) {
                int j;
                for (j = 0; j < 9; j++) {
                    if (s_sudo[row][j] == 0)break;
                }
                resolve(row, j);
            }

            //这一行没有空格了
            else {
                int next_row = -1;
                for (int k = 0; k < 9; k++) {
                    if (blank[k] == 0)continue;
                    if (next_row == -1)next_row = k;
                    if (blank[k] < blank[next_row])next_row = k;
                }
                if (next_row == -1) {
                    isOK = 1;
                    return;
                }
                int j;
                for (j = 0; j < 9; j++) {
                    if (s_sudo[next_row][j] == 0)break;
                }
                resolve(next_row, j);
            }
            if (isOK == 1)return;
        }
    }
    //9个数字都尝试完，没有符合要求的，证明上一个数字填错了，返回
    s_sudo[row][col] = 0;
    blank[row]++;
    return;
}

//把求解的数独写入文件输出
void s_output() {
    FILE* fp;
    if (num_sudo == 0) {
        fp = fopen("sudoku.txt", "w");
        num_sudo++;
    }
    else {
        fp = fopen("sudoku.txt", "a+");
        fprintf(fp, "\n\n");
        num_sudo++;
    }
    char str[18];  //每一行的输出，9个数+空格
    //把数独一行一行的写入文件
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            str[j * 2] = s_sudo[i][j] + '0';
            str[j * 2 + 1] = ' ';
        }
        str[17] = '\0';
        fputs(str, fp);
        if (i < 8) fprintf(fp, "\n");
    }
    fclose(fp);
}

//依次读取每个数独并求解
void solve(const char* txt) {
	FILE* fp = fopen(txt, "r");
    

    //初始化s_sudo[9][9]
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            s_sudo[i][j] = 0;
        }
    }

    //读取需要求解的数独文件并求解
	while (!feof(fp))
	{
        int flag = 0;
        char str[25];
        memset(blank, 0, sizeof(blank));
        for (int i = 0; i < 9; i++) {
            fgets(str, 25, fp);  //str[25]储存文件的每一行
            if (str[0] < '0' || str[0]>'9') {
                flag = 1;
                break;
            }
            int k = 0;
            //把数独以int型存入s_sudo[9][9]
            for (int j = 0; j < 30; j++) {
                if (str[j] >= '0' && str[j] <= '9') {
                    //printf("hsuashu\n");
                    s_sudo[i][k] = str[j] - '0';
                    if (s_sudo[i][k] == 0)  blank[i]++;  //记录每一行空白的个数
                    k++;
                }
                if (k == 9)break;
            }
        }
        if (flag == 1)continue;  //str读到了不含数独的回车行

        /*  debug:  blank数组是否正确
        for (int i = 0; i < 9; i++) {
            printf("%d  ", blank[i]);
        }
        printf("\n");
        */

        //找到空白最少且不为0的一行，从这一行开始算起
        int min_row = -1;
        for (int i = 0; i < 9; i++) {
            if (blank[i] == 0)continue;
            if (min_row == -1)min_row = i;
            if (blank[i] < blank[min_row])min_row = i;
        }

        /*  debug:  输出的最小行是否正确
        printf("dee: %d\n", min_row); 
        */

        //找到为0的那一列
        int col = -1;
        for (int j = 0; j < 9; j++) {
            if (s_sudo[min_row][j] == 0) {
                col = j;
                break;
            }
        }
        if (min_row != -1) resolve(min_row, col);
        s_output();
        isOK = 0;
	}
    fclose(fp);
    return;
}