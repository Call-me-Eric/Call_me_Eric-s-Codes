#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 19;
const int mod = 998244353;

int n, m;
int dp[N][3][2][3][3][2][5][4][6][3][3][8][3];
int vis[N][3][2][3][3][2][5][4][6][3][3][8][3];

/*
f0: 904
f1: 11 14 16
f4: 199
f5: 188
f6: 91 98
f7: 94606
f8: 9646
f9: 946666
f10:994
f11:944
f12:94000006
f13:
*/

inline bool update(int add, int &f0, int &f1, int &f4, int &f5, int &f6, int &f7, int &f8, int &f9, int &f10, int &f11, int &f12, int &f13)
{
    if(add == 9 && f0 == 0) f0++;
    else if(add == 0 && f0 == 1) f0++;
    else if(add == 4 && f0 == 2) f0++;
    if(add == 1 && f1 == 0) f1++;
    else if((add == 1 || add == 4 || add == 6) && f1 == 1) f1++;
    if(add == 1 && f4 == 0) f4++;
    else if(add == 9 && f4 == 1) f4++;
    else if(add == 9 && f4 == 2) f4++;
    if(add == 1 && f5 == 0) f5++;
    else if(add == 8 && f5 == 1) f5++;
    else if(add == 8 && f5 == 2) f5++;
    if(add == 9 && f6 == 0) f6++;
    else if((add == 1 || add == 8) && f6 == 1) f6++;
    if(add == 9 && f7 == 0) f7++;
    else if(add == 4 && f7 == 1) f7++;
    else if(add == 6 && f7 == 2) f7++;
    else if(add == 0 && f7 == 3) f7++;
    else if(add == 6 && f7 == 4) f7++;
    if(add == 9 && f8 == 0) f8++;
    else if(add == 6 && f8 == 1) f8++;
    else if(add == 4 && f8 == 2) f8++;
    else if(add == 6 && f8 == 3) f8++;
    if(add == 9 && f9 == 0) f9++;
    else if(add == 4 && f9 == 1) f9++;
    else if(add == 6 && f9 == 2) f9++;
    else if(add == 6 && f9 == 3) f9++;
    else if(add == 6 && f9 == 4) f9++;
    else if(add == 6 && f9 == 5) f9++;
    if(add == 9 && f10 == 0) f10++;
    else if(add == 9 && f10 == 1) f10++;
    else if(add == 4 && f10 == 2) f10++;
    if(add == 9 && f11 == 0) f11++;
    else if(add == 4 && f11 == 1) f11++;
    else if(add == 4 && f11 == 2) f11++;
    if(add == 9 && f12 == 0) f12++;
    else if(add == 4 && f12 == 1) f12++;
    else if(add == 0 && f12 == 2) f12++;
    else if(add == 0 && f12 == 3) f12++;
    else if(add == 0 && f12 == 4) f12++;
    else if(add == 0 && f12 == 5) f12++;
    else if(add == 0 && f12 == 6) f12++;
    else if(add == 6 && f12 == 7) f12++;
    if(f0 == 3) return 0;
    if(f1 == 2) return 0;
    if(f4 == 3) return 0;
    if(f5 == 3) return 0;
    if(f6 == 2) return 0;
    if(f7 == 5) return 0;
    if(f8 == 4) return 0;
    if(f9 == 6) return 0;
    if(f10 == 3) return 0;
    if(f11 == 3) return 0;
    if(f12 == 8) return 0;
    return 1;
}

