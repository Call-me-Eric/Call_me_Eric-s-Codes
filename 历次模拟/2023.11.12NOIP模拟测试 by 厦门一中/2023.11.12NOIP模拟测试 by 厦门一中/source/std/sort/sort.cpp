#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 5e6 + 10;
int n, ans;
int a[maxn];
int f[maxn], g[maxn];
int s[maxn], top;
signed main() {
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        while (top && a[s[top]] <= a[i]) --top;
        f[i] = i - s[top];
        s[++top] = i;
    }
    top = 0;
    for (int i = n; i >= 1; i--) {
        while (top && a[s[top]] >= a[i]) --top;
        g[i] = (!top ? n + 1 : s[top]) - i;
        s[++top] = i;
    }
    for (int i = 1; i <= n; i++) ans += i * (n - i + 1) - f[i] * g[i];
    cout << ans << endl;
    return 0;

}
