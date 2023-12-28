#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int a[4003],f[4003][4003][3],t[4003][4];
signed main()
{
#ifndef local
	freopen("sequence.in","r",stdin),
	freopen("sequence.out","w",stdout);
#endif
	int n=read(),ans=0;
	for(int i=1; i<=n; ++i) a[i]=read();
	for(int i=1; i<=n; ++i)
		f[2][i][0]=i-1,f[2][i][1]=1;
	for(int i=2; i<n; ++i)
	{
		for(int j=1; j<=n; ++j)
			f[i+1][j][1]=(f[i+1][j][1]+1ll*a[j]*f[i][j][0])%p,
			f[i+1][j][2]=(f[i+1][j][2]+1ll*a[j]*f[i][j][1])%p;
		for(int j=1; j<=n; ++j)
			t[j][0]=(t[j-1][0]+f[i][j][0])%p,
			t[j][1]=(t[j-1][1]+1ll*f[i][j][1]*j)%p,
			t[j][2]=(t[j-1][2]+1ll*f[i][j][2]*j*j)%p;
		for(int j=n; j>=1; --j)
			t[j][3]=(t[j+1][3]+f[i][j][2])%p;
		for(int j=1; j<=n; ++j)
			f[i+1][j][0]=(f[i+1][j][0]+1ll*a[j]*t[j-1][0])%p,
			f[i+1][j][0]=(f[i+1][j][0]+1ll*a[j]*t[j-1][1])%p,
			f[i+1][j][0]=(f[i+1][j][0]+1ll*a[j]*t[j-1][2])%p;
		for(int j=1; j<=n; ++j)
			f[i+1][j][0]=(f[i+1][j][0]+1ll*a[j]*t[j][3]%p*(j-1)*(j-1))%p,
			f[i+1][j][1]=(f[i+1][j][1]+1ll*a[j]*t[j][3]%p*(j-1))%p,
			f[i+1][j][2]=(f[i+1][j][2]+1ll*a[j]*t[j][3])%p;
	}
	for(int i=1; i<=n; ++i)
		ans=(ans+1ll*f[n][i][2]*i*i
		+1ll*f[n][i][1]*i+f[n][i][0])%p;
	printf("%d\n",ans);
	return 0;
}