#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=1e6+5, Mod=1e9+7;

int n, m, deg[N], ans[N];

int fac[N], ifac[N];

int qpow(int a, int b){
	int re=1; for(; b; b>>=1, a=a*a%Mod) if(b&1) re=re*a%Mod;
	return re;
}
int inv(int a){
	return qpow(a, Mod-2);
}

void init(){
	fac[0]=1; for(int i=1; i<=n; i++) fac[i]=fac[i-1]*i%Mod;
	ifac[n]=inv(fac[n]); for(int i=n-1; ~i; i--) ifac[i]=ifac[i+1]*(i+1)%Mod;
}

int C(int a, int b){
	return fac[a]*ifac[b]%Mod*ifac[a-b]%Mod;
}

signed main(){
	freopen("mondstadt.in", "r", stdin);
	freopen("mondstadt.out", "w", stdout);
	n=rd(), m=rd();
	init();
	
	for(int i=1, u, v; i<=m; i++){
		u=rd(), v=rd();
		deg[u]++, deg[v]++;
	}
	
	for(int i=1; i<=n; i++){
		for(int j=2; j<=deg[i]; j++){
			ans[j]=(ans[j]+C(deg[i], j))%Mod;
		}
	}
	
	int Ans=0;
	for(int i=2; i<=n; i++) Ans^=ans[i];
	printf("%lld\n", Ans);
	return 0;
}
/*
4 6
1 2
1 3
1 4
2 3
2 4
3 4
*/
