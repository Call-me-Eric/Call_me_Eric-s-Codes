#include <bits/stdc++.h>
using namespace std; 
typedef long long i64;

int n, q; 
i64 a[50005], b[50005], c, d; 

bool work(i64 x, i64 y) {
	if (x == c && y == d) return 1; 
	if (x < c || y < d) return 0; 
	if (x > y) {
		i64 bx = x; x %= y; 
		if (x < c) x += (c - x + y - 1) / y * y; 
		if (x == bx) return 0; 
		return work(x, y); 
	}
	i64 by = y; y %= x; 
	if (y < d) y += (d - y + x - 1) / x * x; 
	if (y == by) return 0; 
	return work(x, y); 
}

int main(void) {
	freopen("up.in", "r", stdin); 
	freopen("up.out", "w", stdout); 
	scanf("%d%d", &n, &q); 
	for (int i = 1; i <= n; ++i) scanf("%lld%lld", a + i, b + i); 
	while (q--) {
		int ans = 0; scanf("%lld%lld", &c, &d); 
		for (int i = 1; i <= n; ++i) 
			if (c <= a[i] && d <= b[i] && work(a[i], b[i])) ++ans; 
		printf("%d\n", ans); 
	}
	return 0; 
} 
