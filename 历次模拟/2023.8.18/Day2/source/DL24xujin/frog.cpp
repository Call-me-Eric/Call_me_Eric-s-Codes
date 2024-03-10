//frog
//30pts
//n<=10
#include<bits/stdc++.h>
using namespace std;

const int maxn = 11;
int n;
struct node
{
	int a,b,c,d,e,f;
	int id;//Ô­±àºÅ 
}st[maxn];

int ans[maxn][130];
int vis[maxn][maxn];
int res[maxn];
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}
int main()
{  
    freopen("frog.in","r",stdin);
    freopen("frog.out","w",stdout);
	n = read();
	for(int i=1;i<=n;i++)
	{
		st[i].a = read();
		st[i].b = read();
		st[i].c = read();
		st[i].d = read();
		st[i].e = read();
		st[i].f = read();
		st[i].id = i;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=130;j++)
		{
			ans[i][j] = st[i].f;
		}
	}
	for(int i=1;i<=n;i++)
	{
		int pos=0;
		vis[i][i] = 1;
		int A = st[i].a;
		int B = st[i].b;
		int C = st[i].c;
		int D = st[i].d;
		int E = st[i].e;
    for(int k=1;k<=n;k++)
	{
	    for(int j=1;j<=n;j++)
        {
			if(i!=j&&A<=st[j].a&&B<=st[j].b&&C<=st[j].c&&D<=st[j].d&&E<=st[j].e&&vis[i][j]==0) 
			{
				ans[i][++pos]+=st[j].f;
				A = st[j].a;
				B = st[j].b;
				C = st[j].c;
				D = st[j].d;
				E = st[j].e;
				vis[i][j]=1;
			}
		}
	}
	
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=130;j++)
		{
			res[i] = max(ans[i][j],res[i]);
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		cout<<res[i]<<endl;
	}
	return 0;
}
