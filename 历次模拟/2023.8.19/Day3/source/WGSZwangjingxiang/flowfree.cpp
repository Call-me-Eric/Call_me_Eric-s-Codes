#include<bits/stdc++.h>
using namespace std;
int dx[]={0,1,0,-1,0};
int dy[]={0,0,1,0,-1};
int n,m,num;
int mp[15][15],tag[15][15];
int cnt[15];
struct Pos
{
	int x,y;
}ans[15][150];
struct Node
{
	int x1,y1,x2,y2;
}e[15];
bool check()
{
	if(n*n==num)return true;
	return false;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(mp[i][j]==0)return false;
		}
	}
	return true;
}
void info()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cout<<mp[i][j]<<" ";
		}
		cout<<endl;
	}
}
void output()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cnt[mp[i][j]]++;
		}
	}
	for(int i=1;i<=m;i++)
	{
		cout<<cnt[i]<<endl;
		for(int j=1;j<=cnt[i];j++)
		{
			cout<<ans[i][j].x<<" "<<ans[i][j].y<<endl;
		}
	}
}
void work(int x);
void dfs(int x,int y,int id,int step)
{
	mp[x][y]=id;
	num++;
	ans[id][step].x=x;
	ans[id][step].y=y;
	if(x==e[id].x2&&y==e[id].y2)
	{
		work(id+1);
		num--;
		mp[x][y]=0;
		return;
	}
	for(int i=1;i<=4;i++)
	{
		int tx=x+dx[i];
		int ty=y+dy[i];
		if(tx<1||ty<1||tx>n||ty>n||mp[tx][ty])continue;
		if(tag[tx][ty]&&tag[tx][ty]!=id)continue;
		dfs(tx,ty,id,step+1);
	}
	num--;
	mp[x][y]=0;
}
void work(int x)
{
	if(x>m)
	{
		if(check())
		{
			output();
			exit(0);
		}
	}
	else
		dfs(e[x].x1,e[x].y1,x,1);
}
int main()
{
	freopen("flowfree.in","r",stdin);
	freopen("flowfree.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>e[i].x1>>e[i].y1>>e[i].x2>>e[i].y2;
		tag[e[i].x1][e[i].y1]=i;
		tag[e[i].x2][e[i].y2]=i;
	}
	work(1);
	
}
/*
3 1
1 1 1 3
*/
