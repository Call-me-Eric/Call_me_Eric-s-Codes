#include <bits/stdc++.h>
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
const int N = 1e2, mod = 998244353;
void add(int &x, int y) { (x += y) >= mod ? (x -= mod) : y; }
void mul(int &x, int y) { x = 1ll * x * y % mod; }
int n, m, q;
vector<int> s, t, tmp;
map<vector<int>, int> mp, f, g;
void work(vector<int> st, int k) {
    f.clear(), f[st] = 1;
    for(int id = 0; id < k; id++) {
        for(auto l : f) {
            tmp = l.first; int v = l.second;
            for(int i = 0; i < tmp.size(); i++) {
                if(!i or tmp[i] < tmp[i - 1])
                    tmp[i]++, add(g[tmp], v), tmp[i]--;
                if(i + 1 == tmp.size() or tmp[i] > tmp[i + 1]) {
                    tmp[i]--; bool f = 0;
                    if(!tmp[i]) f = 1, tmp.pop_back();
                    add(g[tmp], v);
                    f ? tmp.push_back(1), 1 : tmp[i]++;
                }
            } tmp.push_back(1), add(g[tmp], v);
        } swap(f, g), g.clear();
    }
}
void solve(int k) {
    int ans = 0;
    mp.clear(), work(s, k / 2), swap(f, mp), work(t, k - k / 2);
    for(auto l : mp) add(ans, 1ll * l.second * f[l.first] % mod);
    write(ans), putchar('\n');
}
bool edmer;
signed main() {
    freopen("young.in", "r", stdin);
    freopen("young.out", "w", stdout);
    cerr << "[Mermory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
    n = read();
    for(int i = 1; i <= n; i++) s.push_back(read());
    m = read();
    for(int i = 1; i <= m; i++) t.push_back(read());
    q = read();
    while(q--) solve(read());
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}