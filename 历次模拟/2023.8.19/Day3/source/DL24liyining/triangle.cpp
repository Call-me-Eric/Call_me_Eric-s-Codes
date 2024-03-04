#include <bits/stdc++.h>
using namespace std;

int a[105][105],f[105][105],ans;

int main()
{
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	int n,K;cin>>n>>K;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
//			for(int k=1;k<=K;k++)
//				f[i][j][k]=max(f[i-1][j-1][k],f[i-1][j][k])+a[i][j];
			f[i][j]=max(f[i-1][j-1],f[i-1][j])+a[i][j];
	for(int i=1;i<=n;i++)	
//		for(int k=1;k<=K;k++)
			ans=max(ans,f[n][i]);
	sort(f[n]+1,f[n]+n+1);
	if(K<=4) cout<<ans;
	else cout<<f[n][n-K+1];
	return 0;
}
