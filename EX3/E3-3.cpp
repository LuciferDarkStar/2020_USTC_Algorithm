/******************���ر�������*********************/
#include <iostream>
#include <vector>
#include <math.h>
#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define EMPTY
#define INF -65536
#define max(a,b)	a<b?b:a
int V ;//�������
int T ;//������Ʒ����
int f[10000 + 1];
int c[200] ;
int w[200] ;
int n[200] ;
vector <int> n_list;//�洢�ֽ���ÿһ��ϵ��
vector <int> c_list;//���ֽ���ÿһ��ϵ������ÿһ�����
vector <int> w_list;//���ֽ���ÿһ��ϵ������ÿһ����ֵ
void initpackage()//��ÿ��ϵ���ֽ�
{
	int x = 0;
	for (int i = 0; i < T; i++)
	{
		int p = 1;
		while ((n[i] - pow(2, p) + 1) >= 0)
		{
			n_list.push_back(pow(2, p - 1));
			c_list.push_back(c[i] * pow(2, p - 1));
			w_list.push_back(w[i] * pow(2, p - 1));
			p++;
		}
		x = n[i] - pow(2, p - 1) + 1;
		if (x > 0)
		{
			n_list.push_back(x);
			c_list.push_back(c[i] * x);
			w_list.push_back(w[i] * x);
		}
	}
}
int package()
{
	initpackage();
	int size;
	size = n_list.size();
#ifdef EMPTY
	for (int i = 0; i <= V; i++)
	{
		f[i] = 0;
	}
#else
	f[0] = 0;
	for (int i = 1; i <= V; i++)
	{
		f[i] = INF;
	}
#endif // EMPTY
	for (int i = 0; i < size; i++)
	{
		for (int v = V; v >= c_list[i]; v--)
		{
			f[v] = max(f[v], f[v - c_list[i]] + w_list[i]);
		}
	}
	return f[V];
}
int main()
{
	int temp,i;
	scanf("%d", &T);
	scanf("%d", &V);
	for (i = 0; i < T; i++)
	{
		scanf("%d %d %d", &c[i], &w[i], &n[i]);
	}
	temp = package();
	cout << temp << endl;
	return 0;
}
