#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define inf 1000000000000000000ll
#define pb push_back
using namespace std;
int n,x[100010];
L f[100010][3];
vector<int> a[100010],b[100010];
inline void dp(int i,int j)
{
    int k,l,u;
    if(x[i])
      f[i][0]=f[i][x[i]^3]=inf;
    for(k=0;k<a[i].size();k++)
      if(a[i][k]!=j)
        {
         dp(a[i][k],i);
         f[i][0]=f[i][0]+min(f[a[i][k]][0],min(f[a[i][k]][1],f[a[i][k]][2])+b[i][k]);
         for(l=1;l<=2;l++)
           f[i][l]=f[i][l]+min(f[a[i][k]][l],f[a[i][k]][l^3]+b[i][k]);
        }
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int i,j,k,l;
	scanf("%d",&n);
	for(i=1;i<n;i++)
	  {
       scanf("%d%d%d",&j,&k,&l);
       a[j].pb(k);
       b[j].pb(l);
       a[k].pb(j);
       b[k].pb(l);
      }
    scanf("%d",&k);
    for(i=1;i<=k;i++)
      {
       scanf("%d",&j);
       x[j]=1;
      }
    scanf("%d",&k);
    for(i=1;i<=k;i++)
      {
       scanf("%d",&j);
       x[j]=2;
      }
    dp(1,0);
    printf("%lld\n",min(f[1][0],min(f[1][1],f[1][2])));
	return 0;
}

