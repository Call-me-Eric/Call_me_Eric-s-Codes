#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n,xl[1010],q,c[1010];
struct matrix{
    int m[310][110];
}a,aa;
matrix x(matrix a,matrix b)
{
    matrix t;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
     {
         t.m[i][j]=0;
         for(int k=1;k<=n;k++)
         t.m[i][j]=t.m[i][j]^(a.m[i][k]&b.m[k][j]);
     }
     return t;
}
matrix fm(matrix a,int k)
{
    matrix res;
    for(int i=1;i<=n;i++) 
	for(int j=1;j<=n;j++)
	res.m[i][j]=0;
    for(int i=1;i<=n;i++) res.m[i][i]=1;
    /*for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	printf("%lld ",res.m[i][j]);
   		printf("\n");
	}*/
    while(k>0)
    {
        if(k%2==1) res=x(a,res);
        a=x(a,a);
        k>>=1;
    }
    return res;
}
signed main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
     {
     	scanf("%lld",&a.m[i][j]);
     	aa.m[i][j]=a.m[i][j];
	 }
    for(int i=1;i<=n;i++) scanf("%lld",&xl[i]);
    scanf("%lld",&q);
    while(q--)
    {
    	int k;
    	for(int i=1;i<=n;i++)
     	for(int j=1;j<=n;j++)
     	{
     		a.m[i][j]=aa.m[i][j];
	 	}
	 	memset(c,0,sizeof(c));
    	scanf("%lld",&k);
    	a=fm(a,k);
    	/*for(int i=1;i<=n;i++)
    	{
    		for(int j=1;j<=n;j++)
			printf("%lld ",a.m[i][j]);
			printf("\n"); 
		}*/
    	for(int i=1;i<=n;i++)
    	{
    		c[i]=0;
        	for(int j=1;j<=n;j++)
        	{
        		//printf("c[%lld]=%lld^%lld&%lld\n",i,c[i],a.m[i][j],xl[i]);
        		c[i]^=a.m[i][j]&xl[j];
        		//printf("%lld ",a.m[i][j]);
			}
			printf("%lld",c[i]);
    	}
    	printf("\n");
	}
    return 0;
}
