#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[101], b[101];
int ans;

void dfs(int k) {
	int mk = 0;
	for (int i = 1; i <= n; ++i) {
		mk += abs(a[i] - b[i]);
	}

	if (mk > k) return;
	if (k == 0) {
		ans += 1;
		return;
	}

	for (int i = 1; i <= n + 1; ++i) {
		bool mk = i == n + 1;
		if (mk) n = i;
		for (int d : {-1, 1}) {
			a[i] += d;
			if ((i == 1 || a[i] <= a[i - 1]) && a[i] >= a[i + 1]) dfs(k - 1);
			a[i] -= d;
		}
		if (mk) n = i - 1;
	}
}

int main() {
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) scanf("%d", b + i);

	int _, v;
	scanf("%d %d", &_, &v);
	dfs(v);
	printf("%d\n", ans);
	return 0;
}

