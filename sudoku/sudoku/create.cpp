#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "sudoku.h"
int shift[8] = { 3, 6, 1, 4, 7, 2, 5, 8 };  //��һ�к��Ƶ�λ�ã������������
int first[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };  //��һ�к�˸����֣����������
int mid[3], end[3];  //�м����С�ĩβ���б任��˳��
int flag_mid = 1, flag_end = 1;  //�ж��м䡢ĩβ�������ֱ任����6��
int f = 0;  //f = 0ʱ�ǵ�һ��������f = 1ʱ�ǵڶ�������
int sudo[9][9];

void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

//�м��ĩβ���еı任
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


//������ϵ�һ��
bool permutation(int* p) {
    //�Ӻ���ǰ�ң����ֺ����������ǰ���������ͣ�ں�һ����
    //��û�������������֤�� 8��������������
    int i = 7;
    while (i > 0 && p[i] < p[i - 1])  i--;
    if (i == 0) return false;

    //�Ӻ�鵽i���鵽����p[i - 1]����С����������k   
    int k = i;
    for (int j = 7; j >= i; j--) {
        if (p[j] > p[i - 1] && p[j] < p[k]) k = j;
    }
    swap(p[k], p[i - 1]);

    //����p[last]��p[i]   
    for (int j = 7, k = i; j > k; j--, k++) {
        swap(p[j], p[k]);
    }
    return true;
}


//�����ɵ�����д���ļ����
void output(int sudo[9][9], FILE* fp) {
    flag(flag_mid, flag_end);
    char str[18];  //ÿһ�е������9����+�ո�
    if (f == 1) fprintf(fp, "\n");
    if (f == 0) f = 1;

    //������һ��һ�е�д���ļ�
    for (int i = 0; i < 9; i++) {
        int row = 0;  //�ж��ڱ任����һ��Ҫ�������
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


//����n�������վֲ�д���ļ�
void create(int n) {
    FILE* fp = fopen("sudoku.txt", "w");
    memset(mid, 0, sizeof(mid));
    memset(end, 0, sizeof(end));

    //���õ�һ���������õ�һ��Ϊ1 2 3 4 5 6 7 8 9
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == 0)
                sudo[i][j] = j + 1;
            else
                sudo[i][j] = 0;
        }
    }

    //���n������
    for (int i = 0; i < n; i++) {
        if(i != 0) fprintf(fp, "\n");  //ÿ������֮���һ��

        //36���н��������ʹ��������ϵ�һ�еķ�ʽ����������
        if (flag_mid == 1 && flag_end == 1) { 
            //���ǵ�һ����ʼ����������Ҫ��������ϵ�һ��
            if (i != 0) {
                permutation(first);
                for (int j = 0; j < 8; j++) {
                    sudo[0][j + 1] = first[j];
                }
            }
            //��j��Ϊ��һ������shift[j]���任������������
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