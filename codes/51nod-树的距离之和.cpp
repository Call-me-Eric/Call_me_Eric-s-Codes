#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
vector<long long> G[100010];
long long cnt[100010];
long long dp[100010];
int n;
void dfs1(int fa,int root){
	cnt[root] = 1;
	long long t = 0;
	for(int i = 0,len = G[root].size();i < len;i++){
		t = G[root][i];
		if(t != fa){
			dfs1(root,t);
			cnt[root] += cnt[t];
		}
	}
	dp[1] += root == 1 ? 0 : cnt[root];
}
void dfsdp(int fa,int root){
	long long t = 0;
	for(int i = 0,len = G[root].size();i < len;i++){
		t = G[root][i];
		if(t != fa){
			dp[t] = dp[root] - cnt[t] + n - cnt[t];
			dfsdp(root,t);
		}
	}
}
int main(){
	long long t1 = 0,t2 = 0;
	scanf("%d",&n);
	for(int i = 2;i <= n;i++){
		scanf("%lld%lld",&t1,&t2);
		G[t2].push_back(t1);
		G[t1].push_back(t2); 
	}
	dfs1(1,1);
	dfsdp(1,1);
	for(int i = 1;i <= n;i++){
		printf("%lld\n",dp[i]);
	}
	return 0;
}

