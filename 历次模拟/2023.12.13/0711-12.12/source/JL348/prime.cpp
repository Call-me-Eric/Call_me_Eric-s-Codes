#include <bits/stdc++.h>
#define int long long 
using namespace std;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int MAXN = 1000010, mod = 998244353;
int Add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int Sub(int x, int y) { return (x -= y) < 0 ? x + mod : x; }
int Mul(int x, int y) { return 1ll * x * y % mod; }
bool flag[MAXN]; int prime[] = {2, 3, 5, 7, 11, 19, 41, 61, 89, 409, 449, 499, 881, 991, 6469, 6949, 9001, 9049, 9649, 9949, 60649, 666649, 946669, 60000049, 66000049, 66600049};
int ans[MAXN];
int calc(int x) {
    if (x <= 100000) return ans[x];
}
signed main() {
    for (int i = 0; i <= 20; i++) flag[prime[i]] = true;
    for (int i = 1; i <= 100000; i++) {
        static int digit[10], cnt, F; cnt = 0, F = 1;
        int x = i; while (x) digit[cnt++] = x % 10, x /= 10;
        for (int s = 1; s < (1 << cnt); s++) {
            static int num; num = 0;
            for (int j = 0, tmp = 0; j < cnt; j++) if ((s >> j) & 1) 
                num += digit[j] * pow(10, tmp++);
            if (flag[num]) { F = 0; break; }
        }
        ans[i] = ans[i - 1] + F;
    }
    int T = read();
    while (T--) {
        int L = read(), R = read();
        printf("%lld\n", Sub(calc(R), calc(L - 1)));
    }
}
