#include<bits/stdc++.h>
#define int long long
#define re register
using namespace std;
int read(){
	int sum=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}
	return f*sum;
}
const int N=1e5+10;
bool vis[40010][40010];
int cnt,head[N],ans;
int n,a[N];
struct node{
	int to,nxt,w;
}e[N<<1];
inline void add(int u,int v,int w){
	e[++cnt].w=w;
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
inline void dfs(int x,int zu,int fa,int you){
	for(re int i=head[x];i;i=e[i].nxt){
		if(e[i].to!=fa){
			if(e[i].w>you) continue;
			else{
				if(!vis[zu][e[i].to]&&zu!=e[i].to){
					ans++;
					vis[zu][e[i].to]=true;
					dfs(e[i].to,zu,x,you-e[i].w+a[e[i].to]);
				}
			}
		}
		
	}
}
signed main(){
	freopen("transport.in","r",stdin);freopen("transport.out","w",stdout);
	n=read();
	for(re int i=1;i<=n;i++) a[i]=read();
	for(re int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,w);
	}
	for(re int i=1;i<=n;i++){
		dfs(i,i,0,a[i]);
	}
	printf("%lld",ans);
	return 0;
}
