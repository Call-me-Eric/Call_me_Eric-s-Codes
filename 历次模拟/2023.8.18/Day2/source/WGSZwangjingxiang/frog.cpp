#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5;
int n,f[N];
struct Node
{
	int a[6],f;
}e[N];
bool check(int x,int y)
{
	for(int i=1;i<=5;i++)
	{
		if(e[x].a[i]>e[y].a[i])return false;
	}
	return true;
}
signed main()
{
	
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=5;j++)
		{
			cin>>e[i].a[j];
		}
		cin>>e[i].f;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<i;j++)
		{
			if(check(j,i))
			{
				f[i]=max(f[i],f[j]);
			}
		}
		f[i]+=e[i].f;
		cout<<f[i]<<endl;
	}
	
}
