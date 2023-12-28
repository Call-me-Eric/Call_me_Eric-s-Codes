/*
一个环只要内部或向外连多任意一条边，就是指数级。
原图的每个连通块只能是链、环或 3 个花瓣的菊花图。
链每次长度减 1，最终会消失。
环则一直不动，菊花在一轮后会变成环。
*/
#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int> t[210000];
bool vis[210000];
void dfs(int u,int& vcnt,int& ecnt,int& dmax)
{
	vis[u]=1,vcnt+=1,ecnt+=t[u].size(),dmax=max<int>(dmax,t[u].size());
	for(int i=0;i<t[u].size();i++)
	{
		int v=t[u][i];
		if(!vis[v])
			dfs(v,vcnt,ecnt,dmax);
	}
}
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int a,b;
		cin>>a>>b;
		t[a].push_back(b);
		t[b].push_back(a);
	}
	int cnt1=0,cnt0=0;
	for(int i=1;i<=n;i++)
	{
		if(vis[i])
			continue;
		int vcnt=0,ecnt=0,dmax=0;
		dfs(i,vcnt,ecnt,dmax);
		ecnt/=2;
		// cout<<"i="<<i<<" : vc="<<vcnt<<" ec="<<ecnt<<" dm="<<dmax<<endl;
		if(ecnt==vcnt-1&&dmax<=2)
			cnt0+=vcnt*(vcnt+1)/2;
		else if(ecnt==vcnt-1&&ecnt==3&&dmax==ecnt)
			cnt1+=ecnt;
		else if(ecnt==vcnt&&dmax==2)
			cnt1+=ecnt;
		else
		{
			cout<<-1<<endl;
			return 0;
		}
	}
	if(cnt1)
		cout<<1<<" "<<cnt1<<endl;
	else
		cout<<0<<" "<<cnt0<<endl;
}
/*
14 12
1 2
2 3
3 4
4 5
8 9
9 12
9 13
6 7
7 14
14 10
10 11
11 6

14 10
1 2
2 3
3 4
4 5
6 7
7 8
8 9
9 10
10 11
13 14

5 4
1 2
1 3
1 4
1 5
*/