//liyue

#include<bits/stdc++.h>
using namespace std;

const int maxn = 100009;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}

int tab[450];//±í 
int a[maxn];
int n,q;

int main()
{
    freopen("liyue.in","r",stdin);
    freopen("liyue.out","w",stdout);
	
	n = read();
	for(int i=1;i<=n;i++)
	{
		tab[i] = i*i;
	}
	for(int i=1;i<=n;i++)
	{
		a[i] = read();
		
	}
	q = read();
	int ans;
    while(q--)
    {
    	ans = 0;
        int l,r;
		l = read();
		r = read();
		
		for(int i=l;i<=r-1;i++)
		{
			for(int j=i+1;j<=r;j++)
			{
				for(int k=2;k<=33;k++)
				{
					if(a[i]+a[j]==tab[k]) ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
