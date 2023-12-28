#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-10;
const double PI = acos(-1);
struct Point {double x,y;};
inline Point operator+ (const Point &a,const Point &b) {return {a.x + b.x,a.y + b.y};}
inline bool operator< (const Point &a,const Point &b) {return abs(a.x - b.x) > EPS ? a.x < b.x : a.y + EPS < b.y;}
using ll = long long;
const int N = 1000005;
int n,kk;Point a[N];
vector<int> get(int kk,int p,int c)
{
    assert(kk % p == 0);
    if (c == 1) return vector<int>(p,!!kk);
    int len = 1;for (int i = 0;i < c;i++) len *= p; 
    if (kk == len) return vector<int>(len,1);
    vector<int> tt = get(kk % (len / p),p,c - 1),ret(len);
    for (int i = 0;i < kk / (len / p);i++)
        for (int j = 0;j < len / p;j++) ret[p * j + i] = 1;
    for (int j = 0;j < len / p;j++) ret[p * j + (kk / (len / p))] = tt[j];
    return ret;
}
int main ()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    ios::sync_with_stdio(false);
    cin >> n >> kk;
    if (kk == n)
    {
        for (int i = 1;i <= n;i++) cout << 1;
        cout << endl;return 0;
    }
    if (kk <= 1)
    {
        for (int i = 1;i <= n;i++) cout << 0;
        cout << endl;return 0;
    }
    if (n <= 36)
    {
        for (int i = 0;i < n;i++) a[i] = {cos(i * PI * 2 / n),sin(i * PI * 2 / n)};
        int m1 = n / 2,m2 = n - m1;
        map<Point,vector<int>> mp1,mp2;
        for (int i = 0;i < (1 << m1);i++)
        {
            Point cur = {0,0};for (int j = 0;j < m1;j++) if ((i >> j) & 1) cur = cur + a[j];
            mp1[cur].push_back(i);
        }
        for (int i = 0;i < (1 << m2);i++)
        {
            Point cur = {0,0};for (int j = 0;j < m2;j++) if ((i >> j) & 1) cur = cur + a[j + m1];
            mp2[cur].push_back(i);
        }
        ll ans = 0;
        for (auto &i : mp1)
        {
            auto &v1 = i.second,v2 = mp2[{-i.first.x,-i.first.y}];
            static int va[45],vb[45];
            fill(va,va + kk,-1);fill(vb,vb + kk,-1);
            for (auto &j : v1) va[__builtin_popcount(j)] = j;
            for (auto &j : v2) vb[__builtin_popcount(j)] = j;
            for (int j = 0,k = kk;j <= kk;j++)
            {
                while (j + k > kk || (k >= 0 && vb[k] == -1)) --k;
                if (k < 0) break;
                if (va[j] != -1)
                {
                    ll tt = va[j] + (ll(vb[k]) << m1);if (__builtin_popcountll(tt) > __builtin_popcountll(ans)) ans = tt;
                }
            }
        }
        for (int i = 0;i < n;i++) cout << ((ans >> i) & 1);
        return 0;
    }
    vector<pair<int,int>> d;
    int tt = n;
    for (int i = 2;i <= n;i++)
    {
        if (tt % i) continue;
        int cnt = 0;while (tt % i == 0) ++cnt,tt /= i;
        d.push_back({i,cnt});
    }
    if (d.size() == 1)
    {
        if (d[0].second == 1)
        {
            for (int i = 1;i <= n;i++) cout << 0;
            cout << endl;return 0;
        }
        kk -= kk % d[0].first;
        for (auto &i : get(kk,d[0].first,d[0].second)) cout << i;
        return 0;
    }
    int ans = 0;for (auto &i : d) ans = max(ans,kk - kk % i.first);
    for (auto &i : d)
        if (kk - kk % i.first == ans)
        {
            int len = 1;for (int j = 0;j < i.second;j++) len *= i.first;
            vector<int> tt = get(ans % len,i.first,i.second),ret(n);
            for (int j = 0;j < ans / len;j++)
                for (int k = 0;k < len;k++) ret[k * (n / len) + j] = 1;
            for (int j = 0;j < len;j++) ret[j * (n / len) + (ans / len)] = tt[j];
            for (int j = 0;j < n;j++) cout << ret[j];
        }
    return 0;
}