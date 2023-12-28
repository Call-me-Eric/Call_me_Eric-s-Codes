#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef __int128 lint;
typedef double dou;
typedef long double ld;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
template <typename _T> inline void read(_T &x){
	x=0; char c=getchar(); bool f=0;
	for(; c<'0'||c>'9'; c=getchar()) f|=(c=='-');
	for(; c>='0'&&c<='9'; c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
const int N=705, mod=998244353;
inline ll fpow(ll x, ll y){
	ll ret=1;
	while(y){
		if(y&1) ret=ret*x%mod;
		x=x*x%mod; y>>=1;
	}
	return ret;
}
int n, m;
namespace task2{
	int a[N][N], b[N];
	int c[N][N], d[N];
	inline void calc(){
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j) c[i][j]=a[i][j];
			d[i]=b[i];
		}
		int cur=1;
		for(int i=1; i<=n; ++i){
			int r=cur;
			for(int j=cur+1; j<=n; ++j){
				if(c[j][i]>c[r][i]) r=j;
			}
			if(c[r][i]==0) continue;
			for(int j=i; j<=n; ++j) swap(c[cur][j], c[r][j]);
			swap(d[cur], d[r]);
			ll inv=fpow(c[cur][i], mod-2);
			for(int j=cur+1; j<=n; ++j){
				d[j]=(d[j]-inv*c[j][i]%mod*d[cur]%mod+mod)%mod;
				for(int k=n; k>=i; --k) c[j][k]=(c[j][k]-inv*c[j][i]%mod*c[cur][k]%mod+mod)%mod;
			}
			++cur;
		}
		for(int i=cur; i<=n; ++i){
			if(d[i]) {
				printf("No\n"); return ;
			}
		}
		if(cur<=n) {
			printf("Many\n"); return ;
		}
		for(int i=n; i>=1; --i){
			d[i]=fpow(c[i][i], mod-2)*d[i]%mod;
			c[i][i]=1;
			for(int j=i-1; j>=1; --j) d[j]=(d[j]-(ll)c[j][i]*d[i]%mod+mod)%mod, c[j][i]=0;
		}
		for(int i=1; i<=n; ++i) printf("%d ", d[i]);
		putchar('\n');
	}
	void solve(){	
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j) read(a[i][j]); 
			read(b[i]);
		}	
		calc();
		while(m--){
			int z; read(z);
			for(int i=1; i<=n; ++i) read(a[z][i]);
			read(b[z]);
			calc();
		}
	}
}
namespace task1{
	struct node{
		int a[N]; 
		inline int operator [](int x){
			return a[x];
		}
		inline void rd(){
			for(int i=1; i<=n+1; ++i) read(a[i]);
		}
		inline bool emp(){
			for(int i=1; i<=n+1; ++i) if(a[i]) return false;
			return true;
		}
	}b[N];
	vector<node> vec[805];
	int tim[N];
	inline void ins(int p, int l, int r, int L, int R, node v){
		if(L<=l&&r<=R){
			vec[p].push_back(v);
			return ;
		}
		int mid=(l+r)>>1;
		if(L<=mid) ins(p<<1, l, mid, L, R, v);
		if(R>mid) ins(p<<1|1, mid+1, r, L, R, v);
	}
	node bs[10][N];
	int sz[10];
	int nosol[10];
	inline void calc(int d, int p, int l, int r){
		if(nosol[d-1]){
			if(l==r){
				printf("No\n");
				return ;
			}
			nosol[d]=1;
			int mid=(l+r)>>1;
			calc(d+1, p<<1, l, mid); calc(d+1, p<<1|1, mid+1, r);
			return ;
		}
		for(int i=1; i<=n; ++i){
			bs[d][i]=bs[d-1][i];
		}
		sz[d]=sz[d-1];
		for(auto t:vec[p]){
			bool suc=0;
			for(int i=1; i<=n; ++i) if(t[i]){
				if(bs[d][i].emp()){
					bs[d][i]=t;
					++sz[d];
					suc=1;
					break ;
				}
				ll inv=fpow(bs[d][i][i], mod-2)*t[i]%mod;
				for(int j=n+1; j>=i; --j){
					t.a[j]=(t.a[j]-inv*bs[d][i].a[j]%mod+mod)%mod;
				}
			}
			if(!suc&&t[n+1]){
				nosol[d]=1;
				break;
			}
		}
		if(l==r){
			if(nosol[d]){
				printf("NO\n");
				return ;
			}
			if(sz[d]<n){
				printf("Many\n");
				return ;
			}
			for(int i=n; i>=1; --i){
				bs[d][i].a[n+1]=fpow(bs[d][i][i], mod-2)*bs[d][i].a[n+1]%mod;
				for(int j=i-1; j>=1; --j){
					bs[d][j].a[n+1]=(bs[d][j].a[n+1]-(ll)bs[d][i].a[n+1]*bs[d][j].a[i]%mod+mod)%mod;
				}
			}
			for(int i=1; i<=n; ++i) printf("%d ", bs[d][i][n+1]);
			putchar('\n');
			return ;
		}
		int mid=(l+r)>>1;
		calc(d+1, p<<1, l, mid); calc(d+1, p<<1|1, mid+1, r);
	}
	void solve(){
		for(int i=1; i<=n; ++i){
			b[i].rd();
		}
		for(int i=1; i<=m; ++i){
			int z; read(z);
			ins(1, 0, m, tim[z], i-1, b[z]);
			tim[z]=i;
			b[z].rd();
		}
		for(int i=1; i<=n; ++i) ins(1, 0, m, tim[i], m, b[i]);
		calc(1, 1, 0, m);
	}
}
int main(){
	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);
	read(n); read(m);
	if(m<=100){
		task1::solve();
		return 0;
	}
	task2::solve();
	return 0;
}
