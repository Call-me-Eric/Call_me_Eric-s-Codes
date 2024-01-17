# include <bits/stdc++.h>

using namespace std;

# define ull unsigned long long

const int N = 1e6 + 5 , mod = 998244353 , base = 233;
int n , ans , fac , tot , tmp;
ull pw[N];

struct node
{
    string s;
    vector< int > w;
    vector< ull > ha;
    int len;
} a[N];

ull get(int i , int l , int r) {return a[i].ha[r] - a[i].ha[l - 1] * pw[r - l + 1];}

int F(int i , int j)
{
    for(int l = min(a[i].len , a[j].len); l; l--) if(get(i , a[i].len - l + 1 , a[i].len) == get(j , 1 , l)) return l;
    return 0;
}

namespace subtask1
{
    bool solve()
    {
        if(n > 2000) return 0;
        for(int i = 1; i <= n; i++)
        {
            for(int j = i + 1; j <= n; j++)
            {
                int k1 = F(i , j) , k2 = F(j , i);
                // cout << i << ' ' << j << ' ' << k1 << ' ' << k2 << '\n';
                ans = (1ll * ans + a[i].w[k1] + a[j].w[k1]) % mod;
                ans = (1ll * ans + a[i].w[k2] + a[j].w[k2]) % mod;
            }
        }
        cout << 1ll * ans * fac % mod;
        return 1;
    }
}

namespace subtask2
{
    int s[N];
    bool solve()
    {
        ans = 0;
        for(int i = 1; i <= n; i++) for(int j = 0; j < a[i].len; j++) if(a[i].s[j] != 'a') return 0;
        sort(a + 1 , a + n + 1 , [](node x , node y) {return x.len < y.len;});
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= a[i].len; j++) ans = (ans + 2ll * a[i].w[j] % mod * s[j] % mod) % mod;
            ans = (ans + 2ll * a[i].w[a[i].len] % mod * (n - i) % mod) % mod;
            s[a[i].len]++;
        }
        cout << 1ll * ans * fac % mod;
        return 1;
    }
}

int main()
{
    freopen("unpredictable.in" , "r" , stdin);
    freopen("unpredictable.out" , "w" , stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    pw[0] = 1;
    for(int i = 1; i < N; i++) pw[i] = pw[i - 1] * base;
    cin >> n;
    fac = 1; for(int i = 1; i < n; i++) fac = 1ll * fac * i % mod;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i].s;
        a[i].len = a[i].s.length() , tot += a[i].len;
        a[i].w.push_back(0) , a[i].ha.push_back(0);
        for(int j = 1 , x; j <= a[i].len; j++)
        {
            cin >> x;
            a[i].w.push_back(x);
            a[i].ha.push_back(a[i].ha[j - 1] * base + a[i].s[j - 1] - 'a');
        }
    }
    if(subtask1::solve()) return 0;
    if(subtask2::solve()) return 0;
    return 0;
}