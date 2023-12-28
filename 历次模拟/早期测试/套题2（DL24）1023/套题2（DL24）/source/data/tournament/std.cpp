#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

namespace solve
{
    const int maxn = 1010;

    int a[maxn], n;

    bool e[maxn][maxn];

    vector<vector<int>> solve(vector<int> a)
    {
        if (a.size() == 1)
        {
            vector<vector<int>> res(a[0] + 2, vector<int>(a[0] + 2));
            for (int i = 1; i <= a[0] + 1; i++)
                for (int j = 1; j <= a[0] + 1; j++)
                    if (i != j)
                        res[i][j] = 1;
            return res;
        }
        vector<int> tmp(a.size() - 1);
        for (int i = 0; i < (int)a.size() - 1; i++)
        {
            tmp[i] = a.back() - a[i];
        }
        reverse(tmp.begin(), tmp.end());
        auto o = solve(tmp);
        vector<vector<int>> res(a.back() + 2, vector<int>(a.back() + 2));
        for (int i = 1; i <= tmp.back() + 1; i++)
            for (int j = 1; j <= tmp.back() + 1; j++)
                res[i][j] = o[i][j];
        for (int i = 1; i <= a.back() + 1; i++)
            for (int j = 1; j <= a.back() + 1; j++)
                if (i != j)
                    res[i][j] ^= 1;
        return res;
    }

    void main()
    {
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        auto e = solve(a);
        for (int i = 1; i <= a.back() + 1; i++, cout << endl)
            for (int j = 1; j <= a.back() + 1; j++)
                cout << e[i][j];
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    solve::main();
}