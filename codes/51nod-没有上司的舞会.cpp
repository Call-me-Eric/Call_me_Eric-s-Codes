#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n, a[100001];
int dp[100001][2];
vector<int> tree[100001];//dp[i][0]是第i个人不参加dp[i][1]反之 
void dfs(int root,int father){
	dp[root][0] = 0;
	dp[root][1] = a[root];
	int N = tree[root].size();
	int son = 0;
	for(int i = 0;i < N;i++){
		son = tree[root][i];
		if(son == father) continue;
		dfs(son, root);
		dp[root][1] += max(0, dp[son][0]);//上司参加则下属不能
		dp[root][0] += max(0, max(dp[son][0], dp[son][1]));//上司不参加则下属随意 
	}
	return;
}
int main(){
	int u = 0,v = 0;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i < n;i++){
		scanf("%d%d",&u,&v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	dfs(1, 0);
	int ans = 0;
	for(int i = 1;i <= n;i++){
		ans = max(ans,max(dp[i][0],dp[i][1]));
	}
	printf("%d",ans);
	return 0;
}

