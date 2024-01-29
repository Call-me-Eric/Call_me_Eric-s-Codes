#include<bits/stdc++.h>
using namespace std;
int n, pos;
int first[500001];
int size[500001];
int death[500001];
struct edge{
	int next,to;
}e[500001];
void add(int u,int v){
	e[pos].to = v;
	e[pos].next = first[u];
	first[u] = pos++;
}
void dfs(int step,int father,int d){
	death[step] = d;
	size[step] = 1;
	for(int k = first[step];k != -1;k = e[k].next){
		int v = e[k].to;
		if(v != father){
			dfs(v,step,d + 1);
			size[step] += size[v];
		}
	}
	return;
}
int main(){
	memset(first,-1,sizeof(first));
	scanf("%d",&n);
	int x = 0,y = 0;
	for(int i = 0;i < n - 1;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,0,1);
	for(int i = 1;i <= n;i++)printf("%d ",death[i]);
	putchar('\n');
	for(int i = 1;i <= n;i++)printf("%d ",size[i]);
	return 0;
}
