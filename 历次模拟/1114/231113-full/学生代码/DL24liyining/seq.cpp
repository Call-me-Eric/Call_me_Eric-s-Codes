#include <bits/stdc++.h>
using namespace std;

const int maxn=3e5+5;
int a[maxn];
bool s[505][505][505];

int main()
{
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	int n,Q;cin>>n>>Q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) s[a[i]][i][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=i;k<=j;k++) s[a[k]][i][j]=1;
	while(Q--)
	{
		int L,R;cin>>L>>R;
		int sum=0;
		for(int i=L;i<=R;i++)
			for(int j=i+1;j<=R;j++)
			{
				int ans=0;
				for(int k=i;k<=j;k++)
					if((!s[a[k]][1][max(j-1,1)])&&(!s[a[k]][min(j+1,n)][n])) ans=max(ans,a[k]);
				sum+=ans;
			}
		cout<<sum<<'\n';
	}
	return 0;
}
