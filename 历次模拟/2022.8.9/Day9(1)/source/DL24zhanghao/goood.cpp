#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int aa[6001][6001];
int cc[6001][6001];
int u,v;
int sum;
int flag=-1;
int bb[5001];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void init(int i)
{
	if(i>n)
	{
		return ;
	}
	for(register int j=1;j<=n;j++)
	{
		if(aa[i][j]==1)
		{
			for(register int k=1;k<=n;k++)
			{
				if(i==k)
				{
					continue;
				}
				if(aa[j][k]==1)
				{
					aa[i][k]=1;
				}
			}
		}
	}
	init(i+1);
}
void init2(int i)
{
	if(i>n)
	{
		return ;
	}
	for(register int j=1;j<=n;j++)
	{
		if(cc[i][j]==1)
		{
			for(register int k=1;k<=n;k++)
			{
				if(i==k)
				{
					continue;
				}
				if(cc[j][k]==1)
				{
					cc[i][k]=1;
				}
			}
		}
	}
	init2(i+1);
}
signed main()
{
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	n=read();
	m=read();
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			aa[i][j]=0;
			cc[i][j]=0;
		}
	}
	for(register int i=1;i<=m;i++)
	{
		u=read();
		v=read();
		aa[u][v]=1;
		cc[v][u]=1;
	}
	/*
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d ",aa[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d ",cc[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	*/
	init(1);
	init2(1);
	/*
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d ",aa[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d ",cc[i][j]);
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
			if(cc[i][j]==1)
			{
				aa[i][j]=1;
			}
		}
	}
	/*
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d ",aa[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d ",cc[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	*/
	for(register int i=1;i<=n;i++)
	{
		aa[i][i]=1;
		cc[i][i]=1;
	}
	/*
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d ",aa[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d ",cc[i][j]);
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
			if(aa[i][j]!=1)
			{
				flag=-1;
				break;
			}
			else
			{
				flag=1;
			}
		}
		if(flag==1)
		{
			sum++;
			bb[i]=1;
			flag=-1;
		}
	}
	printf("%lld\n",sum);
	for(register int i=1;i<=n;i++)
	{
		if(bb[i]==1)
		{
			printf("%lld ",i);
		}
	}
	return 0;
}
