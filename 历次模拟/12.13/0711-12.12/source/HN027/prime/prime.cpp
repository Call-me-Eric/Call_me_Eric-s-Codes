#include <bits/stdc++.h>
using namespace std;
int read()
{
    int sum = 0, ne = 1;
    char ch = getchar();
    for (; (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
    if (ch == '-')
        ne = -1, ch = getchar();
    for (; ch >= '0' && ch <= '9'; ch = getchar())
        sum = (sum << 3) + (sum << 1) + (ch ^ 48);
    return sum * ne;
}
const int n = 100000;
const int ans[] = {2, 3, 5, 7, 11, 19, 41, 61, 89, 409, 449, 499, 881, 991, 6469, 6949, 9001, 9049, 9649, 9949, 60649, 666649, 946669, 60000049, 66000049, 66600049};
bitset<n + 5> bt;
int sum[n + 5];
int main()
{
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    // int l = read(), r = read();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            string y = to_string(i), x = to_string(ans[j]);
            int now = 0, flag = 0;
            for (int k = 0; k < x.size(); k++)
            {
                while (now < y.size() && y[now] != x[k]) now++;
                if (now >= y.size())
                {
                    flag = 1;
                    break;
                }
                now++;
            }
            if (!flag)
            {
                bt[i] = 1;
                break;
            }
        }
        sum[i] = sum[i - 1] + (!bt[i]);
    }
    int t = read();
    while (t--)
    {
        int l = read(), r = read();
        printf("%d\n", sum[r] - sum[l - 1]);
    }
    // for (int i = 0; i < 26; i++) printf("%d ", sum[i]);
    // flag[1] = 1;
    // for (int i = 2; i <= n; i++)
    // {
    //     if (!flag[i]) v.emplace_back(i);
    //     for (int j : v)
    //     {
    //         if (1ll * i * j > n) break;
    //         flag[i * j] = 1;
    //         if (i % j == 0) break;
    //     }
    // }
    // vector<int> ans2;
    // // for (int i = 0; i < 26; i++) ans2.emplace_back(ans[i]);
    // for (int i = 0; i < v.size(); i++)
    // {
    //     // if (v[i] <= 100000000) continue;
    //     int sum = 0;
    //     for (int j : ans2)
    //     {
    //         string y = to_string(v[i]), x = to_string(j);
    //         int now = 0, flag = 0;
    //         for (int k = 0; k < x.size(); k++)
    //         {
    //             while (now < y.size() && y[now] != x[k]) now++;
    //             if (now >= y.size())
    //             {
    //                 flag = 1;
    //                 break;
    //             }
    //             now++;
    //         }
    //         if (!flag)
    //         {
    //             sum = 1;
    //             break;
    //         }
    //     }
    //     if (!sum) ans2.emplace_back(v[i]);
    // }
    // for (int i : ans2) printf("%d ", i);
	return 0;
}
