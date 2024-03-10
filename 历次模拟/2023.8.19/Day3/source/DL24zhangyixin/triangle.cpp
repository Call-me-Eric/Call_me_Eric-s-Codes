#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,k,a[N][N];
int f[N][N];
int main()
{
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=1;j<=i;j++)
		{
			f[i][j]=max(f[i+1][j],f[i+1][j+1])+a[i][j];
		}
	}
	printf("%d\n",f[1][1]);
	return 0;
}
