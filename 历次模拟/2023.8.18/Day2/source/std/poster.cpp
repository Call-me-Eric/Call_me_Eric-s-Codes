#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MOD=998244353;
ll ksm(ll a,ll b){
	ll ret=1;a%=MOD;
	for(;b;b>>=1,a=a*a%MOD)if(b&1)ret=ret*a%MOD;
	return ret;
}
ll inv(ll x){return ksm(x,MOD-2);}
int main(){
    freopen("poster.in", "r", stdin);
    freopen("poster.out", "w", stdout);
	ll n,m,t,a,f;
	int T;scanf("%d",&T);
	while(T--){ 
		scanf("%lld%lld",&n,&m);
		a=(MOD+1-2ll*inv(n)%MOD)%MOD;
		t=inv(n);
		f=(ksm(a,m)*(MOD+1-t)%MOD+t)%MOD;
		printf("%lld\n",n%MOD*(MOD+1-f)%MOD);
	}
	return 0;
}
