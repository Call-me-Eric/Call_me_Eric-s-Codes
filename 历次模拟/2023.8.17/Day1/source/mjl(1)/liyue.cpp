#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
//447 max
int n,q,mx,ans;
int f[N][N];
bool tmp1[N],a[N][N];
signed main()
{
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	n=read();
	mx=sqrt(n*2-1);
	for(int i=1;i<=n;i++)
	{
		int x=read();
		for(int j=1;j<=n;j++)a[i][j]=a[i-1][j];
		a[i][x]=1;
	}
	q=read();
	while(q--)
	{
//		auto xx=clock();
		ans=0;
		int l=read(),r=read();
		if(f[l][r])
		{
			printf("%lld\n",f[l][r]);
			continue;
		}
		for(int i=1;i<=n;i++)tmp1[i]=a[l-1][i]^a[r][i];
		for(int i=2;i<=mx;i++)
			for(int j=1;j*2<i*i;j++)ans+=tmp1[j]&tmp1[i*i-j];
		printf("%lld\n",f[l][r]=ans);
//		cout<<(clock()-xx)*1.0/CLOCKS_PER_SEC<<endl;
	}
	return 0;
}
/*

*/
