#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[25],b[25];
int dp[700][30];
int mp[700][30];
int cnt;
int nt[25];
void dfs(int nx,int ls,int sum)
{
	if(sum==0)
	{
		++cnt;
		for(int i=1;i<=nx;i++)	mp[cnt][i]=nt[i];
		return;
	}
	for(int i=1;i<=min(ls,sum);i++)	nt[nx]=i,dfs(nx+1,i,sum-i);
}
int main()
{
	dfs(1,100,20);
	cout<<cnt;
	return 0;
}
