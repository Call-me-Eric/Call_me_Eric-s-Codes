#include <bits/stdc++.h>
using namespace std;
namespace QYB {
	int main() {
		freopen("ur.in", "r", stdin);
		freopen("ur.out", "w", stdout);
		int n, k, t; scanf("%d%d", &n, &k); t = n;
		for (int i = 2; i <= n; i++) {
			if (n % i == 0 && k / i * i > k / t * t) t = i;
		} for (int i = 1; i <= n; i++) {
			printf("%d", (i - 1) % (n / t) < k / t);
		} return !printf("\n");
	}
} int main() {
	return QYB::main();
}
