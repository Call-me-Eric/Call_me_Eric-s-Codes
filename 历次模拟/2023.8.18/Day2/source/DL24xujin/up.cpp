//up
//70pts
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn = 1009;
int n,q;
int a[maxn*2],b[maxn*2],c[maxn*2],d[maxn*2];
int ans[maxn*2];

inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}

signed main()
{
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	n = read();
	q = read();
	for(int i=1;i<=n;i++)
	{
		a[i] = read();
		b[i] = read();
	}
	for(int i=1;i<=q;i++)
	{
		c[i] = read();
		d[i] = read();
		/*
		if(c[i]>d[i])
		{
			swap(c[i],d[i]);
		}
		*/
	}
   	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=q;j++)
		{
			int x = a[i];
		    int y = b[i];
	        while(true)
	        {
			    //if(x>y) {swap(x,y);}
			    if(x<c[j]||y<d[j]) break;
			    if(x==c[j]&&(y-d[j])%x==0 || y==d[j]&&(x-c[j])%y==0) {++ans[j];break;}
		        if(x>y) x%=y; else y%=x;
		    }
		}
	}
	
	for(int i=1;i<=q;i++)
	{
		printf("%lld\n",ans[i]);
	}
	return 0;
}
