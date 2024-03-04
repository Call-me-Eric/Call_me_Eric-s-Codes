#include <bits/stdc++.h>
#define LL __int128_t
using namespace std;
const LL INF = 4e18;
const int N = 1e5 + 100;

LL gcd(LL x, LL y) { return x == 0 ? y : gcd(y % x, x); }

struct P {
    LL x, y;
    LL len() { return x * x + y * y; }
    P(LL xx = 0, LL yy = 0) {
        x = xx;
        y = yy;
    }
};
P operator-(P x, P y) { return P(x.x - y.x, x.y - y.y); }
P operator+(P x, P y) { return P(x.x + y.x, x.y + y.y); }
LL operator*(P x, P y) { return x.x * y.y - x.y * y.x; }

bool cmp1(P x, P y) { return x.y < y.y || (x.y == y.y && x.x < y.x); }
bool cmp2(P x, P y) { return x * y > 0 || (x * y == 0 && x.len() < y.len()); }
void Convex(P* A, int& n) {
    sort(A + 1, A + 1 + n, cmp1);
    // cout<<"x"<<endl;
    // for(int i=1;i<=n;++i) cout<<A[i].x<<" "<<A[i].y<<endl;
    P O = A[1];
    for (int i = 1; i <= n; ++i) {
        A[i] = A[i] - O;
    }
    sort(A + 2, A + 1 + n, cmp2);
    int tp = 1;
    for (int i = 2; i <= n; ++i) {
        while (tp >= 2 && ((A[i] - A[tp - 1]) * (A[tp] - A[tp - 1]) >= 0)) --tp;
        A[++tp] = A[i];
    }
    n = tp;
    for (int i = 1; i <= n; ++i) A[i] = A[i] + O;
    return;
}

int tot;
int n, m, Q;
P D[N]; 
int init(P E) {
    if (E * D[2] > 0 || D[tot] * E > 0) return 0;
    if (E * D[2] == 0) return E.len() <= D[2].len();
    if (E * D[tot] == 0) return E.len() <= D[tot].len();
    LL ps = lower_bound(D + 1, D + tot + 1, E, cmp2) - D - 1;
    return (E - D[ps]) * (D[ps % tot + 1] - D[ps]) <= 0;
}

struct Query {
    LL x, y, z;
} query[N];

void MAIN() {
    int cnt = 4;
    for (int i = 1; i <= cnt; ++i) {
        long long x, y, z;
        cin >> x >> y >> z;
        query[i].x = x;
        query[i].y = y;
        query[i].z = z;
    }

    if (query[4].x + query[4].y + query[4].z == 0) {
        cout << "YES\n";
        return;
    }

    LL S = query[4].x + query[4].y + query[4].z;
    for (int i = 1; i <= 3; ++i) {
        LL tmp = query[i].x + query[i].y + query[i].z;
        LL g = gcd(S, tmp);
        if (tmp == 0) continue;
        S = S / g * tmp;
    }
    for (int i = 1; i <= 4; ++i) {
        LL tmp = query[i].x + query[i].y + query[i].z;
        if (tmp == 0) continue;
        LL g = S / tmp;
        query[i].x *= g;
        query[i].y *= g;
        query[i].z *= g;
    }
    // for (int i = 1; i <= 4; ++i) {
    //     cout << query[i].x << " " << query[i].y << " " << query[i].z << endl;
    // }
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 2; ++j) {
            LL tmp = query[j].x + query[j].y + query[j].z;
            if (tmp == 0) swap(query[j], query[j + 1]);
        }
    }

    n = 3;
    while (query[n].x + query[n].y + query[n].z == 0) {
        n--;
    }

    if (n == 0) {
        cout << "NO\n";
        return;
    }
    if (n == 1) {
        if (query[1].x == query[4].x && query[1].y == query[4].y &&
            query[1].z == query[4].z) {
            cout << "YES\n";
            return;
        } else {
            cout << "NO\n";
            return;
        }
    }

    for (int i = 1; i <= n; ++i) {
        D[i].x = query[i].x;
        D[i].y = query[i].y;
    }

    Convex(D, n);
    tot = n;

    // for (int i = 1; i <= n; ++i) {
    //     cout << D[i].x << " " << D[i].y << endl;
    // }

    P tmp = P(query[4].x, query[4].y);
    P O = D[1];
    D[n + 1] = D[1];
    for (int i = 1; i <= n + 1; ++i) {
        D[i] = D[i] - O;
    }
    // for (int i = 1; i <= n; ++i) {
    //     cout << D[i].x << " " << D[i].y << endl;
    // }
    tmp = tmp - O;
    // cout << tmp.x << " " << tmp.y << endl;
    if (init(tmp)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
	freopen("sumeru.in", "r", stdin);
	freopen("sumeru.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    int ttt = 1;
    cin >> ttt;
    for (int i = 1; i <= ttt; ++i) {
        MAIN();
    }
    return 0;
}
/*


*/
