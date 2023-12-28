#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=1e9+7,H=(p+1)>>1;
int h[9]={1},a[9];
vector<int> e[100003],g[100003];
int d[100003],id[100003],pos[100003],lst[100003];
int calc(int n)
{
	int ans=0;
	for(int i=1; i<=n; ++i) id[i]=i;
	sort(id+1,id+n+1,[&](int x,int y){return d[x]>d[y];});
	for(int i=1; i<=n; ++i) pos[id[i]]=i;
	for(int i=1; i<=n; ++i)
		for(int j:e[i])
			g[pos[i]].push_back(pos[j]);
	for(int i=1; i<=n; ++i)
	{
		for(int j:g[i]) lst[j]=i;
		for(int j:g[i]) if(j>i)
			for(int k:g[j]) if(k>j)
				ans+=(lst[k]==i); 
	}
	return ans;
}
signed main()
{
#ifndef local
	freopen("graph.in","r",stdin),
	freopen("graph.out","w",stdout);
#endif
	int n=read(),m=read(),k=read(),S=1,ans=0;
	for(int i=1; i<=6; ++i) h[i]=1ll*h[i-1]*H%p;
	for(int i=1; i<=n; ++i) S=(S<<1)%p;
	if(k==1) printf("%lld\n",1ll*S*h[2]%p*m%p),exit(0);
	for(int i=1,u,v; i<=m; ++i)
		u=read(),v=read(),
		++d[u],++d[v],
		e[u].push_back(v),
		e[v].push_back(u);
	a[2]=m;
	for(int i=1; i<=n; ++i)
		a[3]=(a[3]+1ll*d[i]*(d[i]-1))%p;
	a[4]=(p+1ll*m*m-a[3])%p,
	a[4]=(p+a[4]-a[2])%p;
	if(k==2)
	{
		for(int i=2; i<=4; ++i)
			ans=(ans+1ll*a[i]*h[i])%p;
		printf("%lld\n",1ll*S*ans%p);
		return 0;
	}
	int R=calc(n);
	a[3]=(3ll*a[3]+6ll*R)%p,a[4]=3ll*a[4]%p;
	for(int i=1; i<=n; ++i)
		a[4]=(a[4]+1ll*d[i]*(d[i]-1)*(d[i]-2))%p;
	for(int i=1; i<=n; ++i)
		for(int j:e[i]) if(j>i)
			a[4]=(a[4]+6ll*(d[i]-1)*(d[j]-1))%p,
			a[5]=(a[5]+p-12ll*(d[i]-1)*(d[j]-1)%p)%p;
	for(int i=1; i<=n; ++i)
		a[5]=(a[5]+3ll*d[i]*(d[i]-1)*(m-d[i]))%p;
	a[4]=(a[4]+p-18ll*R%p)%p,
	a[5]=(a[5]+p+18ll*R%p)%p,
	a[6]=1ll*m*m%p*m%p;
	for(int i=2; i<6; ++i)
		a[6]=(a[6]+p-a[i])%p;
	for(int i=2; i<=6; ++i)
		ans=(ans+1ll*a[i]*h[i])%p;
	printf("%lld\n",1ll*S*ans%p);
	return 0;
}