#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
constexpr int N = 250, M = 31130 * 2;
int R, G, B, n, m, U[M], V[M], C[M], fa[N], up[N], dep[N];
vector<int> id[4], e[N];
bool vis[N], tag[M];
int to_int(char c) {
    if (c == 'r') {
        return 1;
    } else if (c == 'g') {
        return 2;
    } else {
        return 3;
    }
}
void dfs(int u) {
    for (int i : e[u]) {
        int v = V[i];
        if (!vis[v]) {
            int I = i <= m ? i : i - m;
            fa[v] = u;
            up[v] = I;
            dep[v] = dep[u] + 1;
            vis[v] = 1;
            tag[I] = 1;
            dfs(v);            
        }
    }
}
// mt19937 rd(random_device{}());
mt19937 rd(1);
int rand(int l, int r) {
    uniform_int_distribution<> gen(l, r);
    return gen(rd);
}
int main() {
    // freopen("rgb.in", "r", stdin);
    // freopen("rgb.out", "w", stdout);
    auto st = steady_clock::now();
    cin >> R >> G >> B >> m;
    n = R + G + B + 1;
    for (int i = 1; i <= m; i++) {
        char c;
        cin >> U[i] >> V[i] >> c;
        C[i] = to_int(c);
    }
    for (int i = 1; i <= m; i++) {
        e[U[i]].push_back(i);
        e[V[i]].push_back(i + m);
        U[i + m] = V[i];
        V[i + m] = U[i];
    }
    vis[1] = 1;
    dfs(1);
    vector<int> num(4); // 选中的颜色数
    for (int i = 1; i <= m; i++) {
        if (tag[i]) {
            num[C[i]]++;
        } else {
            id[C[i]].push_back(i); // 没选中的边
        }
    }
    auto check = [&]() -> bool {
        auto ed = steady_clock::now();
        float tim = duration<float, milli>(ed - st).count();
        return tim <= 1950;
    };
    vector<int> tot{0, R, G, B};
    while ((num[1] < R || num[2] < G || num[3] < B) && check()) {
        int o;
        do {
            o = rand(1, 3);
        } while (num[o] >= tot[o]);
        int sz = id[o].size();
        if (sz == 0 || (num[1] < R && num[2] < G && num[3] < B)) {
            cout << "NO\n";
            return 0;
        }
        int pos = rd() % sz;
        int t = id[o][pos];
        int x = U[t], y = V[t];
        if (dep[x] < dep[y]) {
            swap(x, y);
        }
        int tmp = 0;
        auto update = [&](int i) {
            if (!i) return;
            if (num[C[i]] > tot[C[i]]) {
                tmp = i;
            }
            return;
        };
        while (dep[fa[x]] >= dep[y] && !tmp) {
            update(up[x]);
            x = fa[x];
        }
        if (x != y) {
            while (fa[x] != fa[y] && !tmp) {
                update(x);
                update(y);
                x = fa[x];
                y = fa[y];
            }
            update(up[x]);
        }
        if (tmp) {
            tag[t] = 1;
            tag[tmp] = 0;
            num[o]++;
            num[C[tmp]]--;
            id[o].erase(id[o].begin() + pos);
            id[C[tmp]].push_back(tmp);
        }
    }
    if (num[1] == R && num[2] == G && num[3] == B) {
        cout << "YES\n";
        for (int i = 1; i <= m; i++) {
            cout << tag[i];
        }
        cout << "\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}