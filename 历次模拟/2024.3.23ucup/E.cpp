#include <bits/stdc++.h>
using namespace std;

const int N = 1145;
int in[N], out[N];
int n, x[N * 2];
int r[N * 2];
int col[N * 2];
int Find(int x) { return r[x] == x ? x : r[x] = Find(r[x]); }
void merge(int x, int y) { r[Find(x)] = Find(y); }
vector <int> s1, s2;
char ans[N];

signed main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n * 2; i = i + 1)
    {
        cin >> x[i];
        if(x[i] > 0)
            in[x[i]] = i;
        else
            out[-x[i]] = i;
        r[i] = i;
    }
    for(int i = 1; i <= n; i = i + 1)
        for(int j = 1; j <= n; j = j + 1)
        {
            if(i == j)
                continue;
            if(in[i] < in[j] && out[i] < out[j] && out[i] > in[j])
                merge(i, j + n),
                merge(i + n, j);
        }
    for(int i = 1; i <= n; i = i + 1)
        if(Find(i) == Find(i + n))
        {
            cout << "*\n";
            return 0;
        }
    for(int i = 1;i <= n;i++){
        int x = col[Find(i)], y = col[Find(i + n)];
    }
    for(int i = 1; i <= n * 2; i = i + 1)
    {
        // cout << x[i] << " ! \n";
        if(x[i] < 0)
        {
            if(s1.back() == -x[i])
                s1.pop_back();
            else
                s2.pop_back();
            continue;
        }
        bool f = 1;
        for(auto j : s1)
            if(Find(j) == Find(x[i] + n) || Find(j + n) == Find(x[i]))
            {
                f = 0;
                break;
            }
        if(f)
            ans[x[i]] = 'G',
            s1.push_back(x[i]);
        else
            ans[x[i]] = 'S',
            s2.push_back(x[i]);
        // cout << x[i] << " " << ans[x[i]] << " ?\n";
    }
    for(int i = 1; i <= n; i = i + 1)
        cout << ans[i];
    cout << "\n";
    return 0;
}