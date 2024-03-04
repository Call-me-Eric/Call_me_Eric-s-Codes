#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define inf 1000000000
using namespace std;
int n,x[100010],p,q;
struct lr
{
    int l,r;
}f[400010];
struct orz
{
    lr x[100010];
}a[20],b,c;
inline lr merge(lr a,lr b)
{
    lr c;
    c.l=min(a.l,b.l);
    c.r=max(a.r,b.r);
    return c;
}
inline lr query(int i,int j,int k,int l,int r)
{
    if(l<=j && k<=r)
      return f[i];
    else
      {
       lr w;
       w.l=inf;
       w.r=-inf;
       if(l<=(j+k>>1))
         w=merge(w,query(i<<1,j,j+k>>1,l,r));
       if(r>(j+k>>1))
         w=merge(w,query(i<<1|1,(j+k>>1)+1,k,l,r));
       return w;
      }
}
inline void calc(orz &a,orz b,orz c)
{
    int i;
    for(i=1;i<=n;i++)
      f[p+i-1]=b.x[i];
    for(i=p+n;i<(p<<1);i++)
      {
       f[i].l=inf;
       f[i].r=-inf;
      }
    for(i=p-1;i>0;i--)
      f[i]=merge(f[i<<1],f[i<<1|1]);
    for(i=1;i<=n;i++)
      a.x[i]=query(1,1,p,c.x[i].l,c.x[i].r);
}
inline bool check(orz a)
{
    int i;
    x[0]=inf;
    for(i=1;i<=n;i++)
      {
       if(x[a.x[i].l-1]<i)
         return 1;
       x[i]=min(x[i-1],a.x[i].r);
      }
    return 0;
}
int main()
{
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	int i;
	scanf("%d",&n);
	for(p=1;p<n;p<<=1);
	for(i=1;i<=n;i++)
	  {
	   scanf("%d",&x[i]);
	   a[0].x[i].l=max(i-x[i],1);
	   a[0].x[i].r=min(i+x[i],n);
	   b.x[i].l=b.x[i].r=i;
      }
	for(i=1;i<=17;i++)
	  calc(a[i],a[i-1],a[i-1]);
	for(i=17;i>=0;i--)
	  {
       calc(c,a[i],b);
       if(check(c))
         {
          b=c;
          q+=1<<i;
         }
      }
    printf("%d\n",q+1);
	return 0;
}

