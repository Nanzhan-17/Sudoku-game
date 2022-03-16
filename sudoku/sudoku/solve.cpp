#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "sudoku.h"
int s_sudo[9][9];
int blank[9];  //��¼ÿһ�пհ׵ĸ���
int isOK = 0;  //isOK == 1������������������
int num_sudo = 0;  //��¼���뵽����ļ����ǵڼ�������

//�ж��С��С��Ź����Ƿ����ظ�
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

//���������dfs
void resolve(int row, int col) {
    if (isOK == 1)return;
    blank[row]--;
    for (int i = 1; i < 10; i++) {
        s_sudo[row][col] = i;
        if (isValid(row, col)) {
            //��һ�л��пո�
            if (blank[row] > 0) {
                int j;
                for (j = 0; j < 9; j++) {
                    if (s_sudo[row][j] == 0)break;
                }
                resolve(row, j);
            }

            //��һ��û�пո���
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
    //9�����ֶ������꣬û�з���Ҫ��ģ�֤����һ����������ˣ�����
    s_sudo[row][col] = 0;
    blank[row]++;
    return;
}

//����������д���ļ����
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
    char str[18];  //ÿһ�е������9����+�ո�
    //������һ��һ�е�д���ļ�
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

//���ζ�ȡÿ�����������
void solve(const char* txt) {
	FILE* fp = fopen(txt, "r");
    

    //��ʼ��s_sudo[9][9]
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            s_sudo[i][j] = 0;
        }
    }

    //��ȡ��Ҫ���������ļ������
	while (!feof(fp))
	{
        int flag = 0;
        char str[25];
        memset(blank, 0, sizeof(blank));
        for (int i = 0; i < 9; i++) {
            fgets(str, 25, fp);  //str[25]�����ļ���ÿһ��
            if (str[0] < '0' || str[0]>'9') {
                flag = 1;
                break;
            }
            int k = 0;
            //��������int�ʹ���s_sudo[9][9]
            for (int j = 0; j < 30; j++) {
                if (str[j] >= '0' && str[j] <= '9') {
                    //printf("hsuashu\n");
                    s_sudo[i][k] = str[j] - '0';
                    if (s_sudo[i][k] == 0)  blank[i]++;  //��¼ÿһ�пհ׵ĸ���
                    k++;
                }
                if (k == 9)break;
            }
        }
        if (flag == 1)continue;  //str�����˲��������Ļس���

        /*  debug:  blank�����Ƿ���ȷ
        for (int i = 0; i < 9; i++) {
            printf("%d  ", blank[i]);
        }
        printf("\n");
        */

        //�ҵ��հ������Ҳ�Ϊ0��һ�У�����һ�п�ʼ����
        int min_row = -1;
        for (int i = 0; i < 9; i++) {
            if (blank[i] == 0)continue;
            if (min_row == -1)min_row = i;
            if (blank[i] < blank[min_row])min_row = i;
        }

        /*  debug:  �������С���Ƿ���ȷ
        printf("dee: %d\n", min_row); 
        */

        //�ҵ�Ϊ0����һ��
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