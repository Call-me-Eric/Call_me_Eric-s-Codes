# include <bits/stdc++.h>

using namespace std;

int read()
{
# define C ch = getchar()
    int x = 0; char C;
    for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x;
}

const int N = 710 , mod = 998244353;
int n , q , a[N][N] , ans[N];

int ksm(int a , int b) {int res = 1; for(; b; b >>= 1 , a = 1ll * a * a % mod) if(b & 1) res = 1ll * res * a % mod; return res;}
int inv(int x) {return ksm(x , mod - 2);}

void Gauss()
{
    static int f[N][N];
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n + 1; j++) f[i][j] = a[i][j];
    }
    for(int i = 1; i <= n; i++)
    {
        int l = i;
        if(!f[i][i])
        {
            for(int j = i + 1; j <= n; j++) if(f[j][i]) {l = j; break ;}
            // cout << l << '*' << endl;
            if(l == i) continue ;
            for(int j = i; j <= n + 1; j++) swap(f[l][j] , f[i][j]);
        }
        int invi = inv(f[i][i]);
        for(int j = i + 1; j <= n; j++)
        {
            int res = 1ll * f[j][i] * invi % mod;
            for(int k = i; k <= n + 1; k++) f[j][k] = (f[j][k] - 1ll * f[i][k] * res % mod + mod) % mod;
        }
    }
    for(int i = 1; i <= n; i++) ans[i] = 0;
    if(!f[n][n] && !f[n][n + 1]) return cout << "Many\n" , void();
    if(!f[n][n] && f[n][n + 1]) return cout << "No\n" , void();
    for(int i = n; i; i--)
    {
        int res = f[i][n + 1];
        for(int j = n; j > i; j--) res = (res - 1ll * ans[j] * f[i][j] % mod + mod) % mod;
        ans[i] = 1ll * res * inv(f[i][i]) % mod;
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << ' '; cout << '\n';
}

int main()
{
    freopen("eq.in" , "r" , stdin);
    freopen("eq.out" , "w" , stdout);
    n = read() , q = read();
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n + 1; j++)
        {
            a[i][j] = read();
        }
    }
    Gauss();
    for(int i = 1; i <= q; i++)
    {
        int z = read();
        for(int j = 1; j <= n + 1; j++) a[z][j] = read();
        Gauss();
    }
    return 0;
}