inline int solve(int Max, int now, int fir, int f0, int f1, int f4, int f5, int f6, int f7, int f8, int f9, int f10, int f11, int f12, int f13)
{
    if(now > Max) return 1;
    if(vis[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13])
        return dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13];
    int sum = Max / now;
    bool flag = ((sum % 10) == sum);
    //0 
    int f00 = f0, f01 = f1;
    int f04 = f4, f05 = f5, f06 = f6, f07 = f7;
    int f08 = f8, f09 = f9;
    int f010 = f10, f011 = f11, f012 = f12, f013 = f13;
    if(update(0, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013))
    {
        if(sum % 10 > 0) f013 = 0;
        if(sum % 10 < 0) f013 = 1;
        if(sum % 10 == 0) f013 = min(f13, 2ll);
        if(now == 1000000000000000000) dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13]++;
        else
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] += solve(Max, now * 10, fir + 1, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013),
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] %= mod;
    }
    //1
    f00 = f0, f01 = f1;
    f04 = f4, f05 = f5, f06 = f6, f07 = f7;
    f08 = f8, f09 = f9;
    f010 = f10, f011 = f11, f012 = f12, f013 = f13;
    if(update(1, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013) && (!flag || (f013 == 1 && sum > 1) || ((f013 == 0 || f013 == 2) && sum >= 1)))
    {
        if(sum % 10 > 1) f013 = 0;
        if(sum % 10 < 1) f013 = 1;
        if(sum % 10 == 1) f013 = min(f13, 2ll);
        if(now == 1000000000000000000) dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13]++;
        else
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] += solve(Max, now * 10, fir + 1, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013),
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] %= mod;
    }
    //4
    f00 = f0, f01 = f1;
    f04 = f4, f05 = f5, f06 = f6, f07 = f7;
    f08 = f8, f09 = f9;
    f010 = f10, f011 = f11, f012 = f12, f013 = f13;
    if(update(4, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013) && (!flag || (f013 == 1 && sum > 4) || ((f013 == 0 || f013 == 2) && sum >= 4)))
    {
        int f04, f05;
        if(sum % 10 > 4) f013 = 0;
        if(sum % 10 < 4) f013 = 1;
        if(sum % 10 == 4) f013 = min(f13, 2ll);
        if(now == 1000000000000000000) dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13]++;
        else
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] += solve(Max, now * 10, fir + 1, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013),
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] %= mod;
    }
    //6
    f00 = f0, f01 = f1;
    f04 = f4, f05 = f5, f06 = f6, f07 = f7;
    f08 = f8, f09 = f9;
    f010 = f10, f011 = f11, f012 = f12, f013 = f13;
    if(update(6, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013) && (!flag || (f013 == 1 && sum > 6) || ((f013 == 0 || f013 == 2) && sum >= 6)))
    {
        int f04, f05;
        if(sum % 10 > 6) f013 = 0;
        if(sum % 10 < 6) f013 = 1;
        if(sum % 10 == 6) f013 = min(f13, 2ll);
        if(now == 1000000000000000000) dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13]++;
        else
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] += solve(Max, now * 10, fir + 1, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013),
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] %= mod;
    }
    //8
    f00 = f0, f01 = f1;
    f04 = f4, f05 = f5, f06 = f6, f07 = f7;
    f08 = f8, f09 = f9;
    f010 = f10, f011 = f11, f012 = f12, f013 = f13;
    if(update(8, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013) && (!flag || (f013 == 1 && sum > 8) || ((f013 == 0 || f013 == 2) && sum >= 8)))
    {
        if(sum % 10 > 8) f013 = 0;
        if(sum % 10 < 8) f013 = 1;
        if(sum % 10 == 8) f013 = min(f13, 2ll);
        if(now == 1000000000000000000) dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13]++;
        else
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] += solve(Max, now * 10, fir + 1, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013),
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] %= mod;
    }
    //9
    f00 = f0, f01 = f1;
    f04 = f4, f05 = f5, f06 = f6, f07 = f7;
    f08 = f8, f09 = f9;
    f010 = f10, f011 = f11, f012 = f12, f013 = f13;
    if(update(9, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013) && (!flag || (f013 == 1 && sum > 9) || ((f013 == 0 || f013 == 2) && sum >= 9)))
    {
        if(sum % 10 > 9) f013 = 0;
        if(sum % 10 < 9) f013 = 1;
        if(sum % 10 == 9) f013 = min(f13, 2ll);
        if(now == 1000000000000000000) dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13]++;
        else
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] += solve(Max, now * 10, fir + 1, f00, f01, f04, f05, f06, f07, f08, f09, f010, f011, f012, f013),
            dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] %= mod;
    }
    vis[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13] = 1;
    return dp[fir][f0][f1][f4][f5][f6][f7][f8][f9][f10][f11][f12][f13];
}

inline int calc(int x)
{
    memset(dp, 0, sizeof dp);
    memset(vis, 0, sizeof vis);
    return solve(x, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);
}

signed main()
{
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    int T;
    cin >> T;
    while(T--)
    {
        int l, r;
        cin >> l >> r;
        int ls = calc(l - 1);
        int rs = calc(r);
        cout << rs - ls << endl;
    }
    return 0;
}