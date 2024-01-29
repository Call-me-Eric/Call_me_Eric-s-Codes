#include <bits/stdc++.h>
#define int long long 
using namespace std;

inline int read() {
    int x = 0, f = 0; char ch = getchar();
    while(ch < '0' or ch > '9') f |= (ch == '-'), ch = getchar();
    while(ch >= '0' and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}
int __stk[128], __top;
inline void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    do { __stk[++__top] = x % 10, x /= 10; } while(x);
    while(__top) putchar(__stk[__top--] + '0');
}
bool stmer;
int n, m, r, g, b;
char ch[3] = {'r', 'g', 'b'};
bool edmer;
signed main() {
    // freopen("T.in", "r", stdin);
    freopen("rgb.in", "w", stdout);
    cerr << "[Mermory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
    srand(time(0)), n = 250, m = n * (n - 1) / 2, r = g = b = n / 3;
    b = 0, r = g = n / 2, r--;
    write(r), putchar(' '), write(g), putchar(' '), write(b), putchar(' '), write(m), putchar('\n');
    for(int i = 1; i < n; i++)
        for(int j = i + 1; j <= n; j++) {
            write(i), putchar(' '), write(j), putchar(' ');
            putchar(ch[rand() % 2]), putchar('\n');
        }

    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}