#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define repn(i, n) for (int i = 1; i <= (n); i++)
int n, m, ans;
const int N = 100010, INF = 0x3f3f3f3f;
int x[N], y[N], best[N];
int main() {
  scanf("%d%d%*d%*d", &n, &m);
  rep(i, n) scanf("%d", x + i);
  repn(i, m) scanf("%d", y + i);
  y[0] = -INF;
  y[m + 1] = INF;
  memset(best, INF, sizeof(best));
  rep(i, n) {
    int j = lower_bound(y, y + m + 2, x[i]) - y;
    int dis = min(x[i] - y[j - 1], y[j] - x[i]);
    if (y[j] - x[i] > dis ||
        (x[i] - y[j - 1] == dis && (best[j - 1] == dis || best[j - 1] == INF)))
      --j;
    if (best[j] == INF || best[j] == dis) ++ans;
    best[j] = min(best[j], dis);
    printf("i=%d %d\n",i,ans);
  }
  printf("%d\n", n - ans);
  return 0;
}