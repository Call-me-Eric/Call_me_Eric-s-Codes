#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(1);i>=(b);--i)
using namespace std;
const int Maxn=1e6;

int n,m,ans,p,vis[Maxn+5];

int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);	
	
	cin>>n>>m;
	For(i,2,n) if(n%i==0)
	{
		int k=(m/i)*i;
		if(k>ans) ans=k,p=i;
	}
	// cerr<<ans<<' '<<p<<endl;
	For(i,1,p) For(j,1,ans/p) vis[(i-1)*(n/p)+j]=1;
	For(i,1,n) putchar(vis[i]+'0'); putchar('\n');
	return 0;
} 
