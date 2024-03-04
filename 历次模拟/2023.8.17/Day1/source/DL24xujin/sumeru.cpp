//sumeru
//30pts 
//0<=a(i,j)<=4
//T<=1000
#include<bits/stdc++.h>
using namespace std;

int a1[4],a2[4],a3[4],a4[4];
int x1,x2,x3;
int T;

inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}
int main()
{
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
	T = read();
	int pos;
	while(T--)
	{
		pos = 0;
		for(int i=1;i<=3;i++)
		{
			a1[i] = read();
		}
		for(int i=1;i<=3;i++)
		{
			a2[i] = read();
		}
		for(int i=1;i<=3;i++)
		{
			a3[i] = read();
		}
		for(int i=1;i<=3;i++)
		{
			a4[i] = read();
		}
		
		for(int i=0;i<=4;i++)
		{
			for(int j=0;j<=4;j++)
			{
				for(int k=0;k<=4;k++)
				{
					if(i*a1[1]+j*a2[1]+k*a3[1]==a4[1] && i*a1[2]+j*a2[2]+k*a3[2]==a4[2] && i*a1[3]+j*a2[3]+k*a3[3]==a4[3])
					{
						pos++;
					}
				}	
			}
		}
		
		if(pos==0)
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
	return 0;
}
