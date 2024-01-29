#include <bits/stdc++.h>
using namespace std;
struct node{
	int val, imp, zhu;
}a[65];
int main(){
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> a[i].val >> a[i].imp >> a[i].zhu;
	for (int j = 0; j <= n; j++)
		for(int i = 1; i <= m; i++){
			if(a[i].zhu > 0) {//ÊÇ¸½¼þ 
			
			}
			else{
				dp[i][j] = 
			}
		}
	return 0;
}
