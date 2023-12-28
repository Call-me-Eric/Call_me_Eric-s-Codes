# include <bits/stdc++.h>

using namespace std;

# define int long long

const int N = 2e3 + 5 , mod = 1e9 + 7;
int n , a[N];

int ksm(int a , int b) {int res = 1; for(; b; b >>= 1) {if(b & 1) res = 1ll * res * a % mod; a = 1ll * a * a % mod;} return res;}

int inv(int x) {return ksm(x , mod - 2);}

namespace subtask1
{
    int A , B;
    int F(int x)
    {
        int X = x * (x - 1) * (A + B - x) * (A + B - x + 1) , Y = (A + B) * (A + B) * (A + B - 1) * (A + B - 1);
        // cout << X << ' ' << Y << endl;
        int y = 1ll * X * inv(Y) % mod;
        return 2ll * inv(1ll * (1 - y + mod) * (1 - y + mod) % mod) % mod * y % mod;
    }
    bool solve()
    {
        if(n != 2) return 0;
        A = a[1] , B = a[2];
        int res = 1 , ans = 0;
        for(int i = A; i; i--) 
        {
            res = 1ll * res * inv(A + B) % mod * inv(A + B - 1) % mod * i % mod * (A + B - i) % mod;
            ans = (ans + res) % mod;
        }
        res = 1;
        for(int i = B; i; i--)
        {
            res = 1ll * res * inv(A + B) % mod * inv(A + B - 1) % mod * i % mod * (A + B - i) % mod;
            ans = (ans + res) % mod;
        } 
        // cout << ans << endl;
        for(int i = A; i > 1; i--) ans = (ans + F(i)) % mod;
        for(int i = B; i > 1; i--) ans = (ans + F(i)) % mod;
        cout << ans;
        return 1;
    }
}

signed main()
{
    freopen("hard.in" , "r" , stdin);
    freopen("hard.out" , "w" , stdout);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    if(subtask1::solve()) return 0; 
    return 0;
}