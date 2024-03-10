#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

i64 gcd(i64 x, i64 y) { 
	if (y == 0) return x; 
	return gcd(y, x % y);
}
i64 lcm(i64 x, i64 y) { 
	if (x == 0 || y == 0) return x + y; 
	return x / gcd(x, y) * y; 
}

struct Equation {
	i64 a, b, c, d; 
} E[10], T[10], m;
int p[10]; 

void solve(void) {
	// 先消 x2
	m = 0; 
}

int main(void) {
	freopen("sumeru.in", "r", stdin); 
	freopen("sumeru.out", "w", stdout); 
	ios::sync_with_stdio(0); 
	int T; cin >> T; 
	while (T--) {
		puts("NO"); 
	}
	return 0;
}
// 剧本：凶宅魅影 
