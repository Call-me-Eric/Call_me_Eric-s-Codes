#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,sq[N],tot;
int block,belong[N];
int a[N],cnt[N],ans,m;
struct Ques
{
	int l,r,ans,id;
	bool operator<(Ques x)const
	{
		return id<x.id;
	}
}q[N];
void pre()
{
	for(int i=1;i*i<=n*2;i++)
	{
		sq[++tot]=i*i;
	}
}
bool cmp(Ques x,Ques y)
{
	if(belong[x.l]==belong[y.l])return x.r<y.r;
	return x.l<y.l;
}
void add(int x)
{
	x=a[x];
	for(int i=tot;i>=1;i--)
	{
		if(sq[i]-x<0)break;
		ans+=cnt[sq[i]-x];
	}
	cnt[x]++;
}
void del(int x)
{
	x=a[x];
	cnt[x]--;
	for(int i=tot;i>=1;i--)
	{
		if(sq[i]-x<0)break;
		ans-=cnt[sq[i]-x];
	}
}
signed main()
{
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	cin>>n;
	pre();
	block=sqrt(n);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		belong[i]=(i-1)/block+1;
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+1+m,cmp);
	for(int i=1,l=1,r=0;i<=m;i++)
	{
		while(r<q[i].r)add(++r);
		while(l>q[i].l)add(--l);
		while(r>q[i].r)del(r--);
		while(l<q[i].l)del(l++);
		q[i].ans=ans;
	}
	sort(q+1,q+1+m);
	for(int i=1;i<=m;i++)
	{
		cout<<q[i].ans<<endl;
	}
}
