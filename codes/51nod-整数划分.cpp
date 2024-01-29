#include<iostream>
#include<cstdio>
using namespace std;
int n;
const long long MOD = 1e9 + 7;
long long r[2001][7011];
long long dfs(int pos,int sum){
	if(sum == n){
		return 1;
	}
	if(r[pos][sum] == 0){
		long long res = 0;
		for(int i = pos + 1;i <= n - sum;i++){
			res += dfs(i,sum + i);
		}
		r[pos][sum] = res % MOD;
	}
	return r[pos][sum];
}
int main(){
	scanf("%d",&n);
	printf("%lld",dfs(0,0));
	return 0;
}

