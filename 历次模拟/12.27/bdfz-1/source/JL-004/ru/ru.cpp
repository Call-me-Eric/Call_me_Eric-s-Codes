#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("ru.in","r",stdin);
	freopen("ru.out","w",stdout);
	int n,k,mx=1,ans=0;cin>>n>>k;
	for(int i=2;i<=n;i++)
	{
		if(n%i==0)
		{
			for(int j=i;j<=n;j+=i)
			if(j<=k&&j>ans)
			{
				ans=j;
				mx=i;
			}
		}
	}
	for(int i=1;i<=mx;i++)
	{
		for(int j=1;j<=ans/mx;j++) putchar('1');
		for(int j=ans/mx+1;j<=n/mx;j++) putchar('0');
	}
	return 0;
}
