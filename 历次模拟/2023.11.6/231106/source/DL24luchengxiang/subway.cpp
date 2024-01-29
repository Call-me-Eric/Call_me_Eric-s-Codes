#include<bits/stdc++.h>
using namespace std;
#define inl inline
#define ll long long
#define int ll
const int N=5e2+5;
const int M=2e3+5;
const int inf=0x3f3f3f3f3f3f3f3f;
const int mod=1e9+7;
inl int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
inl void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inl void writei(int x){write(x);putchar(' ');}
inl void writel(int x){write(x);putchar('\n');}
int n,k,m,a[10][N],b[10][N],dis[10][N][N],u,v,c,vis[N],f[N][N];
int head[N],to[M],nxt[M],w[M],cnt;
inl void add(int u,int v,int c){
	nxt[++cnt]=head[u];
	to[cnt]=v;w[cnt]=c;
	head[u]=cnt;
}
inl void init(){
	for(int i=1;i<=n;i++)head[i]=0;
	for(int i=1;i<=cnt;i++)nxt[i]=0;
	cnt=0;
}
inl void dij(int s,int* dis){
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++)dis[i]=inf;
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
	dis[s]=0;q.push({0,s});
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=head[x];i;i=nxt[i]){
			int y=to[i],c=w[i];
			if(dis[y]>dis[x]+c){
				dis[y]=dis[x]+c;
				q.push({dis[y],y});
			}
		}
	}
}
signed main(){
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	n=read();k=read();
	for(int i=1;i<=k;i++){
		init();
		for(int j=1;j<=n;j++)a[i][j]=read();
		for(int j=1;j<=n;j++)b[i][j]=read();
		m=read();
		for(int j=1;j<=m;j++){
			u=read();v=read();c=read();
			add(u,v,c);add(v,u,c);
		}
		for(int j=1;j<=n;j++)dij(j,dis[i][j]);
	}
	memset(f,0x3f,sizeof f);
	f[1][0]=0;
	for(int s=1;s<(1<<k);s++){
		for(int i=1;i<=n;i++){
			for(int kk=1;kk<=k;kk++){
				if(!(s&(1<<kk-1)))continue;
				for(int j=1;j<=n;j++){
					f[i][s]=min(f[i][s],f[j][s^(1<<kk-1)]+a[kk][j]+dis[kk][j][i]+b[kk][i]);
				}
			}
		}
	}
	int ans=inf;
	for(int s=1;s<(1<<k);s++)ans=min(ans,f[n][s]);
	writel(ans);
	return 0;
}


