#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("OK\n")
using namespace std;

const int N=105;
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

const ll lim=2e5+2;
ll n,m;
ll a[N];
ll f[lim][N];

ll find(ll n,ll m){
	if(n==0||m==0) return 0;
	if(n<lim&&f[n][m]!=-1) return f[n][m];
	ll ans=n/a[m]+find(n,m-1)-find(n/a[m],m-1);
	if(n<lim) f[n][m]=ans;
	return ans; 
}
signed main(){

	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	
	memset(f,-1,sizeof(f));
	n=read();m=read();
	for(int i=1;i<=m;i++) a[i]=read();
	//sort(a+1,a+1+m);//make it faster
	printf("%lld\n",n-find(n,m));
	return 0;
}
/*
*/

