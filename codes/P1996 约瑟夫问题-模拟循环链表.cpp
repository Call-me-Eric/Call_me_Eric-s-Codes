#include <iostream>
#include <cstdio>

using namespace std;
int a[100+5];
int main(){
	int n, m, total = 0, ans = 1,j;
	//total ����������ans��¼�Ƿ񵽴�m
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		a[i] = i+1;  //�������� 
	a[n] = 1 ;		//ѭ������
	j = n;
	while(total < n) {
		while(ans < m){
			j = a[j]; //ָ����һ��
			ans ++; 
		}
		//����m �ˣ� 
		cout <<a[j] <<' ';
		total ++; //
		a[j] = a[a[j]];//ָ������ڵ� 
		ans = 1;  //���������� 
	} 
	return 0;
}

