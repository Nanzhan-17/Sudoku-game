#pragma once
void swap(int& a, int& b);  //交换两个数
void create(int n);   //生成n个数独终局并写入文件
bool permutation(int* p);  //排列组合第一行
void flag(int f1, int f2);  //中间和末尾三行的变换
void output(int sudo[9][9], FILE* fp);  //把生成的数独写入文件输出

void solve(const char* txt);  //依次读取每个数独并求解
void resolve(int row, int col);  //求解数独的dfs
bool isValid(int row, int col);  //判断行、列、九宫格是否有重复
void s_output();  //把求解的数独写入文件输出