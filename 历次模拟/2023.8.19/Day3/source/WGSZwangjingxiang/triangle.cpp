#include<bits/stdc++.h>
using namespace std;
const int N=10000;
int n,K,now,cnt;
int f[2][105][20005];
int a[105][105];
signed main()
{
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	cin>>n>>K;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=n;i>=1;i--)
	{
		now^=1;
		for(int j=1;j<=i;j++)
		{
			for(int k=-N;k<=N;k++)
				f[now][j][k+N]=0;
			f[now][j][a[i][j]+N]++;
			for(int k=-N;k<=N;k++)
			{
				if(k+N-a[i][j]<0)continue;
				if(k+N-a[i][j]>2*N)continue;
				f[now][j][k+N]+=f[now^1][j][k+N-a[i][j]];
				f[now][j][k+N]+=f[now^1][j+1][k+N-a[i][j]];
				
			}
		}
	}
	for(int i=N;i>=-N;i--)
	{
		cnt+=f[now][1][i+N];
//		cout<<cnt<<endl;
		if(cnt>=K)
		{
			cout<<i;
			return 0;
		}
	}
}
/*
3 3
1
2 -8
4 5 6
*/
