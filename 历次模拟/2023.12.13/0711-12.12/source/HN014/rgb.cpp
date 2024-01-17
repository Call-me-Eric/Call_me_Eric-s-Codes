#include<bits/stdc++.h>
#define rg register
#define file(x)freopen(x".in","r",stdin);freopen(x".out","w",stdout)

using namespace std;

const int maxn=250+10;
const int maxm=maxn*maxn;

int n,m,R,G,B;
struct Edge{
	int Color,x,y;
}E[maxm];

namespace BCJ{
	int Fa[maxn],Size[maxn];
	inline void init()
	{
		for(rg int i=1;i<=n;i+=1)Size[Fa[i]=i]=1;
	}
	inline int find(int x)
	{
		return Fa[x]==x?x:find(Fa[x]);
	}
	pair<int,int>Sta[maxn];int top;
	inline bool merge(int x,int y)
	{
		x=find(x),y=find(y);
		if(x==y)return false;
		if(Size[x]<Size[y])swap(x,y);
		Sta[++top]=make_pair(x,y);
		Fa[y]=x,Size[x]+=Size[y];
		return true;
	}
	inline void Undo()
	{
		assert(top);
		auto [x,y]=Sta[top--];
		Size[x]-=Size[y];
		Fa[y]=y;
	}
}

bool vis[maxn];
inline void dfs(int now,int cr,int cg,int cb)
{
	if(now==m+1)
	{
		if(cr!=R||cg!=G||cb!=B)return;
		puts("YES");
		for(rg int i=1;i<=m;i+=1)
			putchar(48+vis[i]);
		puts("");
		exit(0);
	}
	if(E[now].Color==0)
	{
		if(cr<R&&BCJ::merge(E[now].x,E[now].y))
		{
			vis[now]=true;
			dfs(now+1,cr+1,cg,cb);
			BCJ::Undo();
		}
	}
	else if(E[now].Color==1)
	{
		if(cg<G&&BCJ::merge(E[now].x,E[now].y))
		{
			vis[now]=true;
			dfs(now+1,cr,cg+1,cb);
			BCJ::Undo();
		}
	}
	else
	{
		if(cb<B&&BCJ::merge(E[now].x,E[now].y))
		{
			vis[now]=true;
			dfs(now+1,cr,cg,cb+1);
			BCJ::Undo();
		}
	}
	vis[now]=false;
	dfs(now+1,cr,cg,cb);
}

int main()
{
	file("rgb");
	scanf("%d %d %d %d",&R,&G,&B,&m);
	n=R+G+B+1;
	for(rg int i=1;i<=m;i+=1)
	{
		auto &[Color,x,y]=E[i];
		scanf("%d %d",&x,&y);
		static char ssd[14];
		scanf("%s",ssd+1);
		if(ssd[1]=='r')Color=0;
		if(ssd[1]=='g')Color=1;
		if(ssd[1]=='b')Color=2;
	}
	BCJ::init();
	dfs(1,0,0,0);
	puts("NO");
	return 0;
}
