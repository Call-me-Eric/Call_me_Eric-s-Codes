#include<bits/stdc++.h>
#define N 255
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
int n,r,g,b,m,u[N],v[N],tot;
char c[N];bool vis[N],G[N][N];
void dfs(int u){
	vis[u]=true;tot++;
	for(int i=1;i<=n;i++)
		if(G[u][i]&&!vis[i])dfs(i);
}
signed main(){
	file("rgb");
	r=read();g=read();b=read();m=read();n=r+g+b+1;
	for(int i=1;i<=m;i++)u[i]=read(),v[i]=read(),cin>>c[i];
	for(int s=0;s<1<<(m+1);s+=2){
		if(__builtin_popcount(s)!=n-1)continue;
		int cnt[3]={0,0,0};
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)G[i][j]=false;
		for(int i=1;i<=m;i++)
			if((s>>i)&1){
				switch(c[i]){
				case'r':cnt[0]++;break;
				case'g':cnt[1]++;break;
				case'b':cnt[2]++;break;
				}
				G[u[i]][v[i]]=G[v[i]][u[i]]=true;
			}
		if(cnt[0]!=r||cnt[1]!=g||cnt[2]!=b)continue;
		for(int i=1;i<=n;i++)vis[i]=false;
		dfs(1);
		if(tot!=n)continue;
		puts("YES");
		for(int i=1;i<=m;i++)printf("%d",(s>>i)&1);
		return 0;
	}
	puts("NO");
	return 0;
}
