#include <iostream>
#include <set>
#include <cstdio>
#include <map> 
using namespace std;
const int nmax = 100000 + 20;
multiset<int>s;
int a[nmax]; //a[i] ����洢 ����ķ��ʴ��� 
int p[nmax]; //p[i]��ʾa[i]��һ�γ��ֵ�λ��
int g[nmax]; //g[i]��ʾa[i]��һ�γ��ֵ�λ��
//˼·�����������һ�˳��ֵ���Զ�Ļ��� 
int main(int argc, char** argv) {
	int n;//������ʴ��� 
	int m;//cache���� 
	while (cin >> n >> m) {
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for (int i = 1; i <= n; i++) {
			p[i] = n + 1;//�������ֵ�����a[i]û����һ��,�ͱ���n+1 
			p[g[a[i]]] = i;
			g[a[i]] = i;
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (s.find(i) != s.end()) {//���� 
				s.erase(i);     //ɾ������ 
				s.insert(p[i]); //������һ�� 
			}
			else {//û����
				ans++;
				if (s.size() == m) {//��������Ѿ����� 
					s.erase(--s.end());//ɾ�������
				}
				s.insert(p[i]); //������һ�� 

			}
		}
		cout << ans << endl;
	}
	return 0;
}