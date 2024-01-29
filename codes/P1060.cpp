#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n, m;
int v[100100], w[100010];
int dp[100100];
int main(){
	scanf("%d%d",&m,&n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&v[i],&w[i]);
		w[i] = w[i] * v[i];
	}
	for(int i = 1;i <= n;i++){
		for(int j = m;j >= v[i];j--){
			dp[j] = max(dp[j],dp[j - v[i]] + w[i]);
		}
	}
	printf("%d",dp[m]);
	return 0;
} 
