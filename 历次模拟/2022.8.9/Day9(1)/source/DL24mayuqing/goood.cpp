#include<bits/stdc++.h>
#define ri register int
using namespace std;
const int N=1e5+1;
int n,m,ans,cnt,hd[N];
bool flag[N];
inline int read() {
	ri x=0,f=0;
	register char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x; }
struct node {
	int id,to; } e[N];
inline void add(int u,int v) {
	e[++cnt].to=v,e[cnt].id=hd[u],hd[u]=cnt; }

inline void dfs(int x) {
	bool b[N];
	for(ri i=1; i<=n; ++i) b[i]=0;
	for(ri i=hd[x]; ~i; i=e[i].id)
		b[e[i].to]=1;
	for(ri i=1; i<=n; ++i)
		if(b[i]==0) {
			flag[i]=flag[x]=1;
			return; }
	return; }

signed main() {
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	n=read(),m=read();
	for(ri i=1,u,v; i<=m; ++i) u=read(),v=read(),add(u,v);
	for(ri i=1; i<=n; ++i) {
		dfs(i);
		if(flag[i]==0) ++ans; }
	printf("%d\n",ans);
	for(ri i=1; i<=n; ++i)
		if(flag[i]==0) printf("%d ",i);
	return 0; }
