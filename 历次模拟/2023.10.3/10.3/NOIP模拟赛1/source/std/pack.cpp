#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
int n,m;
long long k,p,s[100010],w[100010];
struct orz
{
	long long a,b;
}x[100010];
inline bool cmp(orz a,orz b)
{
	return a.a<b.a || a.a==b.a && a.b<b.b;
}
inline int search(int r)
{
	int l;
	for(l=1;l<r;)
	  if(x[l+r+1>>1].a<=k)
	    l=(l+r+1>>1);
	  else
	    r=(l+r+1>>1)-1;
	return l;
}
inline int search2(int i)
{
	int l,r;
	for(l=0,r=i-1;l<r;)
	  if(s[i]-s[l+r>>1]<=k)
	    r=(l+r>>1);
	  else
	    l=(l+r>>1)+1;
	return l;
}
int main()
{
	freopen("pack.in","r",stdin);
	freopen("pack.out","w",stdout);
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	  scanf("%lld%lld",&x[i].a,&x[i].b);
	sort(x+1,x+n+1,cmp);
	for(i=1;i<=n;i++)
	  {
	   s[i]=s[i-1]+x[i].a;
	   w[i]=w[i-1]+x[i].b;
	  }
	while(m--)
	  {
	   scanf("%lld",&k);
	   p=0;
	   for(i=n;i && k>=x[1].a;i=j)
	     {
	      i=search(i);
	      j=search2(i);
	      k-=s[i]-s[j];
	      p+=w[i]-w[j];
		 }
	   printf("%lld\n",p);
	  }
	return 0;
}

