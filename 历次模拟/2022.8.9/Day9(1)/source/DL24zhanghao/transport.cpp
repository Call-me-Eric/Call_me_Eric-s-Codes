#include<bits/stdc++.h>
using namespace std;
int n;
int u,v,w;
int a[10001];
int aa[10001][10001];
//int a=new int[n];
//int aa=new int[n][n];
int sum;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void dfs(int qq)
{
	if(qq>n)
	{
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(aa[qq][i]!=-0x3f3f3f)
		{
			for(int j=1;j<=n;j++)
			{
				if(qq==j)
				{
					continue;
				}
				if(aa[i][j]!=-0x3f3f3f&&aa[i][j]+aa[qq][i]>=0)
				{
					aa[qq][j]=max(aa[qq][j],aa[qq][i]+aa[i][j]);
					/*
					for(int i=1;i<=n;i++)
					{
						for(int j=1;j<=n;j++)
						{
							printf("%10d ",aa[i][j]);
						}
						printf("\n");
					}
					printf("\n");
					printf("\n");
					*/
				}
			}
		}
	}
	dfs(qq+1);
}
signed main()
{
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	n=read();
	for(register int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			aa[i][j]=-0x3f3f3f;
		}
	}
	/*
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			printf("%10d ",aa[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	*/
	for(register int i=1;i<n;i++)
	{
		u=read();
		v=read();
		w=read();
		aa[u][v]=a[u]-w;
		aa[v][u]=a[v]-w;
	}
	/*
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			printf("%10d ",aa[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	*/
	dfs(1);
	/*
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			printf("%10d ",aa[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	*/
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			if(aa[i][j]>=0)
			{
				sum++;
			}
		}
	}
	printf("%d",sum);
	return 0;
}
