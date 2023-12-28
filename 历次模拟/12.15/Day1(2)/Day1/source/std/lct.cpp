#include<bits/stdc++.h>
#define FT first
#define SC second
#define PB push_back
#define MP make_pair
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define PER(i, r, l) for(int i = (r); i >= (l); i--)
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define ROF(i, n) for(int i = (n) - 1; i >= 0; i--)
#define VEP(i, x) for(int i = 0; i < x.size(); i++)
#define DFOR(i, x) for(int i = hd[x]; i; i = e[i].nxt)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()
#define mid (l + r >> 1)

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const int inf = 0x7fffffff;
const int MOD = 1000000007;

template <typename tn>
inline tn read(){
	char ch; tn f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	tn x = ch - '0';
	while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
	return x * f;
}
template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }

const int N = 200000 + 5, M = N * 60;
struct Edge{ int nxt, to; } e[N * 2];
int s[M], lc[M], rc[M], hd[N], root[N], tail = 0, tot;

void add(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
void modify(int &x, int y, int l, int r, int v){
	s[x = ++tot] = s[y] + 1;
	if (l == r) { s[x] = s[y] + 1; return; }
	if (v <= mid) modify(lc[x], lc[y], l, mid, v), rc[x] = rc[y];
	else modify(rc[x], rc[y], mid + 1, r, v), lc[x] = lc[y];
}
int query(int x, int l, int r, int p, int q){
	if (l > q || r < p) return 0;
	if (l >= p && r <= q) return s[x];
	return query(lc[x], l, mid, p, q) + query(rc[x], mid + 1, r, p, q);
}
int main(){
	freopen("lct.in", "r", stdin);
	freopen("lct.out", "w", stdout);
	int n = rint, m = rint;
	MEM(hd, 0);
	REP(i, 1, n - 1){
		int x = rint, y = rint;
		add(x, y), add(y, x);
	}
	s[tot = root[0] = 0] = lc[0] = rc[0] = 0;
	REP(i, 1, n){
		root[i] = root[i - 1];
		DFOR(j, i) modify(root[i], root[i], 1, n, e[j].to);
	}
	REP(i, 1, m){
		int l = rint, r = rint;
		printf("%d\n", r - l + 1 - (query(root[r], 1, n, l, r) - query(root[l - 1], 1, n, l, r)) / 2);
	}
}
