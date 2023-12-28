#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>

const int N = 1e6 + 5;
struct edge
{
	int nxt,to,val;
};
edge e[N*3];
int head[N],cnt;
int dis[N];
int n,m;

void add(int u,int v,int w)
{
	e[++cnt] = {head[u],v,w};
	head[u] = cnt;
}

int main()
{
	freopen("measure.in","r",stdin);
	freopen("measure.out","w",stdout);
	memset(dis,0x3f,sizeof(dis));
	scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;++i)
		add(i-1,i,1),add(i,i-1,1);
	for(int i = 1;i <= m;++i)
	{
		int l,r;
		scanf("%d %d",&l,&r);
		add(l-1,r,0),add(r,l-1,0);
	}
	std::deque<int> q;
	q.push_back(0);
	dis[0] = 0;
	while(!q.empty())
	{
		int u = q.front();
		//printf("%d\n",u);
		q.pop_front();
		for(int i = head[u];i;i = e[i].nxt)
		{
			int v = e[i].to;
			if(dis[v] <= dis[u] + e[i].val)continue;
			dis[v] = dis[u] + e[i].val;
			if(e[i].val)
				q.push_back(v);
			else
				q.push_front(v);
		}
	}
	for(int i = 1;i <= n;++i)
		putchar(dis[i] - dis[i-1] == 1 ? '1':'0');
	putchar('\n');
}
