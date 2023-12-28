# include <bits/stdc++.h>

using namespace std;

# define ull unsigned long long
# define ll long long
# define uint unsigned int 
# define fi first
# define se second

const int N = 5e4 + 5 , M = 1e6;
const ull base = 233;
int m , T , len , st , cnt;
pair< ll , ll > a[N];
ll s[M + 5] , h[N] , b[M] , tot;
ull ha[M + 100] , pw[M + 100];

namespace subtask1
{
    bool solve()
    {
        if(T > 100) return 0;
        for(int i = 1; i <= T; i++) if(a[i].se - a[i].fi + 1 > 200 || a[i].se > 3e5) return 0;
        for(int i = 1; i <= T; i++)
        {
            uint ans = 0;
            for(int l = a[i].fi; l <= a[i].se; l++) for(int r = l; r <= a[i].se; r++) if(s[r] - s[l - 1] > 0) ans++;
            // if(i == 25) for(ll l = a[i].fi; l <= a[i].se; l++) cout << s[l] << ' ';
            cout << ans << '\n';
        }
        return 1;
    }
}

void init()
{
    s[1] = 134775813 % m;
    for(int i = 2; i <= M; i++) s[i] = (1103515245 * s[i - 1] + 1013904223) % m;
    pw[0] = 1;
    for(int i = 1; i <= M; i++) s[i] = (s[i] % 2 == 1 ? 4 : (s[i] % 4 == 0 ? 1 : 3)) , ha[i] = ha[i - 1] * base + s[i] , pw[i] = pw[i - 1] * base;
    // for(int i = 1; i <= M; i++) cout << s[i] << ' ';
    auto get = [](int l , int r)
    {
        return ha[r] - ha[l - 1] * pw[r - l + 1];
    };
    for(int i = M; i; i -= 2) if(get(1 , i / 2) == get(i / 2 + 1 , i)) {len = i / 2; break ;}
    for(int j = 2; j <= 10; j++)
    {
        if(len > 10000) {st = j - 1; break ;}
        for(int i = M / 2; i > 0; i--) if(get(j , i + j - 1) == get(i + j , j + 2 * i - 1)) {len = i; break ;}
    }
    for(int i = 1; i <= M; i++) s[i] -= 3;
    for(int i = st; i <= st + len - 1; i++) tot += s[i];
    for(int i = 1; i <= M; i++) s[i] += s[i - 1];
    // cout << st << ' ' << len << '\n';
}

namespace subtask2
{
    bool solve()
    {
        if(T > 100) return 0;
        for(int i = 1; i <= T; i++) if(a[i].se - a[i].fi + 1 > 100) return 0;
        auto S = [](ll pos)
        {   
            if(pos < st) return s[pos];
            ll t = (pos - st + 1) / len;
            return s[pos - t * len] + t * tot;
        };
        for(int i = 1; i <= T; i++)
        {
            uint ans = 0;
            for(ll l = a[i].fi; l <= a[i].se; l++) for(ll r = l; r <= a[i].se; r++) if(S(r) - S(l - 1) > 0) ans++;
            // if(i == 25) for(ll l = a[i].fi; l <= a[i].se; l++) cout << S(l) << '*';
            cout << ans << '\n';
        }
        return 1;
    }
}

namespace subtask3
{
    int tr[N];
    int Lowbit(int x) {return x & -x;}
    void Upt(int x) {for(; x <= cnt; x += Lowbit(x)) tr[x]++;}
    int Query(int x) {int res = 0; for(; x; x -= Lowbit(x)) res += tr[x]; return res;}
    bool solve()
    {
        if(T > 2000) return 0;
        for(int i = 1; i <= T; i++) if(a[i].se - a[i].fi + 1 > 3000) return 0;
        auto S = [](ll pos)
        {   
            if(pos < st) return s[pos];
            ll t = (pos - st + 1) / len;
            return s[pos - t * len] + t * tot;
        };
        for(int i = 1; i <= T; i++)
        {
            uint ans = 0;
            cnt = 0;
            for(ll j = a[i].fi - 1; j <= a[i].se; j++) b[j] = S(j) , h[++cnt] = b[j];
            // if(i == 25) for(ll j = a[i].fi;)
            sort(h + 1 , h + cnt + 1) , cnt = unique(h + 1 , h + cnt + 1) - h - 1;
            for(ll j = a[i].fi - 1; j <= a[i].se; j++)
            {
                // if(i == 25) cout << b[j] << ' ';
                b[j] = lower_bound(h + 1 , h + cnt + 1 , b[j]) - h;
                ans += Query(b[j] - 1);
                Upt(b[j]);
            }
            // for(ll j = a[i].fi - 1; j <= a[i].se; j++) for(int k = j + 1; k <= a[i].se; k++) if(b[k] > b[j]) ans++;
            fill(tr + 1 , tr + 2000 + 1 , 0);
            cout << ans << '\n';
        }
        return 1;
    }
}

int main()
{
    freopen("dark.in" , "r" , stdin);
    freopen("dark.out" , "w" , stdout);
    cin >> m >> T;
    for(int i = 1; i <= T; i++) cin >> a[i].fi >> a[i].se;
    init();
    // for(m = 200119; m <= 201651; m += 2) init();
    if(subtask1::solve()) return 0;
    if(subtask2::solve()) return 0;
    if(subtask3::solve()) return 0;
    return 0;
}