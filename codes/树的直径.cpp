#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> G[100001];
int n;
int dep[100001];
void dfs(int rt,int depth,int fa){
	dep[rt] = depth;
	for(int i = 0;i < G[rt].size();i++){
		if(G[rt][i] != fa)dfs(G[rt][i],depth + 1,rt);
	}
}
int main(){
	scanf("%d",&n);
	int u = 0, v = 0;
	for(int i = 1;i < n;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dep[1] = 0;
	dfs(1,0,0);
	int s = 1, maxx = 0;
	for(int i = 1;i <= n;i++){
		if(dep[i] > maxx){
			maxx = dep[i];
			s = i;
		}
	}
	dfs(s,0,0);
	for(int i = 1;i <= n;i++)
		if(dep[i] > maxx)maxx = dep[i];
	printf("%d",maxx);
	return 0;
}

