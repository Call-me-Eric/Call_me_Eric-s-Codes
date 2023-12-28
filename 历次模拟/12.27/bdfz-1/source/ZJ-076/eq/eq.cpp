#include <bits/stdc++.h>
using namespace std;
const int N = 705,P = 998244353;
using ll = long long;
int n,q;
vector<ll> operator+ (const vector<ll> &a,const vector<ll> &b)
{
    vector<ll> c(n + 1);for (int i = 0;i <= n;i++) c[i] = (a[i] + b[i]) % P;
    return c;
}
vector<ll> operator- (const vector<ll> &a,const vector<ll> &b)
{
    vector<ll> c(n + 1);for (int i = 0;i <= n;i++) c[i] = (a[i] + P - b[i]) % P;
    return c;
}
vector<ll> operator* (vector<ll> a,ll b)
{
    for (int i = 0;i <= n;i++) a[i] = a[i] * b % P;
    return a;
}
ll qpow(ll a,ll b)
{
    ll ret = 1;
    while (b)
    {
        if (b & 1) ret = ret * a % P;
        a = a * a % P;b >>= 1;
    }
    return ret;
}
struct TNode {int l,r;vector<vector<ll>> v;} t[N << 2];
inline int lc(int pos) {return pos << 1;}
inline int rc(int pos) {return pos << 1 | 1;}
void build(int pos,int l,int r)
{
    t[pos].l = l;t[pos].r = r;if (l == r) return;
    int mid = (l + r) >> 1;build(lc(pos),l,mid);build(rc(pos),mid + 1,r);
}
void modify(int pos,int l,int r,vector<ll> v)
{
    if (t[pos].l == l && t[pos].r == r) {t[pos].v.push_back(v);return;}
    int mid = (t[pos].l + t[pos].r) >> 1;
    if (r <= mid) modify(lc(pos),l,r,v);
    else if (l > mid) modify(rc(pos),l,r,v);
    else modify(lc(pos),l,mid,v),modify(rc(pos),mid + 1,r,v);
}
void solve(int pos,vector<vector<ll>> cur)
{
    for (auto &i : t[pos].v)
    {
        for (auto &j : cur)
        {
            int pivot = 1;while (!j[pivot]) ++pivot;
            ll coef = i[pivot] * qpow(j[pivot],P - 2) % P;
            i = i - j * coef;
        }
        if (count(i.begin() + 1,i.begin() + n + 1,0) == n)
        {
            if (i[0])
            {
                for (int j = t[pos].l;j <= t[pos].r;j++) cout << "No" << endl;
                return;
            }
            continue;
        }
        cur.push_back(i);
    }
    if (t[pos].l == t[pos].r)
    {
        if (int(cur.size()) != n) {cout << "Many" << endl;return;}
        static ll x[N];fill(x + 1,x + n + 1,0);
        reverse(cur.begin(),cur.end());
        for (auto &i : cur)
        {
            int pivot = 1;while (!i[pivot]) ++pivot;
            for (int j = 1;j <= n;j++) i[0] = (i[0] + P - i[j] * x[j] % P) % P;
            x[pivot] = i[0] * qpow(i[pivot],P - 2) % P;
        }
        for (int i = 1;i <= n;i++) cout << x[i] << ' ';
        cout << endl;return;
    }
    solve(lc(pos),cur);solve(rc(pos),cur);
}
vector<ll> a[N];int lst[N];
int main ()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    ios::sync_with_stdio(false);
    cin >> n >> q;build(1,0,q);
    for (int i = 1;i <= n;i++)
    {
        a[i].resize(n + 1);
        for (int j = 1;j <= n;j++) cin >> a[i][j];
        cin >> a[i][0];
    }
    for (int i = 1;i <= q;i++)
    {
        int x;cin >> x;modify(1,lst[x],i - 1,a[x]);
        for (int j = 1;j <= n;j++) cin >> a[x][j];
        cin >> a[x][0];lst[x] = i;
    }
    for (int i = 1;i <= n;i++) modify(1,lst[i],q,a[i]);
    solve(1,{});
    return 0;
}