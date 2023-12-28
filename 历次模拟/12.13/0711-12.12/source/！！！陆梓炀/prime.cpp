#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll long long
	#define bl bool
	ll my_pow(ll a,ll b,ll mod){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res=(res*a)%mod;
			a=(a*a)%mod;
			b>>=1;
		}
		return res;
	}
	ll qpow(ll a,ll b){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res*=a;
			a*=a;
			b>>=1;
		}
		return res;
	}
	#define db double
	#define pf printf
	#define pc putchar
	#define fr(i,x,y) for(register ll i=(x);i<=(y);i++)
	#define pfr(i,x,y) for(register ll i=(x);i>=(y);i--)
	#define go(u) for(ll i=head[u];i;i=e[i].nxt)
	#define enter pc('\n')
	#define space pc(' ')
	#define fir first
	#define sec second
	#define MP make_pair
	#define il inline
	#define inf 8e18
	#define random(x) rand()*rand()%(x)
	#define inv(a,mod) my_pow((a),(mod-2),(mod))
	il ll read(){
		ll sum=0,f=1;
		char ch=0;
		while(!isdigit(ch)){
			if(ch=='-') f=-1;
			ch=getchar();
		}
		while(isdigit(ch)){
			sum=sum*10+(ch^48);
			ch=getchar();
		}
		return sum*f;
	}
	il void write(ll x){
		if(x<0){
			x=-x;
			pc('-');
		}
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
	il void writeln(ll x){
		write(x);
		enter;
	}
	il void writesp(ll x){
		write(x);
		space;
	}
}
using namespace my_std;
#define mod 998244353
ll t;
char L[100010],R[100010];
il void inc(ll &x,ll y){
	((x+=y)>=mod)?(x-=mod):0;
}
struct node1{//have 1
	ll f[100010][2][2][2][2],g[100010][2];
	il ll solve(char *S,ll n){
		fr(i,0,n) fr(j,0,1) fr(k,0,1) fr(l,0,1) fr(m,0,1) f[i][j][k][l][m]=0;
		fr(i,0,n) fr(j,0,1) g[i][j]=0;
		f[0][1][0][0][0]=1;
		fr(i,1,n){
			fr(j,0,1){
				fr(k,0,1){
					fr(l,0,1){
						fr(m,0,1){
							ll val=f[i-1][j][k][l][m];
							if(!val) continue;
							if((!j||S[i]>='0')&&(!l||!m)){//0
								if(j&&S[i]>'0') inc(f[i][0][k][l][m+l],val);
								else inc(f[i][j][k][l][m+l],val);
							}
							if((!j||S[i]>='8')&&!k){//8
								if(j&&S[i]>'8') inc(f[i][0][1][l][m],val);
								else inc(f[i][j][1][l][m],val);
							}
							if((!j||S[i]>='9')&&!k&&!l){//9
								if(j&&S[i]>'9') inc(f[i][0][k][1][m],val);
								else inc(f[i][j][k][1][m],val);
							}
							if(!j||S[i]>='1'){//1
								if(j&&S[i]>'1') inc(g[i][0],val);
								else inc(g[i][j],val);
							}
						}
					}
				}
			}
			fr(j,0,1){
				ll val=g[i-1][j];
				if(!val) continue;
				if(!j||S[i]>='0'){//0
					if(j&&S[i]>'0') inc(g[i][0],val);
					else inc(g[i][j],val);
				}
				if(!j||S[i]>='4'){//4
					if(j&&S[i]>'4') inc(g[i][0],val);
					else inc(g[i][j],val);
				}
				if(!j||S[i]>='6'){//6
					if(j&&S[i]>'6') inc(g[i][0],val);
					else inc(g[i][j],val);
				}
				if(!j||S[i]>='8'){//8
					if(j&&S[i]>'8') inc(g[i][0],val);
					else inc(g[i][j],val);
				}
			}
		}
		return (g[n][0]+g[n][1])%mod;
	}
}T1;
struct node2{//no 1 no 49
	ll f[100010][2][2][2];
	il ll solve(char *S,ll n){
		fr(i,0,n) fr(j,0,1) fr(k,0,1) fr(l,0,1) f[i][j][k][l]=0;
		f[0][1][0][0]=1;
		fr(i,1,n){
			fr(j,0,1){
				fr(k,0,1){
					fr(l,0,1){
						ll val=f[i-1][j][k][l];
						if(!val) continue;
						if(!j||S[i]>='0'){//0
							if(j&&S[i]>'0') inc(f[i][0][k][l],val);
							else inc(f[i][j][k][l],val);
						}
						if(!j||S[i]>='4'){//4
							if(j&&S[i]>'4') inc(f[i][0][1][l],val);
							else inc(f[i][j][1][l],val);
						}
						if(!j||S[i]>='6'){//6
							if(j&&S[i]>'6') inc(f[i][0][k][l],val);
							else inc(f[i][j][k][l],val);
						}
						if(!j||S[i]>='8'){//8
							if(j&&S[i]>'8') inc(f[i][0][k][1],val);
							else inc(f[i][j][k][1],val);
						}
						if((!j||S[i]>='9')&&!k&&!l){//9
							if(j&&S[i]>'9') inc(f[i][0][k][l],val);
							else inc(f[i][j][k][l],val);
						}
					}
				}
			}
		}
		ll ans=0;
		fr(j,0,1) fr(k,0,1) fr(l,0,1) inc(ans,f[n][j][k][l]); 
		return ans;
	}
}T2;
struct node3{//no 1 have 49
	ll f[100010][2],g[100010][2],h[100010][2][2][6],F[100010][2],G[100010][2][3],H[100010][2],M[100010][2];
	ll solve(char *S,ll n){
		fr(i,0,n) fr(j,0,1) f[i][j]=g[i][j]=F[i][j]=H[i][j]=M[i][j]=0;
		fr(i,0,n) fr(j,0,1) fr(k,0,1) fr(l,1,5) h[i][j][k][l]=0;
		fr(i,0,n) fr(j,0,1) fr(k,0,2) G[i][j][k]=0;
		f[0][1]=1;
		fr(i,1,n){
			fr(j,0,1){
				ll val=f[i-1][j];
				if(!val) continue;
				if(!j||S[i]>='0'){//0
					if(j&&S[i]>'0') inc(f[i][0],val);
					else inc(f[i][j],val);
				}
				if(!j||S[i]>='4'){//4
					if(j&&S[i]>'4') inc(F[i][0],val);
					else inc(F[i][j],val);
				}
				if(!j||S[i]>='6'){//6
					if(j&&S[i]>'6') inc(h[i][0][0][1],val);
					else inc(h[i][j][0][1],val);
				}
				if(!j||S[i]>='9'){//9
					if(j&&S[i]>'9') inc(g[i][0],val);
					else inc(g[i][j],val);
				}
			}
			fr(j,0,1){
				ll val=g[i-1][j];
				if(!val) continue;
				if(!j||S[i]>='4'){//4
					if(j&&S[i]>'4') inc(G[i][0][0],val);
					else inc(G[i][j][0],val);
				}
			}
			fr(j,0,1){
				fr(k,0,1){
					fr(l,1,5){
						ll val=h[i-1][j][k][l];
						if(!val) continue;
						if((!j||S[i]>='0')&&l<5){//0
							if(j&&S[i]>'0') inc(h[i][0][1][l+1],val);
							else inc(h[i][j][1][l+1],val);
						}
						if(!j||S[i]>='4'){//4
							if(j&&S[i]>'4') inc(H[i][0],val);
							else inc(H[i][j],val);
						}
						if((!j||S[i]>='6')&&!k&&l<3){//6
							if(j&&S[i]>'6') inc(h[i][0][k][l+1],val);
							else inc(h[i][j][k][l+1],val);
						}
					}
				}
			}
			fr(j,0,1){
				ll val=F[i-1][j];
				if(!val) continue;
				if(!j||S[i]>='6'){//6
					if(j&&S[i]>'6') inc(F[i][0],val);
					else inc(F[i][j],val);
				}
				if(!j||S[i]>='9'){//9
					if(j&&S[i]>'9') inc(M[i][0],val);
					else inc(M[i][j],val);
				}
			}
			fr(j,0,1){
				fr(k,0,2){
					ll val=G[i-1][j][k];
					if(!val) continue;
					if((!j||S[i]>='6')&&k<2){//6
						if(j&&S[i]>'6') inc(G[i][0][k+1],val);
						else inc(G[i][j][k+1],val);
					}
					if(!j||S[i]>='9'){//9
						if(j&&S[i]>'9') inc(M[i][0],val);
						else inc(M[i][j],val);
					}
				}
			}
			fr(j,0,1){
				ll val=H[i-1][j];
				if(!val) continue;
				if(!j||S[i]>='9'){//9
					if(j&&S[i]>'9') inc(M[i][0],val);
					else inc(M[i][j],val);
				}
			}
			fr(j,0,1){
				ll val=M[i-1][j];
				if(!val) continue;
				if(!j||S[i]>='0'){//0
					if(j&&S[i]>'0') inc(M[i][0],val);
					else inc(M[i][j],val);
				}
				if(!j||S[i]>='4'){//4
					if(j&&S[i]>'4') inc(M[i][0],val);
					else inc(M[i][j],val);
				}
				if(!j||S[i]>='6'){//6
					if(j&&S[i]>'6') inc(M[i][0],val);
					else inc(M[i][j],val);
				}
				if(!j||S[i]>='8'){//8
					if(j&&S[i]>'8') inc(M[i][0],val);
					else inc(M[i][j],val);
				}
			}
		}
		return (M[n][0]+M[n][1])%mod;
	}
}T3;
il ll solve(char *S,ll n){
	return (T1.solve(S,n)+T2.solve(S,n)+T3.solve(S,n))%mod;
}
int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	t=read();
	while(t--){
		scanf("%s",L+1);
		scanf("%s",R+1);
		ll lenl=strlen(L+1),lenr=strlen(R+1);
		pfr(i,lenl,1){
			if(L[i]>='1'){
				L[i]--;
				break;
			}
			L[i]='9';
		}
		writeln((solve(R,lenr)-solve(L,lenl)+mod)%mod);
	}
}
/*
2
1 4242
123456789 1000000000000000000

2,3,5,7
89!!!
11,19,41,61,881,991,9001
409,449,499,(6469),6949,9049,9649,9949,60649,666649,(946669),60000049,66000049,66600049
*/
