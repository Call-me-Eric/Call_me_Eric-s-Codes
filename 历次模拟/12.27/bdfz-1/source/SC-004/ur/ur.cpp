#include<bits/stdc++.h>
#define ll long long
#define rep(i, x, y) for(int i = (x), stozzh = (y); i <= stozzh; i++)
#define irep(i, x, y) for(int i = (x), stozzh = (y); i >= stozzh; i--)
using namespace std;
using vint = vector<int>;
using pii = pair<int, int>;
#define let const auto
#define fi first
#define se second
#define pb emplace_back
#define il inline
int read() {
    int res = 0, flag = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') flag = -1; c = getchar(); }
    while(c >= '0' && c <= '9') res = res * 10 + c - '0', c = getchar();
    return res * flag;
}
template<typename T> il void tmax(T &x, const T y) { if(x < y) x = y; }

#define X real()
#define Y imag()
using db = long double;
using point = complex<db>;
const db eps = 1e-9;
db pi = acos(-1);

namespace brute {
point a[25], sum[1 << 20];
void Main(int n, int k) {
    rep(i, 0, n - 1) {
        db theta = 2 * pi / n * i;
        a[i] = {cos(theta), sin(theta)};
    }
    rep(s, 1, (1 << n) - 1) {
        int i = __builtin_ctz(s);
        sum[s] = sum[s ^ 1 << i] + a[i]; 
    }
    int ans = 0, ansp = 0;
    rep(s, 1, (1 << n) - 1) if(fabs(sum[s].X) <= eps && fabs(sum[s].Y) <= eps) {
        int nv = __builtin_popcount(s);
        if(nv > ans && nv <= k) ans = nv, ansp = s;
    }
    rep(i, 0, n - 1) cout << ((ansp >> i) & 1);
    cout << '\n';
}
}

namespace brute2 {
point a[40];
pair<point, int> sum1[1 << 18], sum2[1 << 18];
void Main(int n, int k) {
    int num1 = n / 2, num2 = n - num1;
    rep(i, 0, n - 1) {
        db theta = 2 * pi / n * i;
        a[i] = {cos(theta), sin(theta)};
    }
    int l1 = (1 << num1) - 1, l2 = (1 << num2) - 1;
    rep(s, 1, l1) {
        int i = __builtin_ctz(s);
        sum1[s].fi = sum1[s ^ 1 << i].fi + a[i]; 
        sum1[s].se = sum2[s].se = s;
    }
    rep(s, 1, l2) {
        int i = __builtin_ctz(s);
        sum2[s].fi = sum2[s ^ 1 << i].fi - a[num1 + i]; 
    }
    auto cmp = [&](const point &a, const point &b) { return fabs(a.X - b.X) <= 1e-11 ? a.Y < b.Y : a.X < b.X; };
    auto cmp2 = [&](const pair<point, int> &a, const pair<point, int> &b) { return cmp(a.fi, b.fi); };
    sort(sum1, sum1 + l1 + 1, cmp2), sort(sum2, sum2 + l2 + 1, cmp2);

    int ans = 0;
    ll ansp = 0;

    int ct = 0;
    rep(i, 0, l1) {
        while(ct != l2 && cmp(sum2[ct].fi, sum1[i].fi)) ct++; 
        rep(j, max(ct - 20, 0), min(ct + 20, l2)) {
            point cur = sum1[i].fi - sum2[j].fi;
            if(fabs(cur.X) > eps || fabs(cur.Y) > eps) continue;
            ll v = sum1[i].se | ((ll)sum2[j].se << num1);
            int t = __builtin_popcountll(v);
            if(t <= k && t > ans) ansp = v, ans = t;
        }
    }
    rep(i, 0, n - 1) cout << (ansp >> i & 1);
    cout << '\n';
}   
}
vector<pii> fen(int n) {
    vector<pii> res;
    for(int i = 2; i * i <= n; i++) if(n % i == 0) {
        int num = 0;
        while(n % i == 0) n /= i, num++;
        res.pb(i, num);
    }
    if(n != 1) res.pb(n, 1);
    return res;
} 
signed main() {
    freopen("ur.in", "r", stdin);
    freopen("ur.out", "w", stdout);
    int n = read(), k = read();
    if(k <= 0) return cout << string(n, '0') << '\n', 0;
    if(k == n) return cout << string(n, '1') << '\n', 0;
    if(n <= 20) return brute::Main(n, k), 0;
    auto vec = fen(n);
    string ans(n, '0');
    if(vec.size() == 1) {
        int p = vec[0].fi;
        int t = k / p, d = n / p;
        rep(i, 0, t - 1) for(int j = i; j < n; j += d) ans[j] = '1';
        cout << ans << '\n';
        return 0;
    }
    if(vec.size() <= 2 && vec[0].se == 1 && vec[1].se == 1) {
        int p = vec[0].fi, q = vec[1].fi;
        if(k / p * p < k / q * q) swap(p, q);
        int t = k / p, d = n / p;
        rep(i, 0, t - 1) for(int j = i; j < n; j += d) ans[j] = '1';
        cout << ans << '\n';
        return 0;
    }
    if(n <= 36) return brute2::Main(n, k), 0;
    return 0;
}
