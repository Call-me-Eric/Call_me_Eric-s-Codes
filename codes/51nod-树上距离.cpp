#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>G[1001];
int val[1001][1001];
int f[1001];
int n,q;
int depth[1001];
void getdepth(int fa,int root,int dph){
	depth[root] = dph;
	for(int i = 0,len = G[root].size();i < len;i++){
		if(fa != G[root][i]){
			f[G[root][i]] = root;
			getdepth(root,G[root][i],dph+1);
		}
	}
}
int dfs(int u,int v){
	int sum = 0;
	if(depth[u] < depth[v]){
		swap(u,v);
	}
	if(depth[u] != depth[v]){
		while(depth[u] != depth[v]){
			sum += val[u][f[u]];
			u = f[u];
		} 
	}
	while(u != v){
		sum += val[u][f[u]] + val[v][f[v]];
		u = f[u];
		v = f[v];
	}
	return sum;
}
int u, v, w;
int main(){
	scanf("%d%d",&n,&q);
	for(int i = 1;i < n;i++){
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back(v);
		G[v].push_back(u);
		val[u][v] = val[v][u] = w;
	}
	getdepth(1,1,1);
	for(int i = 1;i <= q;i++){
		scanf("%d%d",&u,&v);
		printf("%d\n",dfs(u,v));
	}
	return 0;
}

