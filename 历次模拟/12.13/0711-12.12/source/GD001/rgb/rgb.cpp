#include <bits/stdc++.h>
using namespace std;

int r, g, b, m, n;
bool s[15];
vector<tuple<int, int, int>> E;
int S[15];

void init(int n) {
	for (int i = 1; i <= n; ++i) {
		S[i] = i;
	}
}

int getf(int x) {
	return S[x] == x ? x : (S[x] = getf(S[x]));
}

void merge(int x, int y) {
	int a = getf(x);
	int b = getf(y);
	if (a != b) {
		S[a] = b;
		S[x] = b;
	}
}

void check() {
	int cc[4] = {0, 0, 0, 0};
	init(n);
	for (int i = 0; i < m; ++i) {
		if (!s[i]) continue;
		int c = get<2>(E[i]);
		cc[c] += 1;
		int x = get<0>(E[i]);
		int y = get<1>(E[i]);
		merge(x, y);
	}

	if (cc[1] != r || cc[2] != g || cc[3] != b) return;
	for (int i = 2; i <= n; ++i) {
		if (getf(i) != getf(1)) {
			return;
		}
	}

	puts("YES");
	for (int i = 0; i < m; ++i) {
		printf("%c", "01"[s[i]]);
	}
	puts("");
	exit(0);
}

void dfs(int x) {
	if (x == m) return check();

	s[x] = false;
	dfs(x + 1);
	s[x] = true;
	dfs(x + 1);
}

int main() {
	freopen("rgb.in", "r", stdin);
	freopen("rgb.out", "w", stdout);
	scanf("%d %d %d %d", &r, &g, &b, &m);
	n = r + g + b + 1;
	if (m > 20) goto BE;
	for (int i = 0; i < m; ++i) {
		int x, y;
		char c[5];
		scanf("%d %d %s", &x, &y, c);
		int ic = (c[0] == 'r' ? 1 : (c[0] == 'g' ? 2 : 3));
		E.emplace_back(x, y, ic);
	}

	dfs(0);
BE:	puts("NO");
	return 0;
}

