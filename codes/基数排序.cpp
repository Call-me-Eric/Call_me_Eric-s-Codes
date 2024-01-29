#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MOD = (1 << 16) - 1;//65536 = 2 ^ 16 
int n;
int a[100001];
vector<int> G[70000];
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
	}
	//radix_sort().begin
	int tot = 0;
	for(int i = 0;i < 65536;i++){
		G[i].clear();
	}
	for(int i = 1;i <= n;i++){
		G[a[i] & MOD].push_back(a[i]);
	}
	for(int i = MOD;i > 0;i--){
		for(int j = 0,len = G[i].size();j < len;j++){
			a[++tot] = G[i][j];
		}
		G[i].clear();
	}
	tot = 0;
	for(int i = 1;i <= n;i++){
		G[a[i] >> 16].push_back(a[i]); 
	}
	for(int i = MOD;i > 0;i--){
		for(int j = 0,len = G[i].size();j < len;j++){
			a[++tot] = G[i][j];
		}
		G[i].clear();
	}
	//radix_sort().end
	for(int i = 1;i <= n;i++){
		printf("%d ",a[i]);
	}
	return 0;
}

