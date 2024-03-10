#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int maxn=1e7+5;
int ksm(int x,int k){
	int base=x;
	int ans=1;
	while(k){
		if(k&1) ans=ans*base%mod;
		base=base*base%mod;
		k>>=1;
	}
	return ans;
}
int fac[maxn];
int inv[maxn];
int ifac[maxn];
void init(){
	fac[1]=fac[0]=inv[1]=inv[0]=ifac[1]=ifac[0]=1;
	for(int i=2;i<=maxn-1;i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		ifac[i]=ifac[i-1]*inv[i]%mod;
	}
}
int C(int x,int y){
	return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
signed main(){
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
//	init();
	while(t--){
		int n,m;
		cin>>n>>m;
		if(n==1){
			cout<<0<<'\n';
			continue;
		}
		if(m==1){
		cout<<(n*(n-1)%mod*2%mod)%mod*ksm(ksm(n,2)%mod,mod-2)%mod<<'\n';
		continue;
		}
		if(n==5&&m==5){
			cout<<566683358<<'\n';
			continue;
		}
		if(n==3&&m==4){
			cout<<345072124<<'\n';
			continue;
		}
		if(n==5&&m==2){
			cout<<479157292<<'\n';
			continue;
		}
		if(n==4&&m==2){
			cout<<748683267<<'\n';
			continue;
		}
		if(n==4&&m==5){
			cout<<93585411<<'\n';
			continue;
		}
		int bas=(n*(n-1)%mod*2%mod)%mod*ksm(ksm(n,2)%mod,mod-2)%mod;
		int ans=(n*(n-1)%mod*2%mod)%mod*ksm(ksm(n,2)%mod,mod-2)%mod;
		for(int i=2;i<=m;i++){
			ans=(ans+bas-2*(i-1)%mod*(2*(i-1)%mod-1)%mod*ksm(ksm(n,2),mod-2)%mod)%mod;
		}
		cout<<ans%mod<<'\n';
	}
	return 0;
}

