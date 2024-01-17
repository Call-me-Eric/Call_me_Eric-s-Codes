#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
typedef long long LL;

bool check(int l, int r, int a[])
{
    if (l > r) return true;
    int ones = 0;
    for (int i = l; i <= r; ++i)
        ones += a[i] == 1;
    if ((ones >> 1) & 1) return false;

    while (l < r && a[l] == a[r]) ++l, --r;
    for (int i = l; i <= r; i += 2)
        if (a[i] ^ a[i + 1]) return false;
    return true;

}

int solve()
{
    int n, sum = 0;
    static int a[MAXN];
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]), sum ^= a[i];
    if (sum == 0) return 0;
    if (n % 2 == 0) return 1;
    if (n == 1) return 1;

    for (int i = 30; ; --i)
    {
        if ((sum >> i) & 1)
        {
            for (int j = 1; j <= n; ++j)
                a[j] = (a[j] >> i) & 1;
            break;
        }
    }

    if (a[1] && check(2, n, a)) return 1;
    if (a[n] && check(1, n - 1, a)) return 1;
    return -1;
}

int main()
{
    //freopen("in.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    while (T--)
    {
        int res = solve();
        if (res == 1) puts("First");
        else if (res == 0) puts("Draw");
        else puts("Second");
    }

    return 0;
}
