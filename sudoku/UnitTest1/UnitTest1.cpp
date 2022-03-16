#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "CppUnitTest.h"
#include "../sudoku/sudoku.h"
#include "../sudoku/solve.cpp"
#include "../sudoku/create.cpp"
#include "../sudoku/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		//bool permutation(int* p) 函数测试，本项目中第一个数字固定为1，组合排列2-9
		TEST_METHOD(TestMethod1_permutation)
		{
			int p[8] = { 2,3,4,5,6,7,8,9 };
			permutation(p);
			Assert::AreEqual(p[0], 2);
			Assert::AreEqual(p[1], 3);
			Assert::AreEqual(p[2], 4);
			Assert::AreEqual(p[3], 5);
			Assert::AreEqual(p[4], 6);
			Assert::AreEqual(p[5], 7);
			Assert::AreEqual(p[6], 9);
			Assert::AreEqual(p[7], 8);

			permutation(p);
			Assert::AreEqual(p[0], 2);
			Assert::AreEqual(p[1], 3);
			Assert::AreEqual(p[2], 4);
			Assert::AreEqual(p[3], 5);
			Assert::AreEqual(p[4], 6);
			Assert::AreEqual(p[5], 8);
			Assert::AreEqual(p[6], 7);
			Assert::AreEqual(p[7], 9);
		}

		//void swap(int& a, int& b) 函数测试，本项目中涉及交换的数字为1-9
		TEST_METHOD(TestMethod1_swap)
		{
			int aa = 1, bb = 2;
			swap(aa, bb);
			Assert::AreEqual(aa == 2, true);
			Assert::AreEqual(bb == 1, true);			
		}

		TEST_METHOD(TestMethod1_swap2) {
			int aaa = 8, bbb = 9;
			swap(aaa, bbb);
			Assert::AreEqual(aaa == 9, true);
			Assert::AreEqual(bbb == 8, true);
		}

		TEST_METHOD(TestMethod1_swap3) {
			int aaaa = 0, bbbb = 10;
			swap(aaaa, bbbb);
			Assert::AreEqual(aaaa == 10, true);
			Assert::AreEqual(bbbb == 0, true);
		}

		//void flag(int f1, int f2) 函数测试
		TEST_METHOD(TestMethod1_flag)
		{
			flag(1, 1);
			Assert::AreEqual(mid[0] == 3 && mid[1] == 4 && mid[2] == 5 && end[0] == 6 && end[1] == 7 && end[2] == 8, true);
			flag(2, 2);
			Assert::AreEqual(mid[0] == 3 && mid[1] == 5 && mid[2] == 4 && end[0] == 6 && end[1] == 8 && end[2] == 7, true);
			flag(3, 3);
			Assert::AreEqual(mid[0] == 4 && mid[1] == 3 && mid[2] == 5 && end[0] == 7 && end[1] == 6 && end[2] == 8, true);
			flag(4, 4);
			Assert::AreEqual(mid[0] == 4 && mid[1] == 5 && mid[2] == 3 && end[0] == 7 && end[1] == 8 && end[2] == 6, true);
			flag(5, 5);
			Assert::AreEqual(mid[0] == 5 && mid[1] == 3 && mid[2] == 4 && end[0] == 8 && end[1] == 6 && end[2] == 7, true);
			flag(6, 6);
			Assert::AreEqual(mid[0] == 5 && mid[1] == 4 && mid[2] == 3 && end[0] == 8 && end[1] == 7 && end[2] == 6, true);
		}

		//测create函数
		TEST_METHOD(TestMethod1_create) 
		{
			create(1);
			FILE* fp = fopen("sudoku.txt", "r");
			char c = fgetc(fp);
			int k = c - '0';
			Assert::AreEqual(k == 1, true);
			fclose(fp);

		}

		//测solve函数
		TEST_METHOD(TestMethod1_solve)
		{
			char s[] = "test.txt";
			isOK = 0;
			num_sudo = 0;
			for (int i = 0; i < 9; i++)
				blank[i] = 0;
			solve(s);
			FILE* fp = fopen("sudoku.txt", "r");
			char c = fgetc(fp);
			int k = c - '0';
			Assert::AreEqual(k == 7, true);
			fclose(fp);
		}

		//void resolve(int row, int col) 函数测试
		TEST_METHOD(TestMethod1_resolve)
		{
			int ssudo[9][9] = {
				{0,1,2,0,4,0,0,0,9},
				{3,4,0,6,8,9,7,1,0},
				{6,8,9,7,0,0,3,4,5},
				{4,0,6,8,9,0,1,2,3},
				{1,0,3,4,0,6,8,9,7},
				{8,9,0,0,2,3,4,0,0},
				{5,6,8,0,0,0,2,0,4},
				{2,3,4,0,6,0,9,7,1},
				{9,7,0,0,3,4,5,6,0} };
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					s_sudo[i][j] = ssudo[i][j];
				}
			}
			resolve(1, 2);
			int f = 1;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if(ssudo[i][j]==0){
						if (!isValid(i, j)) {
							f = 2;
							break;
						}
					}
				}
			}
			Assert::AreEqual(f, 2);
		}

		//bool isValid(int row, int col) 函数测试
		TEST_METHOD(TestMethod1_isValid2) {
			s_sudo[0][0] = 1; s_sudo[0][3] = 1;
			Assert::AreEqual(isValid(0, 0), false);

			s_sudo[0][0] = 1; s_sudo[3][0] = 1;
			Assert::AreEqual(isValid(0, 0), false);

			s_sudo[0][0] = 1; s_sudo[1][1] = 1;
			Assert::AreEqual(isValid(0, 0), false);
		}
		
		TEST_METHOD(TestMethod1_isValid)
		{			
			int ssudo[9][9] = {
				{7,1,2,0,4,0,0,0,9},
				{3,4,0,6,8,9,7,1,0},
				{6,8,9,7,0,0,3,4,5},
				{4,0,6,8,9,0,1,2,3},
				{1,0,3,4,0,6,8,9,7},
				{8,9,0,0,2,3,4,0,0},
				{5,6,8,0,0,0,2,0,4},
				{2,3,4,0,6,0,9,7,1},
				{9,7,0,0,3,4,5,6,0} };
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					s_sudo[i][j] = ssudo[i][j];
				}
			}
			Assert::AreEqual(isValid(0, 0), true);
		}
	};
}
