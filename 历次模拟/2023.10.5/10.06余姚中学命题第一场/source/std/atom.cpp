#include <bits/stdc++.h>
using namespace std;
int n, m, p[2005], c, d[6];
void write(int x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int main() {
	freopen ("atom.in", "r", stdin);
	freopen ("atom.out", "w", stdout);
	cin >> n, m = n >> 1;
	write(m * (n - m)), putchar('\n');
	for (int i=m+1; i<=n; i++) p[i] = n;
	for (int i=1; i<=m; i++)
		for (int j=m+1; j<=n; j++) {
			c = 0;
			if (p[i] < i - 1) {
				if (p[i]) d[++c] = p[i];
				d[++c] = i - ++ p[i];
			} else if (i > 1)
				d[++c] = i - 1;
			d[++c] = j - i;
			if (p[j] > j)
				d[++c] = p[j] -- - j;
			write(c);
			for (int i=1; i<=c; i++) putchar(' '), write(d[i]);
			putchar('\n');
		}
}
