#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> G[100001];
int n;
int ans;
int dep[100001];
void dfs(int fa,int root,int depth){
	dep[root] = depth;
	for(int i = 0,len = G[root].size();i < len;i++){
		if(G[root][i] != fa){
			dfs(root,G[root][i],depth + 1);
		}
	}
}
int main(){
	scanf("%d",&n);
	int u, v;
	for(int i = 1;i < n;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);  
	}
	dfs(1,1,0);
	int s = 1,maxx = 0;
	for(int i = 1;i <= n;i++){
		if(dep[i] > maxx){
			s = i;
			maxx = dep[i];
		}
	}
	dfs(-1,s,0);
	for(int i = 1;i <= n;i++){
		if(dep[i] > maxx){
			maxx = dep[i];
		}
	}
	printf("%d",maxx);
	return 0;
}

