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
const int Mod=998244353;

inline int qpow(int a, int b){
	int re=1; for(; b; b>>=1, a=a*a%Mod) if(b&1) re=re*a%Mod;
	return re;
}
inline int inv(int a){return qpow(a, Mod-2);}
inline int frac(int a, int b){return a*inv(b)%Mod;}

int T, n, m;

struct Matrix{
	int c[2][2];
	Matrix(bool if_bas=0){
		memset(c, 0, sizeof(c));
		if(if_bas) c[0][0]=c[1][1]=1;
	}
	inline Matrix operator *(const Matrix &o)const{
		Matrix re(0);
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				for(int k=0; k<2; k++){
					re.c[i][j]=(re.c[i][j]+c[i][k]*o.c[k][j]%Mod)%Mod;
				}
			}
		}
		return re;
	}
	inline Matrix qpow(int num){
		Matrix a=(*this), re(1);
		for(; num; num>>=1LL, a=a*a) if(num&1LL) re=re*a;
		return re;
	}
};

signed main(){
	freopen("poster.in", "r", stdin);
	freopen("poster.out", "w", stdout);
	T=rd();
	while(T--){
		n=rd()%Mod, m=rd()%(Mod-1);
		//printf("%lld %lld %lld\n", n, m, n*n);
		Matrix trs;
		trs.c[0][0]=frac((n*n%Mod-2*n%Mod+Mod)%Mod, n*n%Mod);
		trs.c[1][0]=frac(2, n*n%Mod);
		trs.c[1][1]=1;
		trs=trs.qpow(m);
		int Fm=(trs.c[0][0]+trs.c[1][0])%Mod;
		printf("%lld\n", (n-Fm*n%Mod+Mod)%Mod);
	}
	return 0;
}
