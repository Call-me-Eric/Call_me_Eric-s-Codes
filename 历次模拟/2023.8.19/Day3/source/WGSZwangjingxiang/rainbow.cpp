#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int p[N][N];
int cnt[N*N+N],tag[N*N];
int n,m,ans;
bool check(int x1,int y1,int x2,int y2)
{
	memset(cnt,0,sizeof(cnt));
	memset(tag,0,sizeof(tag));
	for(int i=x1;i<=x2;i++)
	{
		for(int j=y1;j<=y2;j++)
		{
			if(cnt[i-j+N]==0)
			{
				if(tag[p[i][j]])return false;
				tag[p[i][j]]=1;
				cnt[i-j+N]=p[i][j];
			}
			else if(cnt[i-j+N]!=p[i][j])return false;
		}
	}
	return true;
}
int main()
{
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>p[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int len=1;i+len-1<=n&&j+len-1<=m;len++)
			{
				int x2=i+len-1;
				int y2=j+len-1;
				if(check(i,j,x2,y2))ans++;
			}
		}
	}
	cout<<ans;
}
/*
10 10
1 2 3 4 5 6 7 8 9 6
2 8 1 9 2 8 3 7 4 6
1 9 2 8 1 9 4 7 2 5
1 9 2 8 1 5 4 9 2 7
4 6 2 9 4 8 1 5 2 9
1 2 8 4 6 4 3 2 8 4
4 1 9 3 4 8 6 7 2 3
7 6 4 5 2 7 3 6 4 7
6 9 3 4 9 2 3 4 8 9
8 3 2 6 4 7 7 4 8 3
*/
