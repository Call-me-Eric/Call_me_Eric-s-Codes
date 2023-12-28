#include <bits/stdc++.h>
using namespace std;
struct IO {
    template<class T>
    IO &operator>>(T &x) {
        x = 0;
        int f = 1;
        char c;
        while (!isdigit(c = getchar())) {
            if (c == '-') {
                f = -1;
            }
        }
        do {
            x = x * 10 + c - '0';
        } while (isdigit(c = getchar()));
        x *= f;
        return *this;
    }
    IO &operator>>(char &x) {
        while (!isalpha(x = getchar()));
        return *this;
    }
    template<class T>
    IO &operator<<(T x) {
        static int s[130], t;
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        do {
            s[++t] = x % 10;
        } while (x /= 10);
        while (t) {
            putchar(s[t--] + '0');
        }
        return *this;
    }
    IO &operator<<(char x) {
        putchar(x);
        return *this;
    }
} io;
constexpr int mod = 998244353;
const int add(int a, const int &b) {
    return a += b, a < mod ? a : a - mod;
}
const int sub(int a, const int &b) {
    return a -= b, a >= 0 ? a : a + mod;
}
const int mul(const int &a, const int &b) {
    return 1ll * a * b % mod;
}
const int inv(const int &a, const int &b) {
    return a == 1 ? a : b - 1ll * b * inv(b % a, a) / a;
}
constexpr int N = 705;
int n, q, a[N][N];
int b[N][N], rk, pos[N], x[N];
void guass() {
    for (int i = 1; i <= rk; i++) {
        pos[i] = x[i] = 0;
    }
    rk = 0;
    for (int i = 1; i <= n; i++) {
        pos[i] = ++rk;
        if (!a[rk][i]) {
            for (int j = rk + 1; j <= n; j++) {
                if (a[j][i]) {
                    swap(a[rk], a[j]);
                    break;
                }
            }
        }
        if (!a[rk][i]) {
            pos[i] = --rk;
            break;
        }
        int iv = inv(a[rk][i], mod);
        for (int j = rk + 1; j <= n; j++) {
            int coef = mul(a[j][i], iv);
            for (int k = i; k <= n + 1; k++) {
                a[j][k] = sub(a[j][k], mul(a[rk][k], coef));
            }
        }
    }
    for (int i = rk + 1; i <= n; i++) {
        if (a[i][n + 1]) {
            puts("No");
            return;
        }
    }
    if (rk < n) {
        puts("Many");
        return;
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            a[i][n + 1] = sub(a[i][n + 1], mul(a[i][j], x[j]));
        }
        x[i] = mul(a[i][n + 1], inv(a[i][i], mod));
    }
    for (int i = 1; i <= n; i++) {
        io << x[i] << ' ';
    }
    io << '\n';
}
void work() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            b[i][j] = a[i][j];
        }
    }
    guass();
    swap(a, b);
}
int main() {
    io >> n >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            io >> a[i][j];
        }
    }
    work();
    while (q--) {
        int z;
        io >> z;
        for (int i = 1; i <= n + 1; i++) {
            io >> a[z][i];
        }
        work();
    }
    return 0;
}