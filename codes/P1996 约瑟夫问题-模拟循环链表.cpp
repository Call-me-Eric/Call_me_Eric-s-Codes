#include <iostream>
#include <cstdio>

using namespace std;
int a[100+5];
int main(){
	int n, m, total = 0, ans = 1,j;
	//total 出对人数，ans记录是否到达m
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		a[i] = i+1;  //建立链表 
	a[n] = 1 ;		//循环链表
	j = n;
	while(total < n) {
		while(ans < m){
			j = a[j]; //指向下一个
			ans ++; 
		}
		//到达m 了， 
		cout <<a[j] <<' ';
		total ++; //
		a[j] = a[a[j]];//指向后续节点 
		ans = 1;  //计数器重置 
	} 
	return 0;
}

