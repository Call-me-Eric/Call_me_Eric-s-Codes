#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define inf 1000000000000000000ll
using namespace std;
int n,m,mx,my,a[1010],b[10010],c[10010],d[10010],e[10010],g[1000010],h[1010],t[1010],x[1010],y[1010],q,r;
long long f[1010],p;
bool z[1010];
inline void add_(int i,int j,int k,int l)
{
    b[++r]=j;
    c[r]=k;
    d[r]=l;
    e[r]=a[i];
    a[i]=r;
}
inline void add(int i,int j,int k,int l)
{
    add_(i,j,k,l);
    add_(j,i,0,-l);
}
inline void spfa()
{
    int i,j;
    for(i=1;i<=n+1;i++)
      {
       f[i]=-inf;
       z[i]=0;
      }
    q=1;
    z[0]=1;
    for(i=1;i<=q;i++)
      {
       for(j=a[g[i]];j>0;j=e[j])
         if(c[j] && f[g[i]]+d[j]>f[b[j]])
           {
            f[b[j]]=f[g[i]]+d[j];
            h[b[j]]=g[i];
            t[b[j]]=j;
            if(!z[b[j]])
              {
               g[++q]=b[j];
               z[b[j]]=1;
              }
           }
       z[g[i]]=0;
      }
    if(f[n+1]==-inf)
      return;
    p+=f[n+1];
    for(i=n+1;i>0;i=h[i])
      {
       c[t[i]]--;
       c[(t[i]-1^1)+1]++;
      }
    spfa();
}
int main()
{
	freopen("delight.in","r",stdin);
	freopen("delight.out","w",stdout);
	int i,j;
	scanf("%d%d%d%d",&n,&m,&mx,&my);
	for(i=1;i<=n;i++)
	  scanf("%d",&x[i]);
	for(i=1;i<=n;i++)
	  {
	   scanf("%d",&y[i]);
	   p+=y[i];
      }
    add(0,1,m-my,0);
    for(i=1;i<=n;i++)
      {
       add(i,i+1,m-my-(i>=m)*mx,0);
       add(i,min(i+m,n+1),1,x[i]-y[i]);
      }
    spfa();
    printf("%lld\n",p);
	return 0;
}

