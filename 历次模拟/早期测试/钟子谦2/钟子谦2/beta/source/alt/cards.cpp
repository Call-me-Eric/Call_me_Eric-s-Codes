// Awwawa! Dis cold yis ratten buy Pikachu!
#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define pi pair<int, int>
#define mod 998244353
template <typename T>
bool chkmin(T &a, T b) { return (b < a) ? a = b, 1 : 0; }
template <typename T>
bool chkmax(T &a, T b) { return (b > a) ? a = b, 1 : 0; }
using namespace std;
const int maxn = 5005;
int n;
int a[maxn], b[maxn];
ll dp[maxn][maxn];
int nx[maxn][maxn];

int main() {
    const ll inf = 1e18;
    // mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    freopen("cards.in", "r", stdin);
    freopen("cards.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    for (int i = n + 1; i >= 1; i--)
        for (int atk = 0; atk <= n; atk++) {
            if (i == n + 1) {
                if (atk == 0) dp[i][atk] = 0;
                else dp[i][atk] = -inf;
            }
            else {
                dp[i][atk] = dp[i + 1][atk] + 1ll * a[i] * atk;
                nx[i][atk] = atk;
                if (atk > 0 && chkmax(dp[i][atk], dp[i + 1][atk - 1] + b[i]))
                    nx[i][atk] = atk - 1;
            }
        }
    ll mxa = 0;
    for (int i = 0; i <= n; i++)
        if (dp[1][i] > dp[1][mxa]) mxa = i;
    cout << dp[1][mxa] << endl;
    int i = 1, atk = mxa;
    while (i <= n) {
        if (nx[i][atk] == atk) {
            cout << "1 ";
            i++;
        }
        else {
            cout << "2 ";
            i += 1;
            atk--;
        }
    }
    cout << endl;
    return 0;
}

