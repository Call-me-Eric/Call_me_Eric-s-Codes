#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define inf 1e9
using namespace std;
inline int read(){
	int re=0,flag=1;
	scanf("%d",&re);return re;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') re=(re<<1)+(re<<3)+ch-'0',ch=getchar();
	return re*flag;
}
int n,m,cnt,first[210],dep[210],cur[210],ans[160][160];
struct edge{
	int to,next,w,W;
}a[10010];
inline void add(int u,int v,int w){
	a[++cnt]=(edge){v,first[u],w,w};first[u]=cnt;
	a[++cnt]=(edge){u,first[v],w,w};first[v]=cnt;
}
bool bfs(int s,int t){
	int q[210],head=0,tail=1,i,u,v;
	for(i=1;i<=n;i++) dep[i]=-1,cur[i]=first[i];
	q[0]=s;dep[s]=0;
	while(head<tail){
		u=q[head++];
		for(i=first[u];~i;i=a[i].next){
			v=a[i].to;
			if(~dep[v]||!a[i].w) continue;
			dep[v]=dep[u]+1;q[tail++]=v;
		}
	}
	return ~dep[t];
}
int dfs(int u,int t,int limit){
	if(u==t||!limit) return limit;
	int i,v,f,flow=0;
	for(i=first[u];~i;i=a[i].next){
		v=a[i].to;
		if(dep[v]==dep[u]+1&&(f=dfs(v,t,min(limit,a[i].w)))){
			a[i].w-=f;a[i^1].w+=f;
			flow+=f;limit-=f;
			if(!limit) return flow;
		}
	}
	return flow;
}
int dinic(int s,int t){
	int re=0;
	while(bfs(s,t)) re+=dfs(s,t,inf);
	return re;
}
void clear(){
	for(int i=0;i<=cnt;i++) a[i].w=a[i].W;
}
void init(){
	memset(first,-1,sizeof(first));memset(a,0,sizeof(a));cnt=-1;
	memset(ans,127,sizeof(ans));
}
int node[210],vis[210];
void cut(int u){
	int i,v;vis[u]=1;
	for(i=first[u];~i;i=a[i].next){
		v=a[i].to;
		if(a[i].w&&!vis[v]) cut(v);
	}
}
void solve(int l,int r){
	if(l==r) return;
	clear();int i,j,tmp,t[2][210]={0};
	memset(vis,0,sizeof(vis));
	tmp=dinic(node[l],node[r]);
	cut(node[l]);
	for(i=1;i<=n;i++)
		if(vis[i])
			for(j=1;j<=n;j++)
				if(!vis[j])
					ans[i][j]=ans[j][i]=min(ans[i][j],tmp);
	for(i=l;i<=r;i++) t[vis[node[i]]][++t[vis[node[i]]][0]]=node[i];
	for(i=l,j=1;j<=t[0][0];j++,i++) node[i]=t[0][j];
	for(i=l+t[0][0],j=1;j<=t[1][0];j++,i++) node[i]=t[1][j];
	solve(l,l+t[0][0]-1);solve(l+t[0][0],r);
}
int main(){
	int i,j,k,T=read(),t1,t2,t3,q;
	while(T--){
		init();
		n=read();m=read();
		for(i=1;i<=m;i++) t1=read(),t2=read(),t3=read(),add(t1,t2,t3);
		for(i=1;i<=n;i++) node[i]=i;
		solve(1,n);
		q=read();
		for(k=1;k<=q;k++){
			t1=read();int tmp=0;
			for(i=1;i<=n;i++){
				for(j=i+1;j<=n;j++) if(ans[i][j]<=t1) tmp++;
			}
			printf("%d\n",tmp);
		}
		puts("");
	}
}
