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
int add(int a, int b) {
    return a += b, a < mod ? a : a - mod;
}
const int sub(const int &a, const int &b) {
    return a >= b ? a - b : a - b + mod;
}
const int mul(const int &a, const int &b) {
    return 1ull * a * b % mod;
}
const int inv(const int &a, const int &b) {
    return a == 1 ? a : b - 1ull * b * inv(b % a, a) / a;
}
constexpr int N = 705;
int n, q, tot;
int a[N][N], tag, b[N * 2][N], c[N];
int top, stk[12][N][N];
int last[N][2], x[N];
vector<int> id[N * 4];
void insert(int *b) {
    if (tag) return;
    for (int i = 1; i <= n + 1; i++) {
        c[i] = b[i];
    }
    for (int i = 1; i <= n; i++) {
        if (!c[i]) continue;
        if (a[i][i]) {
            int coef = mul(c[i], inv(a[i][i], mod));
            for (int j = i; j <= n + 1; j++) {
                c[j] = sub(c[j], mul(a[i][j], coef));
            }
        } else {
            for (int j = i; j <= n + 1; j++) {
                a[i][j] = c[j];
            }
            return;
        }
    }
    if (c[n + 1]) {
        tag = 1;
    }
}
void push() {
    top++;
    stk[top][0][0] = tag;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            stk[top][i][j] = a[i][j];
        }
    }
}
void pop() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            a[i][j] = stk[top][i][j];
        }
    }
    tag = stk[top][0][0];
    top--;
}
void print() {
    if (tag) {
        puts("No");
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!a[i][i]) {
            puts("Many");
            return;
        }
    }
    for (int i = n; i >= 1; i--) {
        int v = a[i][n + 1];
        for (int j = i + 1; j <= n; j++) {
            v = sub(v, mul(a[i][j], x[j]));
        }
        x[i] = mul(v, inv(a[i][i], mod));
    }
    for (int i = 1; i <= n; i++) {
        io << x[i] << ' ';
    }
    io << '\n';
}
void insert(int x, int y, int z, int p, int l, int r) {
    if (x <= l && r <= y) {
        id[p].push_back(z);
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        insert(x, y, z, p << 1, l, mid);
    }
    if (mid < y) {
        insert(x, y, z, p << 1 | 1, mid + 1, r);
    }
}
void dfs(int p, int l, int r) {
    push();
    for (int i : id[p]) {
        insert(b[i]);
    }
    if (l != r) {
        int mid = (l + r) >> 1;
        dfs(p << 1, l, mid);
        dfs(p << 1 | 1, mid + 1, r);
    } else {
        print();
    }
    pop();
}
int main() {
    io >> n >> q;
    for (int i = 1; i <= n; i++) {
        last[i][0] = 0;
        last[i][1] = ++tot;
        for (int j = 1; j <= n + 1; j++) {
            io >> b[tot][j];
        }
    }
    for (int i = 1; i <= q; i++) {
        int z;
        io >> z;
        tot++;
        for (int j = 1; j <= n + 1; j++) {
            io >> b[tot][j];
        }
        insert(last[z][0], i - 1, last[z][1], 1, 0, q);
        last[z][0] = i;
        last[z][1] = tot;
    }
    for (int i = 1; i <= n; i++) {
        insert(last[i][0], q, last[i][1], 1, 0, q);
    }
    dfs(1, 0, q);
    return 0;
}