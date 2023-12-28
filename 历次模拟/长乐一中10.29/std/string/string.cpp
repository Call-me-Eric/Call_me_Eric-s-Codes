#include <bits/stdc++.h>

const int N = 300100;
const int inf = 0x3f3f3f3f;

int n;
char s[N];

struct matrix {
    int a[2][2];
    matrix() {memset(a, 0x3f, sizeof(a)); }

    matrix operator * (const matrix &rhs) const {
        matrix C;
        for (int i = 0; i < 2; ++ i)
            for (int j = 0; j < 2; ++ j) {
                for (int k = 0; k < 2; ++ k) {
                    C.a[i][j] = std::min(C.a[i][j], a[i][k] + rhs.a[k][j]);
                }
            }
        return C;
    }
} A, B;

namespace SGT {
    struct node {
        int l, r;
        matrix ans;
    } t[N * 4];

    void push_up(int p) {
        t[p].ans = t[p << 1].ans * t[p << 1 | 1].ans;
    }

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;

        if (l == r) {
            if (s[l] == '0') {
                t[p].ans.a[0][0] = 0, t[p].ans.a[0][1] = 2;
                t[p].ans.a[1][0] = 1, t[p].ans.a[1][1] = 1;
            } else {
                t[p].ans.a[0][0] = 1, t[p].ans.a[0][1] = 1;
                t[p].ans.a[1][0] = 2, t[p].ans.a[1][1] = 0;
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        push_up(p);
    }

    void modify(int p, int pos) {
        if (t[p].l == t[p].r) {
            if (s[pos] == '0') {
                t[p].ans.a[0][0] = 0, t[p].ans.a[0][1] = 2;
                t[p].ans.a[1][0] = 1, t[p].ans.a[1][1] = 1;
            } else {
                t[p].ans.a[0][0] = 1, t[p].ans.a[0][1] = 1;
                t[p].ans.a[1][0] = 2, t[p].ans.a[1][1] = 0;
            }
            return;
        }

        int mid = (t[p].l + t[p].r) >> 1;
        if (pos <= mid) modify(p << 1, pos);
        else modify(p << 1 | 1, pos);
        push_up(p);
    }

    matrix query(int p, int l, int r) {
        if (l <= t[p].l && t[p].r <= r) return t[p].ans;
        int mid = (t[p].l + t[p].r) >> 1;

        if (l <= mid && r > mid)
            return query(p << 1, l, r) * query(p << 1 | 1, l, r);
        if (l <= mid)
            return query(p << 1, l, r);
        return query(p << 1 | 1, l, r);
    }
}

int main() {
    // freopen("string.in", "r", stdin);
    // freopen("string.out", "w", stdout);
    
    scanf("%d", &n);
    scanf("%s", s + 1);

    for (int i = 1; i <= n; ++ i)
        if (i <= n - i + 1) std::swap(s[i], s[n - i + 1]);

    SGT::build(1, 1, n);

    int Q; scanf("%d", &Q);
    while (Q --) {
        int type, l, r;
        scanf("%d%d%d", &type, &l, &r);

        if (type == 1) {
            l = n - l + 1, r = n - r + 1;
            std::swap(l, r);

            A.a[0][0] = 0, A.a[0][1] = inf;
            A.a[1][0] = A.a[1][1] = inf;

            A = A * SGT::query(1, l, r);
            printf("%d\n", std::min(A.a[0][0], A.a[0][1] + 1));
        } else {
            s[n - l + 1] = r + '0';
            SGT::modify(1, n - l + 1);
        }
    }
    return 0;
}