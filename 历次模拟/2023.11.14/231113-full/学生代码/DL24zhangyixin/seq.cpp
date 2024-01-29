#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=300010;
int n,q,a[N],l,r;
int mx[N],mn[N];
int ans[5010][5010],cnt=0,num[5010][5010];
signed main()
{
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	scanf("%lld %lld",&n,&q);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]); 
	for(int i=1;i<=n;i++) mn[i]=0x3f3f3f3f3f3f3f3f;
	for(int i=1;i<=n;i++) mn[a[i]]=min(mn[a[i]],i);
	for(int i=n;i>=1;i--) mx[a[i]]=max(mx[a[i]],i);
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			for(int k=i;k<=j;k++)
			{
				if(mn[a[k]]>=i&&mx[a[k]]<=j) cnt=max(cnt,a[k]);
			}
			num[i][j]=cnt;
			cnt=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=i;k<=j;k++)
			{
				for(int s=k;s<=j;s++)
				{
					ans[i][j]+=num[k][s];
				}
			}
		}
	}
	while(q--)
	{
		scanf("%lld %lld",&l,&r);
		printf("%lld\n",ans[l][r]);
	}
	return 0;
}
