#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 
const int P = 998244353; 

i64 poww(i64 a, i64 b) {
	a %= P; i64 r = 1; 
	for (; b; b >>= 1, a = a * a % P) if (b & 1) r = r * a % P; 
	return r; 
}

int n, m; 
int a[15], ans; 
void dfs(int x) {
	if (x > m){
		for (int i = 1; i <= n; ++i) if (a[i] != i) ++ans; 
		return; 
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			swap(a[i], a[j]); 
			dfs(x + 1); 
			swap(a[i], a[j]); 
		}
}

int main(void) {
	freopen("poster.in", "r", stdin); 
	freopen("poster.out", "w", stdout); 
	
	/*
	for (n = 1; n <= 6; ++n, cout << "\n")
		for (m = 1; m <= 6; ++m) {
			ans = 0; 
			for (int i = 1; i <= n; ++i) a[i] = i; 
			dfs(1); 
			cout << 1ll * ans * poww(poww(n * n, m), P - 2) % P << " "; 
		}
	return 0; 
	*/
	
	int T; scanf("%d", &T); 
	while (T--) {
		ans = 0; 
		scanf("%d%d", &n, &m); 
		for (int i = 1; i <= n; ++i) a[i] = i; 
		dfs(1); 
		printf("%lld\n", 1ll * ans * poww(poww(n * n, m), P - 2) % P); 
	}
	return 0; 
}

/*
n=1 0  0    0      0       0         0
n=2 4  16   64     256     1024      4096
n=3 12 144  1404   12960   117612    1061424
n=4 24 576  10752  184320  3047424   49545216
n=5 40 1600 49000  1360000 36025000  931000000
n=6 60 3600 164160 6739200 262517760 9928396800
*/ 
