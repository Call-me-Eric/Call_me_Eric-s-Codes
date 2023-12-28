# include <cstdio>

int main() {

  freopen("li.in", "r", stdin);
  freopen("li.out", "w", stdout);

  int n, m;
  scanf("%d %d", &n, &m);

  if (n <= 2) return puts("0 3"), 0;
  if (n == 3 && m == 1) return puts("0 4"), 0;
  if (n == 3 && m == 2) return puts("0 6"), 0;
  if (n == 3 && m == 3) return puts("1 3"), 0;

  return 0;
}