#include <bits/stdc++.h>
using namespace std;
vector<int> a, b;
int dfs(int x) {
    if (x == 0) {
        return a == b;
    }
    int n = a.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || a[i - 1] >= a[i] + 1) {
            a[i]++;
            ans += dfs(x - 1);
            a[i]--;
        }
        if (i == n - 1 || a[i] - 1 >= a[i + 1]) {
            a[i]--;
            bool flag = 0;
            if (a[i] == 0) {
                a.pop_back();
                flag = 1;
            }
            ans += dfs(x - 1);
            if (flag) {
                a.push_back(0);
            }
            a[i]++;
        }
    }
    a.push_back(1);
    ans += dfs(x - 1);
    a.pop_back();
    return ans;
}
int main() {
    freopen("young.in", "r", stdin);
    freopen("young.out", "w", stdout);
    int n;
    cin >> n;
    a.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    b.assign(m, 0);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        cout << dfs(k) << "\n";
    }
    return 0;
}