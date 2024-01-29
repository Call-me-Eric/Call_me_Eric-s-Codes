#include <bits/stdc++.h>
using namespace std;
int n, k;
pair<int, int> ans={-1,1};
inline void calc(int x)
{
    if(x==1)return;
    cerr << x << ' ';
    int v = k / x;
    ans = max(ans, {v * x, x});
}
inline void prt(int x)
{
    for (int i = x; i; --i)
    {
        for (int i = k / x; i; --i)
            putchar('1');
        for (int i = (n/x) - k / x; i; --i)
            putchar('0');
    }
}

int main()
{
    freopen("ur.in", "r", stdin);
    freopen("ur.out", "w", stdout);
    scanf("%d %d", &n, &k);
    int mx = sqrt(n);
    for (int i = 1; i <= mx; ++i)
    {
        if (n % i)
            continue;
        calc(i), calc(n / i);
    }
    prt(ans.second);
    return 0;
}