#include <bits/stdc++.h>
using namespace std;

constexpr int S(int x) {
	return x + 2;
}

namespace Main {
	const int N = 50000;
	const long long MOD = 4294967296;
	
	class node {
	public:
		int l, r;
		mutable char v;
		node(int _l = 0, int _r = 0, char _v = 'a') : l(_l), r(_r), v(_v) {}
		friend bool operator<(node a, node b) {
			return a.l < b.l;
		}
	};
	
	set<node> s;
	
	set<node>::iterator assign(int l, int r) {
		auto it2 = --s.upper_bound(node(r));
		if (it2->r == r) {
			it2++;
		} else {
			node tmp = *it2;
			s.erase(it2);
			it2 = s.insert(node(r + 1, tmp.r, tmp.v)).first;
		}
		auto it1 = --s.upper_bound(node(l));
		if (it1->l != l) {
			node tmp = *it1;
			s.erase(it1);
			it1 = ++s.insert(node(tmp.l, l - 1, tmp.v)).first;
		}
		s.erase(it1, it2);
		return s.insert(node(l, r)).first;
	}
	
	void modify(int l, int r, char v) {
		auto it = assign(l, r);
		it->v = v;
	}
	
	long long query(int l, int r) {
		long long P = 0, Q = 0, R = 0, S = 0, T = 0;
		auto it = --s.upper_bound(node(l)), it2 = --s.upper_bound(node(r));
		if (it->v == '(') {
			P += it->r - l + 1;
		}
		it++;
		for (; it != it2; ++it) {
			int len = it->r - it->l + 1;
			if (it->v == '(') {
				P = (P + len) % MOD;
			} else if (it->v == '0') {
				(Q += P * len) %= MOD;
				(S += R * len) %= MOD;
			} else if (it->v == 'w') {
				(R += Q * len) %= MOD;
			} else if (it->v == ')') {
				(T += S * len) %= MOD;
			}
		}
		if (it->v == ')') {
			(T += S * (r - it->l + 1)) %= MOD;
		}
		return T;
	}
	
	int n, m;
	
	void naive() {
		char a[S(N)];
		char ch, op;
		int x, y;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
		}
		for (int i = 1; i <= m; ++i) {
			cin >> op >> x;
			if (op == 'C') {
				cin >> y;
				long long p = 0, q = 0, r = 0, s = 0, t = 0;
				for (int j = x; j <= y; ++j) {
					if (a[j] == '(') {
						p = (p + 1) % MOD;
					} else if (a[j] == '0') {
						(q += p) %= MOD;
						(s += r) %= MOD;
					} else if (a[j] == 'w') {
						(r += q) %= MOD;
					} else if (a[j] == ')') {
						(t += s) %= MOD;
					}
				}
				cout << t << '\n';
			} else if (op == 'B') {
				cin >> y >> ch;
				for (int j = x; j <= y; ++j) {
					a[j] = ch;
				}
			} else if (op == 'A') {
				cin >> a[x];
			}
		}
	}
	
	void odt() {
		char ch, op;
		int x, y;
		for (int i = 1; i <= n; ++i) {
			cin >> ch;
			s.insert(s.end(), node(i, i, ch));
		}
		for (int i = 1; i <= m; ++i) {
			cin >> op >> x;
			if (op == 'C') {
				cin >> y;
				cout << query(x, y) << endl;
			} else if (op == 'A') {
				cin >> ch;
				modify(x, x, ch);
			} else if (op == 'B') {
				cin >> y >> ch;
				modify(x, y, ch);
			}
		}
	}
	
	void main() {
		freopen("0w0.in", "r", stdin);
		freopen("0w0.out", "w", stdout);
		cin >> n >> m;
		if (n <= 1000 && m <= 1000) {
			naive();
		} else {
			odt();
		}
	}
}

int main() {
	Main::main();
	return 0;
}
