#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100100;
int n,k,q,opt,x,y,num;
int a[N][120];
signed main()
{
	freopen("compose.in","r",stdin);
	freopen("compose.out","w",stdout);
	scanf("%lld %lld %lld",&n,&k,&q);
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&a[i][j]);
		}
	}
	num=k;
	while(q--)
	{
		scanf("%lld %lld %lld",&opt,&x,&y);
		if(opt==1)
		{
			num++;
			for(int i=1;i<=n;i++)
			{
				a[num][i]=max(a[x][i],a[y][i]);	
				//printf("change=%lld %lld %lld\n",a[num][i],a[x][i],a[y][i]);
			}	
		}
		if(opt==2)
		{
			num++;
			for(int i=1;i<=n;i++)
			{
				a[num][i]=min(a[x][i],a[y][i]);
			}
		}
		if(opt==3)
		{
			printf("%lld\n",a[x][y]);
		}
	}
	return 0;
}
