#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("OK\n")
using namespace std;

const int N=505;
const int mod=1e9+7;
const int inf=1e9;
inline ll read(){
	ll x(0),f(1);char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}

inline ll ksm(ll x,ll k){
	ll res=1;
	while(k){
		if(k&1) res=res*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return res;
}

#define add(x,y) ((((x)+=(y))>=mod)&&((x)-=mod))
int n,m;
ll f[N][N];
ll mi[N*N];
inline ll Sum(int a,int b){
	return (a+b)*(b-a+1)/2;
}

signed main(){

	freopen("seg.in","r",stdin);
	freopen("seg.out","w",stdout);

	n=read();m=read();
	mi[0]=1;
	for(int i=1;i<=n*n;i++) mi[i]=mi[i-1]*2%mod;
	f[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			for(int k=i+1;k<=n;k++){
				add(f[k][j+1],f[i][j]*(mi[k-i]+mod-1)%mod*mi[(n-k)*(k-i)]%mod);
			}
		}
	}
	ll ans(0);
	for(int i=0;i<=n;i++) add(ans,f[i][m]);
	printf("%lld\n",ans);
	return 0;
}
/*
*/

