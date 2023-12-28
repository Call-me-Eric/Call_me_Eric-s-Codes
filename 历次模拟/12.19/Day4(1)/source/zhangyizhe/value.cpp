# include <bits/stdc++.h>

using namespace std;

# define ll long long

int read()
{
# define C ch = getchar()
    int x = 0; char C;
    for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x;
}

const int N = 150000 + 5;
int n , h[N] , cnt , lst;
ll ans , tmp;

struct node
{
    ll a , b;
    node() {}
    node(int a , int b) : a(a) , b(b) {}
} a[N] , b[N];

struct BIT
{
    int s[N];
    int Lowbit(int x) {return x & -x;}
    void Upt(int x) {for(; x <= cnt; x += Lowbit(x)) s[x]++;}
    int Query(int x) {int res = 0; for(; x; x -= Lowbit(x)) res += s[x]; return res;}
} bit;

namespace subtask1
{
    bool solve()
    {
        if(n > 3000) return 0;
        sort(a + 1 , a + n + 1 , [](node x , node y) {return x.a < y.a;});
        sort(h + 1 , h + cnt + 1);
        cnt =  unique(h + 1 , h + cnt + 1) - h - 1;
        for(int i = 1; i <= n; i++) a[i].b = lower_bound(h + 1 , h + cnt + 1 , a[i].b) - h;
        lst = 1 , ans = a[1].a * n;
        for(int i = 2; i <= n; i++)
        {
            ll res = a[i].a * (n - i + 1);
            bit.Upt(a[i - 1].b);
            if(a[i - 1].b >= lst) 
            {
                for(int j = lst; j <= a[i - 1].b; j++) if(bit.Query(j) - bit.Query(j - 1))
                {
                    ll t = h[j] * (i - 1 - bit.Query(j - 1));
                    if(tmp < t)
                    {
                        tmp = t;
                        lst = j;
                    }
                }
            }
            else
            {
                for(int j = 1; j <= a[i - 1].b; j++) if(bit.Query(j) - bit.Query(j - 1))
                {
                    ll t = h[j] * (i - 1 - bit.Query(j - 1));
                    if(tmp < t)
                    {
                        tmp = t;
                        lst = j;
                    }
                }
            }
            ans = max(ans , res + tmp);
        }
        cout << ans;
        return 1;
    }
}

int main()
{
    freopen("value.in" , "r" , stdin);
    freopen("value.out" , "w" , stdout);
    n = read();
    for(int i = 1; i <= n; i++)
    {
        a[i].a = read() , a[i].b = read();
        h[++cnt] = a[i].b;
    }
    if(subtask1::solve()) return 0;
    for(int i = 2; i <= n; i++)
    {
        ll res = a[i].a * (n - i + 1) , tmp = 0;
        bit.Upt(a[i - 1].b);
        int l = 1 , r = cnt;
        while(l <= r)
        {
            int lmid = (r - l + 1) / 3 + l , rmid = r - (r - l + 1) / 3;
            ll lans = (bit.Query(lmid) - bit.Query(lmid - 1) != 0) * h[lmid] * (i - 1 - bit.Query(lmid - 1));
            ll rans = (bit.Query(rmid) - bit.Query(rmid - 1) != 0) * h[rmid] * (i - 1 - bit.Query(rmid - 1));
            if(lans < rans) tmp = max(tmp , rans) , l = lmid + 1;
            else tmp = max(tmp , lans) , r = rmid - 1;
        }
        ans = max(ans , res + tmp);
    }
    cout << ans;
    return 0;
}