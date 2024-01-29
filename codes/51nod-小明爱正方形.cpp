#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,T;
int len[21],a[5];
int m;
bool dfs(int k){
	if(k == 0)return true;
	for(int i = 1;i <= 4;i++){
		if(a[i] + len[k] > m)continue;
		a[i] += len[k];
		bool b = dfs(k - 1);
		a[i] -= len[k];
		if(b)return true;
	}
	return false;
}
int main(){
	scanf("%d",&T);
	while(T--){
		int sum = 0;
		for(int i = 1;i <= 20;i++){
			len[i] = 0;
			a[i / 5] = 0;
		}
		scanf("%d",&n);
		for(int i = 1;i <= n;i++){
			scanf("%d",&len[i]);
			sum += len[i];
		}
		m = sum / 4;
		printf("%s",(sum % 4 == 0 && dfs(n)) ? "true" : "false");
	}
	return 0;
}

