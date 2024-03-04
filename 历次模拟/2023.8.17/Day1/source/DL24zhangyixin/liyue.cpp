#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,a[N],q,l,r,cnt,sum;
int main()
{
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int ans=0;
		scanf("%d %d",&l,&r);
		for(int i=l;i<=r;i++)
		{
			for(int j=i+1;j<=r;j++)
			{
				sum=a[i]+a[j];
				cnt=sqrt(a[i]+a[j]);
				if(sum==cnt*cnt) ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
