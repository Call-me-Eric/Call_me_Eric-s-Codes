#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4+10;
int edgenum,head[maxn];
struct Edge{int nxt,to,val;}edge[maxn];
//struct Point{int pos,val;}p[maxn];
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
void add(int x,int y,int v)
{
	edge[++edgenum].nxt=head[x];
	head[x]=edgenum;
	edge[edgenum].to=y;
	edge[edgenum].val=v;
}
int n,din[maxn],ans,sum,p[maxn];
bool vis[maxn];
void dfs(int x)
{
	vis[x]=1;
	sum+=p[x];
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int y=edge[i].to;
		if(vis[y]) continue;
		if(sum-edge[i].val>=0)
		{
			//if(x==1) cout<<"---"<<endl;
			sum-=edge[i].val;
			ans++;
			//cout<<x<<" "<<y<<" "<<endl;
			dfs(y);
			sum+=edge[i].val;
		} 
	}
	sum-=p[x];
}
int main()
{
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n-1;i++)
	{
		int x,y,v;
		x=read(),y=read(),v=read();
		din[x]++;din[y]++;
		add(x,y,v);
		add(y,x,v);
	}
	//cout<<endl;
	for(int i=1;i<=n;i++) 
	{
		sum=0;
		memset(vis,false,sizeof(vis));
		dfs(i);
	}
	cout<<ans<<endl;
	
	return 0;
}
/*
5
3 1 2 4 5
1 2 3
3 2 2
4 2 6
5 4 3
*/
