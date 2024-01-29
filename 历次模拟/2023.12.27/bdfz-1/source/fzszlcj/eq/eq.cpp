#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using vi = vector<int>;
using pii = pair<int, int>;
#define pb emplace_back
#define sz(a) int(a.size())

const int N = 700, P = 998244353;

int qpow(int a, int b = P - 2)
{
	int t = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) {
		if (b & 1) {
			t = 1ll * t * a % P;
		}
	}
	return t;
}

int n, q, id, lst[N * 2 + 5], nw[N * 2 + 5];
vi b[N * 2 + 5];

#define mid ((L + R) >> 1)
#define Ls rt << 1, L, mid
#define Rs rt << 1 | 1, mid + 1, R

vi tr[N * 4 + 5];

void ins(int l, int r, int v, int rt = 1, int L = 0, int R = q)
{
	if (l <= L && R <= r) {
		tr[rt].pb(v);
		return ;
	}
	if (l <= mid) {
		ins(l, r, v, Ls);
	}
	if (r > mid) {
		ins(l, r, v, Rs);
	}
}


struct info {
	vector<vi> vec;
	vi xa, xb;
} fk[15];


void sol(int d = 1, int rt = 1, int L = 0, int R = q)
{
	fk[d] = fk[d - 1];
	for (auto i : tr[rt]) {
		fk[d].vec.pb(b[i]);
		for (int j = 0; j < n; ++j) {
			if (fk[d].vec.back()[j] && ~fk[d].xb[j]) {
				int mul = 1ll * fk[d].vec.back()[j] * qpow(fk[d].vec[fk[d].xb[j]][j]) % P;
				for (int z = 0; z <= n; ++z) {
					fk[d].vec.back()[z] = (fk[d].vec.back()[z] - 1ll * mul * fk[d].vec[fk[d].xb[j]][z]) % P;
				}
			}
		}
		int p = -1;
		for (auto j : fk[d].xa) {
			if (fk[d].vec.back()[j]) {
				p = j;
				break;
			}
		}
		if (~p) {
			int inv = qpow(fk[d].vec.back()[p]);
			for (int j = 0; j < sz(fk[d].vec) - 1; ++j) {
				if (fk[d].vec[j][p]) {
					int mul = 1ll * fk[d].vec[j][p] * inv % P;
					for (int z = 0; z <= n; ++z) {
						fk[d].vec[j][z] = (fk[d].vec[j][z] - 1ll * mul * fk[d].vec.back()[z]) % P;
					}
				}
			}
		}
		if (~p) {
			fk[d].xb[p] = sz(fk[d].vec) - 1;
			fk[d].xa.erase(find(fk[d].xa.begin(), fk[d].xa.end(), p));
		}
	}
	if (L == R) {
		if (sz(fk[d].xa)) {
			for (auto i : fk[d].vec) {
				bool flag = 0;
				for (int j = 0; j < n; ++j)  {
					if (i[j]) {
						flag = true;
						break;
					}
				}
				if (!flag && i[n]) {
					cout << "No\n";
					return ;
				}
			}
			cout << "Many\n";
		}else {
			for (int i = 0; i < n; ++i) {
				cout << (1ll * qpow(fk[d].vec[fk[d].xb[i]][i]) * fk[d].vec[fk[d].xb[i]].back() % P + P) % P << ' ';
			}
			cout << '\n';
		}
	}else {
		sol(d + 1, Ls);
		sol(d + 1, Rs);
	}
}


#undef mid
#undef Ls
#undef Rs

signed main()
{
	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		b[i].resize(n + 1);
		for (auto &j : b[i]) {
			cin >> j;
		}
		lst[i] = 0;
		nw[i] = i;
	}
	for (int i = 1; i <= q; ++i) {
		int z;
		cin >> z;
		ins(lst[z], i - 1, nw[z]);
		lst[z] = i;
		nw[z] = i + n;
		
		b[i + n].resize(n + 1);
		for (auto &j : b[i + n]) {
			cin >> j;	
		}
	}
	for (int i = 1; i <= n; ++i) {
		ins(lst[i], q, nw[i]);
	}
	for (int i = 0; i < n; ++i) {
		fk[0].xa.pb(i);
	}
	fk[0].xb.resize(n, -1);
	sol();
	return 0;
}

