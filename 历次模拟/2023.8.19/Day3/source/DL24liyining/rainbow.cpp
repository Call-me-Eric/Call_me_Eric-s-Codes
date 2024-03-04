#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxnm=1e6+5,maxn=2005;
int p[maxn][maxn],n,m;

bool check(int x11,int y11,int x22,int y22)
{
	if(x22>n||y22>m||x22<1||y22<1) return 0;
	for(int i=x11;i<x22;++i)
		for(int j=y11;j<y22;++j)
			if(p[i][j]!=p[i+1][j+1]) return 0;
	for(int i=x22;i;--i)
		for(int j=y22;j;--j)
			if(p[i][j]==p[i-1][j-1]) return 0;
	return 1;
}

signed main()
{
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	cin>>n>>m;
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) cin>>p[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;++j)
		{
			for(int l=1;l<=n;++l)
			{
				if(check(i,j,l+i,l+j)) cnt++;
				if(check(i,j,i-l,j-l)) cnt++;
				if(check(i,j,i-l,j+l)) cnt++;
				if(check(i,j,i+l,j-l)) cnt++;
			}
		}
	cout<<cnt/2+n*m;
	return 0;
}
