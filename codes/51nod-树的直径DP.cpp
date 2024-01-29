#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int dp[100001];
vector<int> G[100001];
int n;
bool vis[100001];
int dfs(int root){
	dp[root] = 0;
	int m1 = 0,m2 = 0;
	int len = G[root].size();
	for(int i = 0;i < len;i++){
		int next = G[root][i];
		dfs(next);
		if(dp[next] + 1 > m1){
			m2 = m1;
			m1 = dp[next] + 1;
		}
		else if(dp[next] + 1 > m2){
			m2 = dp[next] + 1;
		}
	}
	dp[root] = m1;
	return m1 + m2;
}
int main(){
	scanf("%d",&n);
	int u, v;
	for(int i = 1;i < n;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		vis[v] = 1; 
	}
	int k = 1;
	/*for(int i = 1;i < n;i++){
		if(vis[i] == 0){
			k = i;
			break;
		}
	}*/
	printf("%d",dfs(k));
	return 0;
}

