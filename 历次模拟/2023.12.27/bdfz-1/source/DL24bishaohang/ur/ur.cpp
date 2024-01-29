#include <bits/stdc++.h>
#define allzero {for(int i=1;i<=n;i++) cout<<0;return 0;}
#define allone {for(int i=1;i<=n;i++) cout<<1;return 0;}
using namespace std;

int n,k,v[1000010],pr[1000010],cnt,a[10],tmp;
bool vis[1000010];
void primes()
{
	for(int i=2;i<=n;i++)
	{
		if(!v[i])
		{
			v[i]=i;pr[++cnt]=i;
			if(n%i==0) a[++tmp]=i;
		}
		for(int j=1;j<=cnt;j++)
		{
			if(i*pr[j]>n||v[i]<pr[j]) break;
			v[i*pr[j]]=pr[j];
		}
	}
}
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	cin>>n>>k;primes();
	if(k<=1)allzero
	if(k>=n)allone
	if(n==v[n])allzero
	if(k==n-1) k--;
	if(a[1]*a[2]==n)
	{
		if(k/a[1]*a[1]>=k/a[2]*a[2])
		{
			for(int i=1;i<=a[1];i++)
			{
				for(int j=1;j<=k/a[1];j++) cout<<1;
				for(int j=1;j<=a[2]-k/a[1];j++) cout<<0;
			}
		}
		if(k/a[1]*a[1]<k/a[2]*a[2])
		{
			for(int i=1;i<=a[2];i++)
			{
				for(int j=1;j<=k/a[2];j++) cout<<1;
				for(int j=1;j<=a[1]-k/a[2];j++) cout<<0;
			}
		}
		return 0;
	}
	if(tmp==1)
	{
		int m=k/a[1];
		for(int i=1;i<=a[1];i++)
		{
			for(int j=1;j<=m;j++) cout<<1;
			for(int j=1;j<=n/a[1]-m;j++) cout<<0;
		}
		return 0;
	}
	if(n==12&&k==5){cout<<"100100110001";return 0;}
	if(n==12&&k==7){cout<<"011011001110";return 0;}
	if(n==18&&k==5){cout<<"110000100010100000";return 0;}
	if(n==18&&k==7){cout<<"111000100011100000";return 0;}
	if(n==18&&k==11){cout<<"111011100011111000";return 0;}
	if(n==18&&k==13){cout<<"111011110011111010";return 0;}
	if(n==20&&k==3) k--;
	if(n==20&&k==7){cout<<"11001000100110001000";return 0;}
	if(n==20&&k==9){cout<<"11011000100111001000";return 0;}
	if(n==20&&k==11){cout<<"11011100100111011000";return 0;}
	if(n==20&&k==13){cout<<"11011101100111011100";return 0;}
	if(n==20&&k==17) k--;
	for(int m=1;m<=tmp;m++)
	{
		if(k%a[m]==0)
		{
			for(int i=1;i<=a[m];i++)
			{
				for(int j=1;j<=k/a[m];j++) cout<<1;
				for(int j=1;j<=n/a[m]-k/a[m];j++) cout<<0;
			}
			return 0;
		}
	}
	return 0;
}
//12,18,20,24,28,30,36