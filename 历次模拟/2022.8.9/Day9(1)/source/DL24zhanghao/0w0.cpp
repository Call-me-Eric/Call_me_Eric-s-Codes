#include<bits/stdc++.h>
using namespace std;
const int mod=4294967296;
int n,m;
char c[1001];
int a[1001];
int aa[1001][1001];
char s;
int x;
int yy;
char y,z;
int sum;
int sum0;
int ans0;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int qmi(int m,int k,int mod)
{
    int res=1%mod,t=m;
    while(k)
    {
        if(k&1) res=res*t%mod;
        t=t*t%mod;
        k>>=1;
    }
    return res;
}
int main()
{
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		scanf("%c",&c[i]);
	}
	printf("1\n4");
	for(int i=1;i<=m;i++)
	{
		scanf("%c",&s);
		if(s=='A')
		{
			x=read();
			scanf("%c",&y);
			c[x]=y;
		}
		if(s=='B')
		{
			x=read();
			yy=read();
			scanf("%c",&z);
			for(int i=x;i<=yy;y++)
			{
				c[i]=z;
			}
		}
		if(s=='C')
		{
			x=read();
			yy=read();
			int flag=0;
			int color=-1;
			for(int i=x;i<=yy;i++)
			{
				if(c[i]=='(')
				{
					color=1;
					flag++;
					a[i-x+1]=1;
				}
				else if(color==1)
				{
					if(c[i]=='0')
					{
						sum0++;
						flag++;
						a[i-x+1]=2;
					}
					if(c[i]=='w')
					{
						flag++;
						a[i-x+1]=3;
					}
					if(c[i]==')')
					{
						flag++;
						a[i-x+1]=5;
					}
				}
				else
				{
					a[i-x+1]=0;
				}
			}	
			int num=yy-x+1;
			for(int i=1;i<=yy-x+1;i++)
			{
				if(a[i]==0)
				{
					num--;
					for(int j=i+1;j<=yy-x+1;j++)
					{
						a[j-1]=a[j];
					}
				}
			}
			int ans=1;
			ans=qmi(2,sum0,mod);
			ans0=1;
			for(int i=1;i<=num;i++)
			{
				if(a[i]==1||a[i]==3||a[i]==5)
				{
					for(int j=1;j<=ans;j++)
					{
						aa[i][j]=a[i];
						length[i]=ans;
					}
				}
			/*	if(a[i]==2)
				{
					for(int k=1;k<=ans0;k++)
					{
						for(int j=)
					}
					ans0*=2;
				}
			}
			for(int i=1;i<=num;i++)
			{
				for(int j=1;j<=ans;j++)
				{
					
				}
			}*/
			}
		}
	}
}
