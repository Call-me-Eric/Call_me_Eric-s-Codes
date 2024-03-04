#include<bits/stdc++.h>
using namespace std;
const int N=1e2+5;
int n,m,p[N][N],f[N][N][N];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>p[i][j];
		}
	}
	for(int i=1;i<=n-1;i++)
	{
		for(int j=2;j<=n;j++)
		{
			if(p[i][j-1]==p[i+1][j])
				f[i][j][2]=1;
		}
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=1;j<=n;j++)
		{
			if(i+1>n||j-1<1)continue;
			for(int k=3;k<=min(n-i,j);k++)
			{
				if(f[i][j][k-1]&&f[i][j-1][k-1]&&f[1+1][j][k-1]&&f[i+1][j-1][k-1])
				{
					f[i][j][k]=1;
				}
			}
		}
	}
	
}
