#include <bits/stdc++.h>
using namespace std;
constexpr int N = 250, M = 31130;
int R, G, B, n, m, U[M], V[M], C[M], pa[N], cnt;
int to_int(char c) {
    if (c == 'r') {
        return 1;
    } else if (c == 'g') {
        return 2;
    } else {
        return 3;
    }
}
char to_char(int x) {
    if (x == 1) {
        return 'r';
    } else if (x == 2) {
        return 'g';
    } else {
        return 'b';
    }
}
int find(int x) {
    if (x == pa[x]) {
        return x;
    } else {
        return pa[x] = find(pa[x]);
    }
}
bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return 0;
    }
    cnt--;
    pa[x] = y;
    return 1;
}
int main() {
    // freopen("rgb.in", "r", stdin);
    // freopen("rgb.out", "w", stdout);
    cin >> R >> G >> B >> m;
    n = R + G + B + 1;
    for (int i = 1; i <= m; i++) {
        char c;
        cin >> U[i] >> V[i] >> c;
        C[i] = to_int(c);
    }
    // if (n <= 5) {
        for (int s = 0; s < 1 << m; s++) {
            if (__builtin_popcount(s) != n - 1) {
                continue;
            }
            for (int i = 1; i <= n; i++) {
                pa[i] = i;
            }
            cnt = n;
            vector<int> num(4);
            for (int i = 1; i <= m; i++) {
                if (s >> (i - 1) & 1) {
                    merge(U[i], V[i]);
                    num[C[i]]++;
                }
            }
            if (num[1] == R && num[2] == G && num[3] == B && cnt == 1) {
                cout << "YES\n";
                // for (int i = 1; i <= m; i++) {
                //     cout << (s >> (i - 1) & 1);
                // }
                // cout << "\n";
                return 0;
            }
        }
    // }
    cout << "NO\n";
    return 0;
}