#pragma once
void swap(int& a, int& b);
void create(int n);   //����n�������վֲ�д���ļ�
bool permutation(int* p);  //������ϵ�һ��
void flag(int f1, int f2);  //�м��ĩβ���еı任
void output(int sudo[9][9], FILE* fp);  //�����ɵ�����д���ļ����

void solve(const char* txt);  //���ζ�ȡÿ�����������
void resolve(int row, int col);  //���������dfs
bool isValid(int row, int col);  //�ж��С��С��Ź����Ƿ����ظ�
void s_output();  //����������д���ļ����