#include<bits/stdc++.h>
#define rg register
#define file(x)freopen(x".in","r",stdin);freopen(x".out","w",stdout)

using namespace std;

const int maxn=2e5+10;

pair<int,long long>Ans;
int n,m;
int head[maxn],to[maxn<<1],nxt[maxn<<1],tot;
int Deg[maxn];
inline void add(int x,int y)
{
    nxt[++tot]=head[x];head[x]=tot;to[tot]=y;
    nxt[++tot]=head[y];head[y]=tot;to[tot]=x;
}

bool vis[maxn];
int Node,Edge;
int MaxD;
inline void dfs(int now)
{
    MaxD=max(MaxD,Deg[now]);
    vis[now]=true;
    Node+=1;
    for(rg int i=head[now];i;i=nxt[i])
    {
	if(!vis[to[i]])
	    dfs(to[i]);
	if(now<to[i])Edge+=1;
    }
}
inline void calc(int Node,int Edge)
{
    if(Node<Edge)
    {
	puts("-1");
	exit(0);
    }
    else if(Node==Edge)
    {
	if(MaxD>2)
	{
	    puts("-1");
	    exit(0);
	}
	if(Ans.first)Ans.second+=Node;
	else
	{
	    Ans.first=1;
	    Ans.second=Node;
	}
    }
    else
    {
	if(MaxD<=2)
	{
	    if(Ans.first)return;
	    else Ans.second+=1ll*Node*(Node+1)/2;
	}
	else
	{
	    if(Node^4)
	    {
		puts("-1");
		exit(0);
	    }
	    if(!Ans.first)
	    {
		Ans.first=1;
		Ans.second=3;
	    }
	    else Ans.second+=3;
	}
    }
}
inline void solve(int x)
{
    Node=Edge=0;
    MaxD=0;
    dfs(x);
    calc(Node,Edge);
}

int main()
{
    file("li");
    scanf("%d %d",&n,&m);
    for(rg int i=1;i<=m;i+=1)
    {
	int x,y;scanf("%d %d",&x,&y);
	add(x,y);
	Deg[x]+=1,Deg[y]+=1;
    }
    for(rg int i=1;i<=n;i+=1)
	if(!vis[i])
	    solve(i);
    printf("%d %lld\n",Ans.first,Ans.second);
    return 0;
}
