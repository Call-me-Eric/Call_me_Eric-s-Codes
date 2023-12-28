#include <bits/stdc++.h>
using namespace std;

int m;
struct juzhen
{
	int n,m,a[20][20];
	juzhen operator * (juzhen p)
	{
		juzhen ans;ans.n=this->n;ans.m=p.m;
		memset(ans.a,0,sizeof(ans.a));
		for(int i=1;i<=ans.n;i++)
		{
			for(int j=1;j<=ans.m;j++)
			{
				for(int k=1;k<=p.n;k++)
				{
					ans.a[i][j]^=(this->a[i][k]&p.a[k][j]);
				}
			}
		}
		return ans;
	}
}a,b;
juzhen init(juzhen p)
{
	for(int i=1;i<=p.n;i++)
	{
		for(int j=1;j<=p.m;j++)
		{
			if(i==j) p.a[i][j]=1;
			else p.a[i][j]=0;
		}
	}
	return p;
}
juzhen qqpow(juzhen x,int m)
{
	juzhen ans=init(x);
	while(m)
	{
		ans=ans*x;
		if(m&1) x=x*x;
		m>>=1;
	}
	return ans;
}
int main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	cin>>a.n;b.n=a.m=a.n;b.m=1;
	for(int i=1;i<=a.n;i++)
	{
		for(int j=1;j<=a.n;j++)
		{
			char c;cin>>c;
			a.a[i][j]=c-'0';
		}
	}
	for(int i=1;i<=b.n;i++)
	{
		char c;cin>>c;
		b.a[i][1]=c-'0';
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int k;cin>>k;
		juzhen ans=qqpow(a,k)*b;
		for(int i=1;i<=ans.n;i++) cout<<ans.a[i][1];
		cout<<'\n';
	}
	return 0;
}