#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
inline int read()
{
	int n=0,f=1,ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		n=n*10+ch-'0';
		ch=getchar();
	}
	return n*f;
}
int a[65],b[65];
int na[65],len;
int n,m;
unordered_map<long long,int>ma;
int jdz(int x)
{
	if(x<0)return -x;
	return x;
}
int k;
int dfs(int cs)
{
	int minc=0;
	for(int i=1;i<=len;i++)assert(na[i]>=0&&na[i]>=na[i+1]);
	for(int i=1;i<=max(len,m);i++)minc+=jdz(na[i]-b[i]);
	if(minc>cs)return 0;
	if(cs==0&&len!=m)return 0;
	if(cs==0)return 1;
	long long zt=0;
	for(int i=1;i<=len;i++)zt|=(1LL<<(na[i]+len-i));
	zt=zt*(k+1)+cs;
	if(ma.count(zt))return ma[zt];
	int nans=0;
	for(int i=len;i>=1;i--)
	{
		if(na[i]==na[i-1])continue;
		na[i]++;
		nans=(nans+dfs(cs-1))%mod;
		na[i]--;
	}
	na[len+1]++;
	len++;
	nans=(nans+dfs(cs-1))%mod;
	len--;
	na[len+1]--;
	for(int i=len;i>=1;i--)
	{
		if(na[i]==na[i+1])continue;
		na[i]--;
		int plen=len;
		if(na[i]==0&&i==len)len--;
		nans=(nans+dfs(cs-1))%mod;
		na[i]++;
		len=plen;
	}
	return nans;
}
signed main()
{
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	int q;
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	m=read();
	for(int i=1;i<=m;i++)b[i]=read();
	q=read();
	for(int i=1;i<=q;i++)
	{
		k=read();
		na[0]=1000000000;
		len=n;
		for(int j=1;j<=len;j++)na[j]=a[j];
		printf("%d\n",dfs(k));
	}
}
