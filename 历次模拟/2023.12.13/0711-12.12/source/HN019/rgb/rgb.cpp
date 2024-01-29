#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<bitset>
#define N 250
using namespace std;
int read()
{
    char c=0;
    int sum=0;
    while (c<'0'||c>'9') c=getchar();
    while ('0'<=c&&c<='9') sum=sum*10+c-'0',c=getchar();
    return sum;
}
struct reads
{
    int x,y,cl;
};
reads st[N*N+1];
struct node
{
    int num,data;
};
int n,m,cnts,fa[N+1],tfa[N+1],pv[N*N+1],lca[N+1][N+1],rts[N+1],rt[N+1],depth[N+1],cnt[4],maxn[4];
bool op,used[N*N+1],vis[N+1],dst[N+1],rch[N*N+1];
vector<int>v[4];
vector<node>E[N+1];
bitset<N+1>vst[N+1];
int F(char c)
{
    if (c=='r') return 1;
    else if (c=='g') return 2;
    else return 3;
}
void add(int x,int y,int z)
{
    E[x].push_back((node){y,z}),E[y].push_back((node){x,z});
    return;
}
void dfs(int x)
{
    vis[x]=vst[x][x]=1;
    for (int i=0;i<E[x].size();++i)
	if (!vis[E[x][i].num])
	    fa[E[x][i].num]=x,tfa[E[x][i].num]=E[x][i].data,rts[E[x][i].num]=rts[x],depth[E[x][i].num]=depth[x]+1,dfs(E[x][i].num),vst[x]|=vst[E[x][i].num];
    return;
}
void dfs2(int x,int y)
{
    if (vst[x][y]) lca[x][y]=x;
    for (int i=0;i<E[x].size();++i)
	if (fa[E[x][i].num]==x)
	    lca[E[x][i].num][y]=lca[x][y],dfs2(E[x][i].num,y);
    return;
}
int find(int x)
{
    if (rt[x]==x) return x;
    return rt[x]=find(rt[x]);
}
void unionn(int x,int y)
{
    rt[x]=y;
    return;
}
void bfs()
{
    int top,x,d,t=0;
    queue<int>q;
    for (int i=1;i<=m;++i)
	if (!used[i]&&cnt[st[i].cl]<maxn[st[i].cl])
	    rch[i]=1,q.push(i);
    while (!q.empty())
    {
	top=q.front(),q.pop();
	if (used[top])
	{
	    if (!dst[st[top].cl])
	    {
		for (int i=0;i<v[st[top].cl].size();++i)
		    if (!rch[v[st[top].cl][i]])
			pv[v[st[top].cl][i]]=top,rch[v[st[top].cl][i]]=1,q.push(v[st[top].cl][i]);
		dst[st[top].cl]=1;
	    }
	}
	else
	{
	    if (rts[st[top].x]!=rts[st[top].y])
	    {
		t=top;
		break;
	    }
	    d=lca[st[top].x][st[top].y],x=find(st[top].x);
	    while (depth[x]>depth[d])
	    {
		if (!rch[tfa[x]]) pv[tfa[x]]=top,rch[tfa[x]]=1,q.push(tfa[x]);
		unionn(x,find(fa[x])),x=find(fa[x]);
	    }
	    x=find(st[top].y);
	    while (depth[x]>depth[d])
	    {
		if (!rch[tfa[x]]) pv[tfa[x]]=top,rch[tfa[x]]=1,q.push(tfa[x]);
		unionn(x,find(fa[x])),x=find(fa[x]);
	    }
	}
    }
    if (t) op=1;
    while (t) used[t]^=1,t=pv[t];
    return;
}
int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    char c;
    maxn[1]=read(),maxn[2]=read(),maxn[3]=read(),n=maxn[1]+maxn[2]+maxn[3]+1,m=read();
    for (int i=1;i<=m;++i) st[i].x=read(),st[i].y=read(),cin>>c,st[i].cl=F(c);
    while (1)
    {
	op=0;
	for (int i=1;i<=3;++i) cnt[i]=dst[i]=0,v[i].clear();
	for (int i=1;i<=n;++i) vis[i]=fa[i]=0,rt[i]=i,E[i].clear(),vst[i].reset();
	for (int i=1;i<=m;++i) pv[i]=rch[i]=0;
	for (int i=1;i<=n;++i)
	    for (int j=1;j<=n;++j)
		lca[i][j]=0;
	for (int i=1;i<=m;++i)
	{
	    if (used[i]) cnt[st[i].cl]++,add(st[i].x,st[i].y,i);
	    else v[st[i].cl].push_back(i);
	}
	for (int i=1;i<=n;++i)
	    if (!vis[i])
		rts[i]=i,depth[i]=1,dfs(i);
	for (int i=1;i<=n;++i) dfs2(1,i);
	bfs();
	if (!op) break;
	cnts++;
    }
    if (cnts<n-1) puts("NO");
    else
    {
	puts("YES");
	for (int i=1;i<=m;++i) printf("%d",used[i]);
	puts("");
    }
    return 0;
}
