# include <bits/stdc++.h>

using namespace std;

namespace subtask1
{
    int n , mod = 1e9 + 7;
    int ksm(int a , int b) {int res = 1; for(; b; b >>= 1) {if(b & 1) res = 1ll * res * a % mod; a = 1ll * a * a % mod;} return res;}
    void solve()
    {       
        cin >> n;
        if(n & 1) cout << 1ll * (ksm(3 , n) - ksm(3 , n - 1) - 2 + mod) * ksm(8 , mod - 2) % mod * 12 % mod;
        else cout << 1ll * (ksm(3 , n) - ksm(3 , n - 1) + 2 + mod) * ksm(8 , mod - 2) % mod * 12 % mod;
    }
}

namespace subtask2
{
    void solve()
    {

    }
}

int main()
{
    freopen("crack.in" , "r" , stdin);
    freopen("crack.out" , "w" , stdout);
    int T;
    cin >> T;
    switch(T)
    {
        case 1 : subtask1::solve(); break ;
        case 2 : subtask2::solve(); break ;

    }
    return 0;
}