#include<bits/stdc++.h>
#define ri register int
using namespace std;
const int N=1e4+7,M=1e5+7;
int n,a[M],dis[N][N];
long long ans;
bool b[N][N];
inline int read() {
	ri x=0,f=0;
	register char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x; }

struct node {
	int u,v,w; } e[N];
inline bool cmp(node x,node y) {
	return x.u<y.u; }

signed main() {
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	n=read();
	if(n<=10000) {
		memset(dis,-0x3f3f3f3f,sizeof(dis));
		for(ri i=1; i<=n; ++i) a[i]=read();
		for(ri i=1,u,v,w; i<n; ++i) {
			u=read(),v=read(),w=read();
			dis[u][v]=max(dis[u][v],a[u]-w);
			dis[v][u]=max(dis[v][u],a[v]-w); }
		for(ri k=1; k<=n; ++k)
			for(ri i=1; i<=n; ++i) {
				if(dis[i][k]<0||i==k) continue;
				for(ri j=1; j<=n; ++j) {
					if(i==j||j==k) continue;
					if(dis[k][j]==dis[k][i]+dis[i][j]) continue;
					dis[i][j]=max(dis[i][j],dis[i][k]+dis[k][j]);
					/*printf("%d %d %d %d %d %d\n",
					i,k,j,dis[i][k],dis[k][j],dis[i][j]);*/
				} }
		for(ri i=1; i<=n; ++i) {
			for(ri j=1; j<=n; ++j) {
				if(dis[i][j]>=0) ++ans;
				/*printf("%d ",dis[i][j]); }
				printf("\n"); }*/
			} }
		printf("%ld\n",ans);
		return 0; }
	else {
		for(ri i=1; i<=n; ++i) a[i]=read();
		for(ri i=1; i<n; ++i) e[i].u=read(),e[i].v=read(),e[i].w=read();
		sort(e+1,e+n,cmp);
		ri r=1,tot=0;
		for(ri i=1; i<n; ++i) {
			r=max(i,r);
			while(tot+a[r]-e[r].w>=0&&r<=n) tot+=a[r]-e[r].w,++r;
			--r,ans+=(long long)r-i,tot-=a[i]-e[i].w; }
		r=n,tot=0;
		for(ri i=n; i>1; --i) {
			r=min(i,r);
			while(tot+a[r]-e[r-1].w>=0&&r) tot+=a[r]-e[r-1].w,--r;
			ans+=(long long)i-r,tot-=a[i]-e[i].w; }
		printf("%ld\n",ans);
		return 0; } }
