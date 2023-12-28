#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m, K;
const int maxn = 801;
short f[maxn][maxn][11][11][2];  // f[0] = max,f[1] = min
int sum[maxn][maxn];
int logg[maxn];
signed main() {
    n = read();
    m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            f[i][j][0][0][0] = f[i][j][0][0][1] = sum[i][j] = read();
            sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
        }
    logg[0] = -1;
    for (int i = 1, len = max(n, m); i <= len; i++) logg[i] = logg[i >> 1] + 1;
    for (int k = 0; (1 << k) <= n; k++)
        for (int l = 0; (1 << l) <= m; l++)
            if (l || k)
                for (int i = 1; i + (1 << k) - 1 <= n; i++)
                    for (int j = 1; j + (1 << l) - 1 <= m; j++) {
                        if (k)
                            f[i][j][k][l][0] = max(f[i][j][k - 1][l][0], f[i + (1 << k - 1)][j][k - 1][l][0]);
                        else
                            f[i][j][k][l][0] = max(f[i][j][k][l - 1][0], f[i][j + (1 << l - 1)][k][l - 1][0]);
                        if (k)
                            f[i][j][k][l][1] = min(f[i][j][k - 1][l][1], f[i + (1 << k - 1)][j][k - 1][l][1]);
                        else
                            f[i][j][k][l][1] = min(f[i][j][k][l - 1][1], f[i][j + (1 << l - 1)][k][l - 1][1]);
                    }
    K = read();
    char opt[5];
    int x1, yy, x2, y2;
    for (int i = 1; i <= K; i++) {
        scanf("%s", opt);
        x1 = read() + 1;
        yy = read() + 1;
        x2 = read() + 1, y2 = read() + 1;
        int k1 = logg[x2 - x1 + 1], k2 = logg[y2 - yy + 1];
        if (opt[0] == 'S')
            cout << sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][yy - 1] + sum[x1 - 1][yy - 1] << endl;
        else if (opt[1] == 'I')
            cout << min(min(f[x1][yy][k1][k2][1], f[x2 - (1 << k1) + 1][yy][k1][k2][1]),
                        min(f[x1][y2 - (1 << k2) + 1][k1][k2][1],
                            f[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2][1]))
                 << endl;
        else
            cout << max(max(f[x1][yy][k1][k2][0], f[x2 - (1 << k1) + 1][yy][k1][k2][0]),
                        max(f[x1][y2 - (1 << k2) + 1][k1][k2][0],
                            f[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2][0]))
                 << endl;
    }
    return 0;
}