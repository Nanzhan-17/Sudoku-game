#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "sudoku.h"

int main(int argc, char* argv[]) {
	//��¼��ͬ��Ŀ������������ʱ
	int start = clock();
	int end = 0;
	int time = 0;
	

	//�����ж�����Ĳ����Ƿ���ȷ
	if (argc != 3) {
		printf("Please enter the correct command!\n");
		return 0;
	}
	
	if ((strcmp(argv[0], "sudoku") != 0)) {
		printf("Please enter the correct command - sudoku! \n");
		return 0;
	}
	
	//sudoku -c 20 �����������n�������վ�
	if (!(strcmp(argv[1], "-c"))) {
		for (int i = 0; argv[2][i] != '\0'; i++) {  //sudoku -c 20 �����µ�����������������
			if ((argv[2][i] >= 'a' && argv[2][i] <= 'z') || (argv[2][i] >= 'A' && argv[2][i] <= 'Z'))
			{
				printf("The third parameter should be an integer!\n");
				return 0;
			}
		}

		int n = atoi(argv[2]);  //sudoku -c 20 �����µ�������������Ҫ��Χ��
		if (n <= 0 || n > 1000000)
		{
			printf("The third parameter should be between 1 and 1000000!\n");
			return 0;
		}

		create(n);
		printf("Create succeeded!\n");
		end = clock();
		time = end - start;
		printf("The time consumed is %d ms!\n", time);
	}

	//sudoku -s absolute_path_of_puzzlefile ��������������
	if (!(strcmp(argv[1], "-s"))) {
		solve(argv[2]);
		printf("Solve succeeded!\n");
		end = clock();
		time = end - start;
		printf("The time consumed is %d ms!\n", time);
	}
}