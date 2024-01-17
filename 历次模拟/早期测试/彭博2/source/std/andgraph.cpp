#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }
    while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 1 << 20, INF = 0x3f3f3f3f;

int a[N], mn[N], popc[N], dis[20][20], res[20][N];
int n, m, q;

inline int lowbit(int x) { return x & -x; }

int main() {
	freopen("andgraph.in","r",stdin);
	freopen("andgraph.out","w",stdout);

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    memset(mn, 0x3f, sizeof(mn));
    cin>>n>>m>>q;
    for (int i = 1; i <= n; i++) cin>>a[i], mn[a[i]] = a[i];
    for (int i = 1; i < N; i++) popc[i] = popc[i ^ lowbit(i)] + 1;
    for (int i = N - 1; i >= 1; i--) {
        if (popc[i] <= 2) continue;
        int a = lowbit(i), b = lowbit(i ^ a);
        mn[i ^ a] = min(mn[i ^ a], mn[i]);
        mn[i ^ b] = min(mn[i ^ b], mn[i]);
        mn[a ^ b] = min(mn[a ^ b], mn[i]);
    }
    for (int i = 0; i < 20; i++) {
        for (int j = i + 1; j < 20; j++) {
            dis[i][j] = dis[j][i] = mn[(1 << i) ^ (1 << j)];
        }
    }
    for (int k = 0; k < 20; k++) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) res[i][1 << j] = dis[i][j];
        for (int j = 1; j < N; j++) {
            if (popc[j] <= 1) continue;
            int a = lowbit(j);
            res[i][j] = min(res[i][j ^ a], res[i][a]);
        }
    }
    int cnt=0;
    while (q--) {
        int s, t;
        cin>>s>>t;
        s = a[s]; t = a[t];
        int ans = INF;
        for (int i = 0; i < 20; i++) {
            if ((s >> i) & 1) {
                ans = min(ans, res[i][t] * 2 + s + t);
            }
        }
        if (ans == INF) ans = -1;
        if( ans == s + t ) cnt++;
        cout<<ans<<'\n';
    }
    cerr<<cnt<<endl;
    return 0;
}
