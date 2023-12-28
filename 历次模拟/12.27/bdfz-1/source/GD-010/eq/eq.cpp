#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=998244353;
int n,q;
int a[1405][705];
int l[705],lk[705];
int cnt;
int b[705][705],num;
vector<int> hv[705];
int an[705];
int ans[705];
int tans[705];
vector<int> tr[4000];
int pw(int a,int b=p-2)
{
	int re=1;
	while(b)
	{
		if(b&1)	re=re*a%p;
		a=a*a%p;
		b>>=1;
	}
	return re;
}
void add(int nx,int nl,int nr,int cl,int cr,int c)
{
	if(cl>cr)	return;
	if(cl<=nl&&nr<=cr)
	{
		tr[nx].push_back(c);
		return;
	}
	int mid=nl+nr>>1;
	if(cl<=mid)	add(nx*2,nl,mid,cl,cr,c);
	if(cr>mid)	add(nx*2+1,mid+1,nr,cl,cr,c);
	return;
}
void sol(int nx,int nl,int nr)
{
	int bac=num;
	for(int i:tr[nx])
	{
		++num;
//		hv[num].clear();
		for(int j=1;j<=n+1;j++)	b[num][j]=a[i][j];
		for(int i=1;i<num;i++)
		{
			for(int j=n+1;j>=i;j--)	b[num][j]=(b[num][j]-b[num][i]*b[i][j])%p;
		}
		int ok=n+1;
		for(int i=num;i<=n;i++)
		{
			if(b[num][i])
			{
				ok=i;
				break;
			}
		}
		if(ok==n+1)
		{
			if(b[num][n+1])
			{
				for(int i=nl;i<=nr;i++)	cout<<"No\n";
				num=bac;
				return;
			}
			else
			{
				--num;
				continue;
			}
		}
		if(num!=ok)
		{
			for(int i=1;i<=num;i++)	swap(b[i][num],b[i][ok]);
			for(int i=1;i<=n+q;i++)	swap(a[i][num],a[i][ok]);
			swap(an[num],an[ok]);
		}
		int tk=pw(b[num][num]);
		for(int i=num;i<=n+1;i++)	b[num][i]=b[num][i]*tk%p;
//		for(int i=n+1;i>=num;i--)	if(b[num][i])	hv[num].push_back(i);
	}
	if(nl==nr)
	{
		if(num!=n)
		{
			cout<<"Many\n";
			num=bac;
			return;
		}
		for(int i=n;i>=1;i--)
		{
			ans[i]=(b[i][n+1]+p)%p;
			for(int j=n;j>i;j--)	ans[i]=(ans[i]-b[i][j]*ans[j])%p;
			ans[i]=(ans[i]+p)%p;
		}
		for(int i=1;i<=n;i++)
		{
			tans[an[i]]=ans[i];	
		}
		for(int i=1;i<=n;i++)	printf("%lld ",tans[i]);
		putchar('\n');
		num=bac;
		return;
	}
	int mid=nl+nr>>1;
	sol(nx*2,nl,mid);
	sol(nx*2+1,mid+1,nr);
	num=bac;
}
signed main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)
	{
		an[i]=i;
		lk[i]=i;
		for(int j=1;j<=n+1;j++)	scanf("%lld",&a[i][j]);
	}
	cnt=n;
	for(int i=1;i<=q;i++)
	{
		int x;
		scanf("%lld",&x);
		add(1,0,q,l[x],i-1,lk[x]);
		l[x]=i;
		lk[x]=i+n;
		for(int j=1;j<=n+1;j++)	scanf("%lld",&a[i+n][j]);
	}
	for(int i=1;i<=n;i++)
	{
		add(1,0,q,l[i],n,lk[i]);
	}
	sol(1,0,q);
	return 0;
}
