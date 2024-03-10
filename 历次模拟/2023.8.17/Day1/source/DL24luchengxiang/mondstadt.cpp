#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
const int N=1e6+5;
const int mod=1e9+7;
int n,m,cnt[N],u,v,tot[N];
ll fac[N],inv[N],ans;
ll C(int n,int m){
	if(n<m)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n==1){puts("1");return 0;}
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=((mod-mod/i)*inv[mod%i]+mod)%mod;
	}
	for(int i=2;i<=n;i++)inv[i]=inv[i]*inv[i-1]%mod;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		cnt[u]++,cnt[v]++;
	}
	if(n==2){
		for(int i=1;i<=n;i++){
			tot[2]=(tot[2]+C(cnt[i],2))%mod;
		}
		printf("%lld\n",tot[2]);
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=min(cnt[i],n-1);j++){
			tot[j]=(tot[j]+C(cnt[i],j))%mod;
		}
	}
	for(int i=2;i<=n-1;i++)ans^=tot[i];
	printf("%lld\n",ans);
	return 0;
}

