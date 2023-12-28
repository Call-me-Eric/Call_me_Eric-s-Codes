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

const int N = 5e5 + 5;

int cnt[N];
int T, n;

int main() {
	freopen("mexor.in","r",stdin);
	freopen("mexor.out","w",stdout);

    T = 1;
    while (T--) {
        read(n);
        memset(cnt, 0, (n + 1) * 4);
        for (int i = 1; i <= n; i++) {
            int a; read(a);
            if (a > n) continue;
            ++cnt[a];
        }
        for (int i = 1; i <= n; i++) cnt[i] = min(cnt[i], cnt[i - 1]);
        int ans = 0, now = 1;
        for (int i = n; i >= 1; i--) {
            if (cnt[i - 1] >= now && (ans & i) == 0) {
                ans ^= i; ++now;
            }
        }
        print(ans, '\n');
    }
    return 0;
}
