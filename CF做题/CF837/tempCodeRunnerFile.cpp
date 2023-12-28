#include <bits/stdc++.h>
#define RI int
typedef long long LL;
#define int LL

using namespace std;

int const MAXN = 1e6 + 5;
int Notprime[MAXN], Prime[MAXN], tot;
int stk[MAXN], tong[MAXN], top;

void Euler(int Max) {
  for (RI i = 2; i <= Max; ++i) {
    if (!Notprime[i]) Prime[++tot] = i;
    for (RI j = 1; j <= tot && i * Prime[j] <= Max; ++j) {
      Notprime[i * Prime[j]] = 1;
      if (i % Prime[j] == 0) break;
    }
  }
}

signed main() {
  Euler(1e6);
  LL x, y;
  cin >> x >> y;
  
  LL sq = sqrt(x * 1.0), tmp = x;
  for (RI i = 1; Prime[i] <= sq && i <= tot; ++i) {  // 对 x 质因数分解
    int cnt = 0;
    while (tmp % Prime[i] == 0) ++cnt, tmp /= Prime[i];
    if (cnt) stk[++top] = Prime[i], tong[top] = cnt;
  }
  if (tmp != 1) stk[++top] = tmp, tong[top] = 1;
  
  LL ans = 0;
  while (666) {
    
    LL mmax = 0, pos = 0;
    for (RI i = 1; i <= top; ++i) // 求出小于 y 的最大的 k 使得 gcd(x,k)≠1
      if (tong[i]) {
        tmp = y / stk[i] * stk[i];
        if (tmp > mmax) mmax = tmp, pos = i;
      }
    
    ans += y - mmax;
    y = mmax;
    if (!y) break;
    --tong[pos];
    x /= stk[pos];
    y /= stk[pos];
  }
  cout << ans << endl;
  return 0;
}
