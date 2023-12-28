# include <cstdio>
# include <vector>

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

constexpr int MAXN = 1e6 + 5, MOD = 998244353;

int n;

int a[MAXN << 1], b[MAXN << 1];

int deg[MAXN << 1], mp[MAXN << 1];

int que[MAXN << 1], *hd = que, *tl = que;

std::vector<int> vec[MAXN << 1], pos[MAXN << 1];

bool mrk[MAXN << 1];

bool Get(int x, int val) { return b[x] == val; }

int fa[MAXN << 1];

int find(int x) {
	return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
	fa[find(x)] = find(y);
}

int fpow(int x, int k) {
	int res = 1;
	for (; k; k >>= 1) {
		if (k & 1) res = res * x % MOD;
		x = x * x % MOD;
	}
	return res;
}

signed main() {
	
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	
	gi(n);
	int tot = fpow(n, n);
	for (int i = 1; i <= n; ++i) {
		gi(a[i]);
		++deg[ a[i] ], vec[ a[i] ].emplace_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		gi(b[i]);
		++deg[ b[i] ], vec[ b[i] ].emplace_back(i);
	}
	int cnt = 1;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == b[i] && mp[ a[i] ]) return printf("%lld\n", tot), 0;
		if (a[i] == b[i]) mp[ a[i] ] = true, mrk[i] = true, cnt = cnt * n % MOD;
	}
	for (int i = 1; i <= n; ++i) 
		if (deg[i] < 2) *tl ++ = i;
	
	while (hd != tl) {
		int u = *hd ++;
		if (mp[u]) continue; mp[u] = true;
		if (deg[u] == 0) return printf("%lld\n", tot), 0;
		for (int k : vec[u]) if (!mrk[k]) {
			mrk[k] = true;
			if (a[k] == u) if (--deg[ b[k] ] == 1) *tl ++ = b[k];
			if (b[k] == u) if (--deg[ a[k] ] == 1) *tl ++ = a[k];
		}
	}
	std::vector<int> rem;
	for (int i = 1; i <= n; ++i) if (!mp[i]) {
		rem.push_back(i);
		for (int k : vec[i]) if (!mrk[k]) pos[i].push_back(k);
	}
	for (int i = 1; i <= 2 * n; ++i) fa[i] = i;
	for (int k : rem) {
		auto GetV = [=](int x, int y) {
			return a[x] == y ? b[x] : a[x];
		};
		auto Get = [=](int x, int y) {
			return pos[x][0] == y ? 0 : 1;
		};
		unite(k, GetV(pos[k][1], k) + Get(GetV(pos[k][1], k), pos[k][1]) * n);
		unite(k + n, GetV(pos[k][0], k) + Get(GetV(pos[k][0], k), pos[k][0]) * n);
	}
	for (int k : rem) if (find(k) == find(k + n)) return printf("%lld\n", tot), 0;
	
	int num = 0;
	for (int k : rem) num += fa[k] == k, num += fa[k + n] == k + n;
	printf("%lld\n", (tot - fpow(2, num >> 1) * cnt % MOD + MOD) % MOD);
	
	return 0;
}
