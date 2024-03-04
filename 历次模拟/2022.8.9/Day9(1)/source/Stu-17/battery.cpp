#include <iostream>
#include <cstdio>

using namespace std;

int n, m;
char s[55][55];

void solve(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", s[i] + 1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (s[i][j] == '|' || s[i][j] == '-')
			{
				puts("IMPOSSIBLE");
				return;
			}
	puts("POSSIBLE");
	for (int i = 1; i <= n; ++i)
		printf("%s\n", s[i] + 1);
}

int main(void)
{
	freopen("battery.in", "r", stdin);
	freopen("battery.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
