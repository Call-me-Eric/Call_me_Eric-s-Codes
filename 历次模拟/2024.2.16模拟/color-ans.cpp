#include <cstdio>
using namespace std;
int T, n, x, y, ans, a[1000006];
int read() {
	int s = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s;
}
#define d if ((ans <<= 1) >= 998244353) ans -= 998244353
int main() {
	freopen ("color.in", "r", stdin);
	freopen ("color.out", "w", stdout);
	T = read();
	while (T --) {
		n = read(), x = y = 0, ans = 1;
		for (int i=1; i<=n; i++)
			a[i] = read();
		for (int i=1; i<=n; i++)
			if (a[i] < a[y]) { ans = 0; break; }
			else if (a[i] < a[i-1]) {
				if (a[i] >= a[x]) for (; a[y]<=a[i]; y++) d;
				x = i - 1, y = i;
			} else if (a[i] < a[x]) y = i;
		for (; y<n; y++) d;
		printf ("%d\n", ans);
	}
}