#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,m;
int edgenum1,head1[maxn],edgenum2,head2[maxn];
struct Edge{int nxt,to;}edge1[maxn],edge2[maxn];
int cnt;
bool vis1[maxn],vis2[maxn];
void addedge1(int x,int y)
{
	edgenum1++;
	edge1[edgenum1].nxt=head1[x];
	head1[x]=edgenum1;
	edge1[edgenum1].to=y;
	return;
}
void addedge2(int x,int y)
{
	edgenum2++;
	edge2[edgenum2].nxt=head2[x];
	head2[x]=edgenum2;
	edge2[edgenum2].to=y;
	return;
}
void dfs1(int x)
{
	vis1[x]=1;
	for(int i=head1[x];i;i=edge1[i].nxt)
	{
		int y=edge1[i].to;
		if(vis1[y]) continue;
		cnt++;
		dfs1(y);
	}
}
void dfs2(int x)
{
	vis2[x]=1;
	for(int i=head2[x];i;i=edge2[i].nxt)
	{
		int y=edge2[i].to;
		if(vis2[y]) continue;
		if(!vis1[y]) cnt++;
		dfs2(y);
	}
}
int main()
{
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	
	n=read();
	m=read();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=read();
		y=read();
		addedge1(x,y);
		addedge2(y,x);
	}
	int ans[maxn],pos=0;
	for(int i=1;i<=n;i++)
	{
		memset(vis1,false,sizeof(vis1));
		memset(vis2,false,sizeof(vis2));
		cnt=0;
		dfs1(i);
		dfs2(i);
		if(cnt==n-1) ans[++pos]=i;
	}
	cout<<pos<<endl;
	for(int i=1;i<=pos;i++)
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}
