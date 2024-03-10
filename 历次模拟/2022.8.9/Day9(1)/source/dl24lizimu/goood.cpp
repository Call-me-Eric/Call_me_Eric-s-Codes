#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int n,m,u,v;
int ans[N],res=0;
vector<int> e1[N],e2[N];
int vis[N],num=0;
void check1(int x){
	queue<int> q1;
	for(int i=0;i<e1[x].size();i++){
		if(!vis[e1[x][i]]){
			q1.push(e1[x][i]);
			num++;vis[e1[x][i]]=1;
		}
	}
	while(!q1.empty()){
		check1(q1.front());q1.pop();
	}
}
void check2(int x){
	queue<int> q2;
	for(int i=0;i<e2[x].size();i++){
		if(!vis[e2[x][i]]){
			q2.push(e2[x][i]);
			num++;vis[e2[x][i]]=1;
		}
	}
	while(!q2.empty()){
		check2(q2.front());q2.pop();
	}
}
bool dfs(int x){
	memset(vis,0,sizeof(vis));
	num=0;
	vis[x]=1;
	check1(x);
	check2(x);
	memset(vis,0,sizeof(vis));
	num=0;
	vis[x]=1;
	check2(x);
	check1(x);
	return num==n-1?1:0;
}
int main(){
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		e1[u].push_back(v);
		e2[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(dfs(i)){
			ans[++res]=i;
		}
	}
	printf("%d\n",res);
	for(int i=1;i<=res;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
