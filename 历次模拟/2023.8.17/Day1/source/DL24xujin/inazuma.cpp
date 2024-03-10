//inazuma
//20pts n<=10 m<=20
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}

int n,m;
int a[211][211];//矩阵存 
int pos[211];//判断每个点的连边数量 
int main()
{
	freopen("inazuma.in","r",stdin);
	freopen("inazuma.out","w",stdout);
	n = read();
	m = read();
	for(int i=1;i<=m;i++)
	{
		int u,v,d;
		u = read(),v = read(),d = read();
		a[u][v] += d;
		a[v][u] += d;
		pos[u]++,pos[v]++;
	}
	
	int ans = 1000009;
	for(int i=1;i<=n;i++)
	{
		if(pos[i]==1)
		{
			for(int j=1;j<=n;j++)
			{
				if(a[i][j]!=0)
				{
					ans = min(ans,a[i][j]);
				}
			}
		}
	}
    
    for(int i=1;i<=n;i++)
    {
    	int res1=0,res2=0;
    	int tes=0;
    	if(pos[i]==2)
    	{
    		for(int j=1;j<=n;j++)
    		{
    			if(a[i][j]!=0&&tes==0)
    			{
    				res1 = a[i][j];
    				tes=1;
				}
				if(a[i][j]!=0&&tes==1)
				{
					res2 = a[i][j];
				}
			}
			ans = min(ans,res1+res2);
		}
	}
	
	for(int i=1;i<=n;i++)
    {
    	int res1=0,res2=0,res3=0;
    	int tes=0;
    	if(pos[i]==3)
    	{
    		for(int j=1;j<=n;j++)
    		{
    			if(a[i][j]!=0&&tes==0)
    			{
    				res1 = a[i][j];
    				tes=1;
				}
				if(a[i][j]!=0&&tes==1)
				{
					res2 = a[i][j];
					tes=2;
				}
				if(a[i][j]!=0&&tes==2)
				{
					res3 = a[i][j];
				}
			}
			ans = min(ans,res1+res2+res3);
		}
	}
	for(int i=1;i<=n;i++)
    {
    	int res1=0,res2=0,res3=0,res4=0;
    	int tes=0;
    	if(pos[i]==4)
    	{
    		for(int j=1;j<=n;j++)
    		{
    			if(a[i][j]!=0&&tes==0)
    			{
    				res1 = a[i][j];
    				tes=1;
				}
				if(a[i][j]!=0&&tes==1)
				{
					res2 = a[i][j];
					tes=2;
				}
				if(a[i][j]!=0&&tes==2)
				{
					res3 = a[i][j];
					tes=3;
				}
				if(a[i][j]!=0&&tes==3)
				{
					res4 = a[i][j];
				}
			}
			ans = min(ans,res1+res2+res3+res4);
		}
	}
	for(int i=1;i<=n;i++)
    {
    	int res1=0,res2=0,res3=0,res4=0,res5=0;
    	int tes=0;
    	if(pos[i]==5)
    	{
    		for(int j=1;j<=n;j++)
    		{
    			if(a[i][j]!=0&&tes==0)
    			{
    				res1 = a[i][j];
    				tes=1;
				}
				if(a[i][j]!=0&&tes==1)
				{
					res2 = a[i][j];
					tes=2;
				}
				if(a[i][j]!=0&&tes==2)
				{
					res3 = a[i][j];
					tes=3;
				}
				if(a[i][j]!=0&&tes==3)
				{
					res4 = a[i][j];
					tes=4;
				}
				if(a[i][j]!=0&&tes==4)
				{
					res5 = a[i][j];
				}
			}
			ans = min(ans,res1+res2+res3+res4+res5);
		}
	}
	for(int i=1;i<=n;i++)
    {
    	int res1=0,res2=0,res3=0,res4=0,res5=0,res6=0;
    	int tes=0;
    	if(pos[i]==6)
    	{
    		for(int j=1;j<=n;j++)
    		{
    			if(a[i][j]!=0&&tes==0)
    			{
    				res1 = a[i][j];
    				tes=1;
				}
				if(a[i][j]!=0&&tes==1)
				{
					res2 = a[i][j];
					tes=2;
				}
				if(a[i][j]!=0&&tes==2)
				{
					res3 = a[i][j];
					tes=3;
				}
				if(a[i][j]!=0&&tes==3)
				{
					res4 = a[i][j];
					tes=4;
				}
				if(a[i][j]!=0&&tes==4)
				{
					res5 = a[i][j];
					tes=5;
				}
				if(a[i][j]!=0&&tes==5)
				{
					res5 = a[i][j];
				}
			}
			ans = min(ans,res1+res2+res3+res4+res5+res6);
		}
	}
	printf("%d",ans);
	return 0;
}
