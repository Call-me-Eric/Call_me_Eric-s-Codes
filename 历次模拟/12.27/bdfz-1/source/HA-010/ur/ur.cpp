#include <cmath>
#include <cstdio>
#include <unordered_map>
typedef double db; int n, k;
const db PI = acos(-1.0);
namespace N36
{
typedef unsigned long long ull;
std::unordered_map<ull, int> mp; db alp[4][40]; int tn[4], ans[40];
ull Hash(db x, db y)
{
    ull a = x * 1e9, b = y * 1e9;
    a = (a << 32) + b; return a;
}
void main()
{
    db now = 0, stp = PI * 2 / n;
    for (int i = 0; i < n; ++i)
    {
        if (now < PI / 2) alp[0][tn[0]++] = now;
        else if (now < PI) alp[1][tn[1]++] = now - PI / 2;
        else if (now < PI * 3 / 2) alp[2][tn[2]++] = now - PI;
        else alp[3][tn[3]++] = 2 * PI - now;
        now += stp;
    }
    int all = 1 << (tn[0] + tn[3]);
    for (int S = 0; S < all; ++S)
    {
        db now = 0, tot = 0;
        for (int i = 0; i < tn[0]; ++i)
            if (S & (1 << i)) now += sin(alp[0][i]), tot += cos(alp[0][i]);
        for (int i = 0; i < tn[3]; ++i)
            if (S & (1 << (tn[0] + i))) now -= sin(alp[3][i]), tot += cos(alp[3][i]);
        auto o = Hash(now, tot);
        if ((mp.find(o) == mp.end() || __builtin_popcount(mp[o]) < __builtin_popcount(S))) mp[o] = S;
    }
    all = 1 << (tn[1] + tn[2]);
    int cnt = 0;
    for (int S = 0; S < all; ++S)
    {
        db now = 0, tot = 0;
        for (int i = 0; i < tn[1]; ++i)
            if (S & (1 << i)) now += cos(alp[1][i]), tot += sin(alp[1][i]);
        for (int i = 0; i < tn[2]; ++i)
            if (S & (1 << (i + tn[1]))) now -= sin(alp[2][i]), tot += cos(alp[2][i]);
        auto o = Hash(-now, tot);
        if (mp.find(o) != mp.end() && __builtin_popcount(mp[o]) + __builtin_popcount(S) > cnt && __builtin_popcount(mp[o]) + __builtin_popcount(S) <= k)
        {
            int T = mp[o];
            cnt = __builtin_popcount(T) + __builtin_popcount(S);
            for (int i = 0; i < tn[0]; ++i) ans[i] = (T >> i) & 1;
            for (int i = 0; i < tn[1]; ++i) ans[i + tn[0]] = (S >> i) & 1;
            for (int i = 0; i < tn[2]; ++i) ans[i + tn[0] + tn[1]] = (S >> (i + tn[1])) & 1;
            for (int i = 0; i < tn[3]; ++i) ans[i + tn[0] + tn[1] + tn[2]] = (T >> (i + tn[0])) & 1;
        }
    }
    for (int i = 0; i < n; ++i) printf("%d", ans[i]);
    puts("");
}
} // namespace N36
namespace NPrime
{
void main()
{
    for (int i = 1; i <= n; ++i) putchar(k == n ? '1' : '0');
}
} // namespace NPrime
int main()
{
    freopen("ur.in", "r", stdin); freopen("ur.out", "w", stdout);
    scanf("%d%d", &n, &k);
    if (n <= 36) N36::main();
    else NPrime::main();
    return 0;
}