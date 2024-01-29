#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	int n, k;
	cin >> n >> k;
	vector<int> pr;
	{
		int x = n;
		for (int i = 2; i * i <= x; i++) {
			if (x % i == 0) {
				pr.push_back(i);
				while (x % i == 0) {
					x /= i;
				}
			}
		}
		if (x > 1) {
			pr.push_back(x);
		}
	}
	vector<bool> dp(n + 1);
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int p : pr) {
			if (i >= p && dp[i - p]) {
				dp[i] = 1;
				break;
			}
		}
	}
	auto construct = [&](int k) {
		string res(n, '0');
		if (__gcd(n, k) > 1) {
			for (int p : pr) {
				if (k % p == 0) {
					for (int i = 0; i < k / p; i++) {
						for (int j = i; j < n; j += n / p) {
							res[j] = '1';
						}
					}
					break;
				}
			}
		} else {
			assert(2 * k < n && pr.size() > 1);
			int p = pr[0], q = pr[1];
			if (k < (p - 1) * (q - 1)) {
				// if ab < n, we can construct a + b from a and b
				vector<bool> done(k + 1);
				vector<int> from(k + 1, -1);
				for (int i = 0; i <= k; i++) {
					if (__gcd(n, i) > 1) {
						done[i] = 1;
					} else {
						for (int p : pr) {
							if (i >= p && done[i - p] && 1LL * (i - p) * p < n) {
								done[i] = 1;
								from[i] = p;
								break;
							}
						}
					}
				}
				assert(done[k]);
				auto rec = [&](auto self, int k) -> void {
					if (__gcd(n, k) > 1) {
						for (int p : pr) {
							if (k % p == 0) {
								for (int i = 0; i < k / p; i++) {
									for (int j = i; j < n; j += n / p) {
										res[j] = '1';
									}
								}
								break;
							}
						}
					} else {
						int p = from[k];
						self(self, k - p);
						for (int i = 0; i < n / p; i++) {
							bool good = 1;
							for (int j = i; j < n; j += n / p) {
								good &= res[j] == '0';
							}
							if (good) {
								for (int j = i; j < n; j += n / p) {
									res[j] = '1';
								}
								break;
							}
						}
					}
				};
				rec(rec, k);
			} else {
				// write k = ap + bq (0 <= b < p)
				int a, b;
				for (b = 0; ; b++) {
					if ((k - b * q) % p == 0) {
						a = (k - b * q) / p;
						break;
					}
				}
				// take the set of pq-th roots of unity, and from those select b rotations of the q-th roots
				for (int i = 0; i < b; i++) {
					for (int j = i; j < p * q; j += p) {
						res[n / (p * q) * j] = '1';
					}
				}
				// choose disjoint collections of p balanced roots which do not intersect
				for (int i = 0; i < n / p && a; i++) {
					bool good = 1;
					for (int j = i; j < n; j += n / p) {
						good &= res[j] == '0';
					}
					if (good) {
						for (int j = i; j < n; j += n / p) {
							res[j] = '1';
						}
						a--;
					}
				}
			}
		}
		assert(count(res.begin(), res.end(), '1') == k);
		return res;
	};
	for (int ans = k; ans >= 0; ans--) {
		if (dp[ans] && dp[n - ans]) {
			if (ans > n - ans) {
				auto str = construct(n - ans);
				for (char &c : str) {
					c = c == '0' ? '1' : '0';
				}
				cout << str << "\n";
			} else {
				cout << construct(ans) << "\n";
			}
			break;
		}
	}
	return 0;
}