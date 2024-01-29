#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int P = 998244353;
const int N = 705;
int n, q;
inline int qpow(ll base, int exp)
{
    ll ans = 1;
    while (exp)
    {
        if (exp & 1)
            ans = base * ans % P;
        base = base * base % P, exp >>= 1;
    }
    return ans;
}
inline int inv(ll base)
{
    return qpow(base, P - 2);
}
struct vec
{
    int a[N]{};
    inline int &operator[](int x)
    {
        return a[x];
    }
    inline int operator[](int x) const
    {
        return a[x];
    }
    inline vec operator+(vec b) const
    {
        for (int i = 0; i <= n; ++i)
            b[i] = (b[i] + a[i]) % P;
        return b;
    }
    inline vec operator*(ll b) const
    {
        vec t = *this;
        for (int i = 0; i <= n; ++i)
            t[i] = t[i] * b % P;
        return t;
    }
    inline void operator-=(const vec &b)
    {
        for (int i = 0; i <= n; ++i)
        {
            a[i] = a[i] < b[i] ? (a[i] - b[i] + P) % P : a[i] - b[i];
        }
    }
    inline void operator*=(ll b)
    {
        for (int i = 0; i <= n; ++i)
            a[i] = a[i] * b % P;
    }
    inline void operator/=(ll b)
    {
        b = inv(b);
        *this *= (b);
    }
    inline bool err() const
    {
        bool f = 1;
        for (int i = 1; i <= n; ++i)
            f &= a[i] == 0;
        return f && a[0];
    }
    inline void read()
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        scanf("%d", a);
    }
};
struct LinerBase
{
    pair<vec, int> a[N];
    LinerBase()
    {
        for (int i = 0; i < N; ++i)
            a[i].second = -1;
    }
    inline void ins(pair<vec, int> x, int del)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (a[i].second == del)
            {
                swap(a[i], x);
                return;
            }
            if (x.first[i] == 0)
                continue;
            if (x.second > a[i].second)
                swap(a[i], x);
            if(a[i].first[i]==0)
                swap(a[i],x);
            else
            {
                a[i].first /= a[i].first[i];
                x.first -= a[i].first * x.first[i]; //-=和*一起处理会调加乘熔积加速？
            }
        }
    }
    inline vec get() const
    {
        LinerBase t = *this;
        for (int i = n; i; --i)
        {
            ll iv = inv(t.a[i].first[i]);
            int a = t.a[i].first[i] * iv % P;
            int b = t.a[i].first[0] * iv % P;
            t.a[i].first[i] = a;
            t.a[i].first[0] = b;
            for (int j = i - 1; j; --j)
            {
                ll x = t.a[j].first[i];
                t.a[j].first[i] = 0, t.a[j].first[0] = (t.a[j].first[0] - b * x) % P;
            }
        }
        vec res;
        for (int i = 1; i <= n; ++i)
            res[i] = t.a[i].first[0];
        return res;
    }
    inline int calc() const
    {
        bool none = 0;
        // for(int i=1;i<=n;++i)
        //     cerr<<a[i].first[i]<<' ';
        // cerr<<'\n';
        for (int i = n; i; --i)
        {
            if (a[i].first.err())
                return -1;
            none |= a[i].first[i] == 0;
        }
        if (none)
        {
            return 2;
        }
        return 1;
    }
};
LinerBase lb;
pair<vec, pair<int, int>> mem[N];
struct Seq
{
    vec v;
    int st, ed;
    int q;
};
vector<Seq> seq;
pair<int, vec> ans[N];
int main()
{

    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);

    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        mem[i].first.read();
        mem[i].second = {0, 0};
    }
    for (int i = 1, x; i <= q; ++i)
    {
        static vec tmp;
        scanf("%d", &x);
        tmp.read();
        seq.push_back({mem[x].first, mem[x].second.first, i - 1, mem[x].second.second});
        mem[x] = {tmp, {i, i}};
    }
    for (int i = 1; i <= n; ++i)
    {
        seq.push_back({mem[i].first, mem[i].second.first, n, mem[i].second.second});
    }
    sort(seq.begin(), seq.end(),
         [](auto a, auto b)
         { return a.st < b.st; });
    int cnt = 0;
    for (auto &i : seq)
    {
        cnt += i.st == 0;
        if (i.v[1])
            cerr << cnt << ' ';
        lb.ins({i.v, i.ed}, i.st - 1);
        if (cnt == n || i.q)
        {
            cnt = 0x3f3f3f3f;
            int f = lb.calc();
            ans[i.q].first = f;
            if (f == 1)
            {
                ans[i.q].second = lb.get();
            }
        }
    }
    for (int i = 0; i <= q; ++i)
    {
        if (ans[i].first == -1)
            puts("No");
        else if (ans[i].first == 2)
            puts("Many");
        else
        {
            for (int j = 1; j <= n; ++j)
                printf("%d ", (ans[i].second[j] + P) % P);
            puts("");
        }
    }
    return 0;
}
