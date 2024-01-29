#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	int n, m;
	scanf("%d %d", &n, &m);
	auto G = vector<vector<int>>(n + 1);
	auto n0 = n;
	for (int _ = 0; _ < m; ++_) {
		int x, y;
		scanf("%d %d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}

	const auto eval = [&n, &m, &G] {
		auto id = map<pair<int, int>, int>();
		int nn = 0;
		for (int x = 1; x <= n; ++x) {
			for (int y : G[x]) {
				if (id.count({y, x})) id[make_pair(x, y)] = id[make_pair(y, x)];
				else id[make_pair(x, y)] = ++nn;
			}
		}

		auto E = set<pair<int, int>>();
		for (int x = 1; x <= n; ++x) {
			for (int y : G[x]) {
				for (int z : G[x]) {
					if (y == z) continue;
					E.insert({id[make_pair(x, y)], id[make_pair(x, z)]});
				}
			}
		}

		G.clear();
		G.resize(m + 1);
		for (const auto& e : E) {
			int x, y;
			tie(x, y) = e;
			G[x].push_back(y);
		}
		n = m;
		m = E.size() / 2;
	};

	for (int i = 1; i <= n; ++i) {
		if (G[i].size() >= 4) goto QE;
	}

	eval();
	for (int i = 1; i <= n; ++i) {
		if (G[i].size() >= 3) goto QE;
	}
{
	static struct _dfsA {
		_dfsA(int n, int m, decltype(G)* g): c(n + 1), G(g), n(n), m(m) {}
		void operator()(int x, int v) {
			if (c[x]) return;
			c[x] = v;
//			fprintf(stderr, "+%d\n", x);
			for (int y : (*G)[x]) {
				(*this)(y, v);
			}
		}
		vector<int> c;
		vector<vector<int>> *G;
		int n, m;
	} dfsA(n, m, &G);

//	fprintf(stderr, "+%d %d\n", n, m);
	int k = 0;
	for (int i = 1; i <= n; ++i) {
		if (!dfsA.c[i]) dfsA(i, ++k);
	}

	vector<int> N(k + 1), M(k + 1);

	for (int i = 1; i <= n; ++i) {
		N[dfsA.c[i]] += 1;
		M[dfsA.c[i]] += G[i].size();
	}

	for_each(M.begin() + 1, M.end(), [](auto &x) {
		x /= 2;
	});

	int rtc = 0;
	for (int i = 1; i <= k; ++i) {
		if (M[i] > N[i]) goto QE;
		if (N[i] == M[i]) rtc += N[i];
	}

	struct Accr {
		int64_t sum;
		Accr() : sum(0) {}
		void operator()(int x) {
			sum += x * (x + 1LL) / 2;
		}
	};

	if (rtc) printf("1 %d\n", rtc);
	else printf("0 %lld", for_each(N.begin() + 1, N.end(), Accr()).sum + n0);
}
	return 0;

QE:	puts("-1");
	return 0;
}
