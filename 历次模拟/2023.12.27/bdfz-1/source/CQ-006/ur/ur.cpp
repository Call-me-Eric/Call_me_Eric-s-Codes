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
const int N = 1e6 + 10;
int n, k, ans;
namespace sub1 {
    unordered_map<int, int> f, g;
    vector<int> p;
    void solve() {
        f[0] = 0;
        for(int i = 2; i < n; i++) if(!(n % i)) {
            bool f = 1;
            for(int j = i + i; j < n; j += i) if(!(n % j)) f = 0;
            if(f) p.push_back(i);
        }
        for(int i = 0; i < n; i++) {
            for(int s : p) {
                if(s <= i) continue;
                int to = 1ll << i, val = n / s;
                for(int j = (i + s) % n; j ^ i; j = (j + s) % n) to |= 1ll << j;
                for(auto l : f) {
                    int v = val + l.second;
                    if(!(l.first & to) and v <= k) g[l.first | to] = v;
                }
            } for(auto l : g) f[l.first] = l.second; g.clear();
        } int mx = 0;
        for(auto l : f) if(l.second > mx) mx = l.second, ans = l.first;
        for(int i = 0; i < n; i++) putchar((ans >> i & 1) + '0'); 
    }
}
namespace sub2 {
    vector<int> p;
    int res[N];
    void solve() {
        int tmp = n;
        for(int i = 2; i * i <= tmp; i++)
            while(!(tmp % i)) p.push_back(i), tmp /= i;
        if(tmp ^ 1) p.push_back(tmp);
        if(p.size() == 1) {
            for(int i = 0; i < n; i++) putchar('0');
            exit(0);
        }
        if(p.size() == 2) {
            int x = n / p[0], y = n / p[1];
            if(k % y < k % x) swap(x, y);
            for(int i = 0; i < k / x; i++) 
                for(int j = i; j < n; j += n / x) res[j] = 1;
            for(int i = 0; i < n; i++) putchar(res[i] + '0');
            exit(0);
        }
        int x = p[0];
        for(auto l : p) if(l ^ x) x = 0;
        if(x) {
            for(int i = 0; i < k / x; i++)
                for(int j = i; j < n; j += n / x) res[j] = 1;
            for(int i = 0; i < n; i++) putchar(res[i] + '0');
            exit(0);
        }
    }
}
bool edmer;
signed main() {
    freopen("ur.in", "r", stdin);
    freopen("ur.out", "w", stdout);
    cerr << "[Mermory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
    n = read(), k = read();
    if(k == n) {
        for(int i = 0; i < n; i++) putchar('1');
        exit(0);
    }
    if(k <= 1) {
        for(int i = 0; i < n; i++) putchar('0');
        exit(0);
    }
    if(n <= 36) sub1 :: solve();
    else sub2 :: solve();
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}