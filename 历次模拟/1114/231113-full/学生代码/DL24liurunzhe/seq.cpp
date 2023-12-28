# include <cstdio>
# include <vector>
# include <algorithm>

# define int long long

namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
		return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
	}
	template<class T> void gi(T& x){
		x=0; char c=gc();
		for(;c<'0'||c>'9';c=gc());
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0) pc('-'),x=-x; 
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;

constexpr int MAXN = 3e3 + 5;

int n, m;

int a[MAXN << 1];

int ll[MAXN << 1], rr[MAXN << 1];

std::vector<int> pos[MAXN << 1], vec[MAXN << 1];

int f[MAXN][MAXN], g[MAXN][MAXN], sum[MAXN][MAXN];

signed main() {
	
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	
	gi(n), gi(m);
	for (int i = 1; i <= n; ++i) gi(a[i]), pos[ a[i] ].push_back(i);
	for (int i = 1; i <= n; ++i) if (!pos[i].empty()) {
		ll[i] = pos[i][0], rr[i] = pos[i].back();
		vec[ rr[i] ].push_back(i);
	}
	for (int l = 1; l <= n; ++l) {
		for (int r = l; r <= n; ++r) {
			f[l][r] = f[l][r - 1];
			for (int k : vec[r]) 
				if (ll[k] >= l) f[l][r] = std::max(f[l][r], k);
			
			sum[l][r] = sum[l][r - 1] + f[l][r];
		}
	}
	for (int l = n; l >= 1; --l) {
		for (int r = l; r <= n; ++r)
			g[l][r] = g[l + 1][r] + sum[l][r];
	}
	for (int i = 1; i <= m; ++i) {
		int L, R;
		gi(L), gi(R); pi(g[L][R], '\n');
	}
	
	return 0;
}
