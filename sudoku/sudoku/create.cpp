#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "sudoku.h"
int shift[8] = { 3, 6, 1, 4, 7, 2, 5, 8 };  //第一行后移的位置，变成数独矩阵
int first[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };  //第一行后八个数字，排列组合用
int mid[3], end[3];  //中间三行、末尾三行变换的顺序
int flag_mid = 1, flag_end = 1;  //判断中间、末尾处于哪种变换，共6种
int f = 0;  //f = 0时是第一个数独，f = 1时是第二个数独
int sudo[9][9];

void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

//中间和末尾三行的变换
void flag(int f1, int f2) {
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


//排列组合第一行
bool permutation(int* p) {
    //从后往前找，发现后面的数大于前面的数，则停在后一个数
    //若没有以上情况，则证明 8！种排列已排完
    int i = 7;
    while (i > 0 && p[i] < p[i - 1])  i--;
    if (i == 0) return false;

    //从后查到i，查到大于p[i - 1]的最小的数，记入k   
    int k = i;
    for (int j = 7; j >= i; j--) {
        if (p[j] > p[i - 1] && p[j] < p[k]) k = j;
    }
    swap(p[k], p[i - 1]);

    //倒置p[last]到p[i]   
    for (int j = 7, k = i; j > k; j--, k++) {
        swap(p[j], p[k]);
    }
    return true;
}


//把生成的数独写入文件输出
void output(int sudo[9][9], FILE* fp) {
    flag(flag_mid, flag_end);
    char str[18];  //每一行的输出，9个数+空格
    if (f == 1) fprintf(fp, "\n");
    if (f == 0) f = 1;

    //把数独一行一行的写入文件
    for (int i = 0; i < 9; i++) {
        int row = 0;  //判断在变换后下一个要输出的行
        if (i < 3) row = i;
        if (i >= 3 && i <= 5) row = mid[i - 3];
        if (i > 5) row = end[i - 6];
        for (int j = 0; j < 9; j++) {
            str[j * 2] = sudo[row][j] + '0';
            str[j * 2 + 1] = ' ';
        }
        str[17] = '\0';
        fputs(str, fp);
        if (i < 8) fprintf(fp, "\n");
    }

}


//生成n个数独终局并写入文件
void create(int n) {
    FILE* fp = fopen("sudoku.txt", "w");
    memset(mid, 0, sizeof(mid));
    memset(end, 0, sizeof(end));

    //设置第一个数独，让第一行为1 2 3 4 5 6 7 8 9
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == 0)
                sudo[i][j] = j + 1;
            else
                sudo[i][j] = 0;
        }
    }

    //输出n个数独
    for (int i = 0; i < n; i++) {
        if(i != 0) fprintf(fp, "\n");  //每个数独之间空一行

        //36种行交换用完后，使用排列组合第一行的方式生成新数独
        if (flag_mid == 1 && flag_end == 1) { 
            //不是第一个初始化数独，需要先排列组合第一行
            if (i != 0) {
                permutation(first);
                for (int j = 0; j < 8; j++) {
                    sudo[0][j + 1] = first[j];
                }
            }
            //第j行为第一行左移shift[j]，变换出完整的数独
            for (int j = 1; j < 9; j++) {
                for (int k = 0; k < 9; k++) {
                    sudo[j][k] = sudo[0][(k + shift[j - 1]) % 9];
                }
            }
        }
        output(sudo, fp);
        if (flag_mid == 6) {
            flag_mid = 1;
            if (flag_end == 6) {
                flag_end = 1;
            }
            if (flag_end != 6) flag_end++;
        }
        if (flag_mid != 6) flag_mid++;
    }
    fclose(fp);
}