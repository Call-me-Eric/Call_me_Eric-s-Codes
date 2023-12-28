#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int MAXN = 1000010;
int N, K;
int main() {
    freopen("ur.in", "r", stdin);
    freopen("ur.out", "w", stdout);
    N = read(), K = read();
    int x = (N == K);
    for (int i = 1; i <= N; i++)
        printf("%d", x);
}
