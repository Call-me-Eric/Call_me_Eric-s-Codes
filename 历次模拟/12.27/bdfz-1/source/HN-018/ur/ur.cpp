#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define x first
#define y second
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 1000010;

int n, m, ans;
vector<int> to;

signed main()
{
    freopen("ur.in", "r", stdin);
    freopen("ur.out", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    fro(i, 2, n)
        if(n % i == 0)
        {
            if(!ans) ans = i;
            if(floor(m / ans) * ans < floor(m / i) * i)
                ans = i;
        }
    fro(i, 1, ans)
    {
        fro(j, 1, floor(m / ans))
            cout << 1;
        fro(j, floor(m / ans) + 1, n / ans)
            cout << 0;
    }
    return 0;
}