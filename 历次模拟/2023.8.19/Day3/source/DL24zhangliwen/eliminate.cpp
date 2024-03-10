#include <bits/stdc++.h>
using namespace std; 

inline int read(void) {
	int x = 0, c = getchar(), f = 1; 
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); 
	return x * f; 
}

int n, m, c[1000005]; 
struct Node {
	int v, p; 
	bool operator< (const Node &a) const { return v < a.v; }
} a[2000005]; 
int res, buc[1000005]; 
inline void add(int x, int k) {
	if (k == 1) {
		if (buc[x] == 0) ++res; 
		++buc[x]; 
	} else {
		if (buc[x] == 1) --res; 
		--buc[x]; 
	}
}

int main(void) {
	freopen("eliminate.in", "r", stdin); 
	freopen("eliminate.out", "w", stdout); 
	
	n = read(); 
	for (int i = 1; i <= n; ++i) {
		c[i] = read(); 
		for (int j = 0; j < c[i]; ++j) a[++m].v = read(), a[m].p = i; 
	}
	sort(a + 1, a + m + 1); 
	
	int ans = 2e9 + 5; 
	for (int L = 1, R = 0; L <= m; ) {
		while (R < m && res < n) { ++R; add(a[R].p, 1); }
		if (res == n) ans = min(ans, a[R].v - a[L].v); 
		add(a[L].p, -1); ++L; 
	}
	
	return !printf("%d\n", ans); 
}
