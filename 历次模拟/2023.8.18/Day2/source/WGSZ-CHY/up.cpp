#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-5;
const int N = 1e6 + 5;
const int M = 20;
const int V = 1e7;
const int mod = 998244353;
const int bse = 998244353;
const int inf = 1e18;
const double pi = acos(-1);
int n, m;
struct node {
	int a, b;
} p[N];
signed main() {
	freopen("up.in", "r", stdin);
	freopen("up.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) p[i] = {read(), read()};
	while(m--) {
		int a, b;
		a = read(), b = read();
		int ans = 0;
		for(int i = 1; i <= n; i++)
			if(a > p[i].a || b > p[i].b) continue;
			else {
				int A = p[i].a, B = p[i].b;
				while(A >= a && B >= b) {
					if(A == a && (B - b) % A == 0 || (B == b && (A - a) % B == 0)) {
						ans++;
						break;
					}
					if(A > B) A %= B;
					else B %= A;
				}
			}
		printf("%lld\n", ans);
	}
	return 0;
}


