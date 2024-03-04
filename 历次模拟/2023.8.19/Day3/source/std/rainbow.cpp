#include <cstdio>
#include <iostream>
using namespace std;
const int N = 2001;

long long t, n, m, a[N][N], f[N][N], g[N] = {1};

bool vis[N * N];

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  for (; !isdigit(c); c = getchar()) f |= (c == '-');
  for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return f ? -x : x;
}

int main() {
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
    n = rd(); m = rd();
    for(int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j]=rd();
    for (int i = 1; i <= n; i++)
        f[i][m] = 1;
    for (int j = 1; j <= m; j++)
        f[n][j] = 1;
    for (int i = n - 1; i > 0; i--)
        for (int j = m - 1; j > 0; j--) {
            if(a[i][j] == a[i + 1][j + 1])
                f[i][j] = min(min(f[i + 1][j], f[i][j + 1]), f[i + 1][j + 1]) + 1;
            else
                f[i][j] = 1;
        }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            g[j] = g[j - 1] - 1;
            while(g[j] < f[i][j] && !vis[a[i][j + g[j]]] && !vis[a[i + g[j]][j]] && (!g[j] || a[i][j + g[j]] != a[i + g[j]][j])) {
                vis[a[i][j + g[j]]] = true;
                vis[a[i + g[j]][j]] = true;
                g[j]++;
            }
            ans += g[j];
            vis[a[i + g[j] - 1][j]] = false;
            if(g[j] > 1)
                vis[a[i + g[j] - 2][j]] = false;
        }
    }
    printf("%lld\n", ans);
}