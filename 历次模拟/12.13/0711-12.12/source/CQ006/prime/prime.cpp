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
const int N = 1e8, mod = 998244353;
struct node {
    string s;
    int p[22];
} st;
int T, cnt, tot;
string s, t[26];
vector<int> p = { 2, 3, 5, 7, 11, 19, 41, 61, 89, 409, 449, 499, 881, 991, 6469, 6949, 9001, 9049, 9649, 9949, 60649, 666649, 946669, 60000049, 66000049, 66600049, };
vector<node> ans, f, g;
char e[6] = {'0', '1', '4', '6', '8', '9'};
bool operator < (string x, string y) {
    if(x.size() != y.size()) return x.size() < y.size();
    for(int i = x.size() - 1; i + 1; i--)
        if(x[i] != y[i]) return x[i] < y[i];
    return 0;
}
bool check(int x, int id) {
    s = ""; int pos = 0;
    while(x) s += x % 10 + '0', x /= 10;
    for(int i = 0; i < s.size(); i++)
        if(pos < t[id].size() and s[i] == t[id][pos]) pos++;
    return pos >= t[id].size();
}
bool check(string x, int id) {
    int pos = 0;
    for(int i = 0; i < x.size(); i++)
        if(pos < t[id].size() and x[i] == t[id][pos]) pos++;
    return pos >= t[id].size();
}
void init() {
    for(int i = 0; i < 26; i++) {
        int x = p[i];
        while(x) t[i] += x % 10 + '0', x /= 10;
    } f.push_back(st);
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 6; j++) for(auto l : f) {
            node tmp = l; tmp.s += e[j]; bool f1 = 0;
            for(int k = 4; k < 26 and !f1; k++) {
                if(t[k][tmp.p[k - 4]] == e[j]) tmp.p[k - 4]++;
                if(tmp.p[k - 4] == t[k].size()) f1 = 1;
            }
            if(!f1) g.push_back(tmp);
        } swap(f, g), g.clear();
        for(auto l : f) if(l.s.back() != '0') ans.push_back(l);
    } 
    st = f[0], st.s.push_back('1'), ans.push_back(st);
}
int work(int x) {
    s = ""; 
    while(x) s += x % 10 + '0', x /= 10;
    int l = 0, r = ans.size() - 1, pos = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(s < ans[mid].s) r = mid - 1;
        else l = mid + 1, pos = mid;
    }
    return pos;
}
void solve() {
    int L = read(), R = read();
    int res = work(R) - work(L - 1);
    write(res), putchar('\n');
}
bool edmer;
signed main() {
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    cerr << "[Mermory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
    init(), T = read(); while(T--) solve();
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}