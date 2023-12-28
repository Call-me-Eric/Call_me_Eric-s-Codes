# include <bits/stdc++.h>

using namespace std;

int n , k;

namespace subtask1
{
    bool solve()
    {
        if(k == n) {for(int i = 1; i <= n; i++) cout << 1; return 1;}
        if(k <= 1 && n > 1) {for(int i = 1; i <= n; i++) cout << 0; return 1;}
        return 0;
    }
}

namespace subtask2
{
    vector< int > vec;
    int mx , p;
    bool solve()
    {
        // if(n > 36) return 0;
        for(int i = 2; i <= n; i++) if(n % i == 0) vec.push_back(i);
        for(int x : vec)
        {
            if(k / x * x > mx) mx = k / x * x , p = x;
        }
        // cout << mx << ' ' << p << endl;
        if(!p) for(int i = 1; i <= n; i++) cout << 0;
        else
        {
            int cnt = k / p , t = k / cnt;
            for(int i = 1; i <= t; i++) 
            {
                for(int j = 1; j <= cnt; j++) cout << 1;
                for(int j = 1; j <= n / p - cnt; j++) cout << 0;
            }
        }
        return 1;
    }
}

int main()
{
    freopen("ur.in" , "r" , stdin);
    freopen("ur.out" , "w" , stdout);
    cin >> n >> k;
    if(subtask1::solve()) return 0;
    if(subtask2::solve()) return 0;

    return 0;
}