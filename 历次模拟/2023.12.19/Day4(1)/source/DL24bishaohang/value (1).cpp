#include <bits/stdc++.h>
using namespace std;

int n,ans;
struct dian
{
	int va,vb;
}a[150010];
bool cmp(dian x,dian y)
{
	return x.va>y.va;
}
int main()
{
	freopen("value.in","r",stdin);
	freopen("value.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].va>>a[i].vb;
	if(n<=3000)
	{
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				int cnt=0;
				for(int k=j;k<=n;k++)
				{
					if(a[k].vb>=a[j].vb) cnt++;
				}
				ans=max(ans,a[i].va*i+a[j].vb*cnt);
			}
		}
		cout<<ans;
	}
}