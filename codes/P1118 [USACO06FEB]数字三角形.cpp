#include <iostream>
#include <cstdio>
using namespace std;
int a[13], b[13], f[13][13];
int n, sum, s=0, flag;

void dfs(int k,int s){
	if(flag) return;
	if(s > sum)	return ;	//减枝 ,不减枝80分！！！~ 
	if(k == n+1){
		if(s == sum){
			for(int i = 1; i <= n;i++)
				cout <<a[i] <<' '; 
			cout << endl;
			flag = 1;	
		}
		return;
	}
	for(int i = 1; i <= n; i++){
		if(!b[i]){
			a[k] = i;
			b[i] = 1;
			s += f[n][k] * a[k];
			dfs(k+1,s);
			s -= f[n][k] * a[k];
			b[i] = 0;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n >> sum;
	f[1][1] = 1;
	for(int i = 2; i <= n; i++)
		for(int j = 1; j <= i; j++)
			f[i][j] = f[i-1][j] + f[i-1][j-1];
	//n=12; sum=12269;	暴力dfs 70分，超时 
	dfs(1,0);	//记录当前的和 
	return 0;
}

