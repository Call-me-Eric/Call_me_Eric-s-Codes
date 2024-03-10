// 5 Î¬Æ«Ðò¡£/qd
// How bitset? /kk

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

const int N = 5e4;

int n;
struct node { int _m[0]; int a, b, c, d, e; } a[N + 5];
int w[N + 5], f[N + 5];

// ensure x < y
bool check(int x, int y) {
	for(int i = 0; i < 5; i++) {
		if(a[x]._m[i] > a[y]._m[i]) return false;
	}
	return true;
}

int main() {
	freopen("frog.in", "r", stdin), freopen("frog.out", "w", stdout);

	n = rd();
	for(int i = 1; i <= n; i++) {
		a[i] = {rd(), rd(), rd(), rd(), rd()}, w[i] = rd();
	}
	int lim = 1e8 / n;
	for(int i = 1; i <= n; i++) {
		for(int j = std::max(0, i - lim); j < i; j++) {
			if(check(j, i)) f[i] = std::max(f[i], f[j] + w[i]);
		}
	}
	for(int i = 1; i <= n; i++) {
		printf("%d\n", f[i]);
	}
	return 0;
}

