#include <bits/stdc++.h>
using namespace std;
int n, m, fa[500001], maxdep[500001], dep[500001], tot, rt[500001];
long long w[500001], l[500001], c[500001];
vector<int> son[500001];
bool vis[500001];
struct node {
    int to;
    long long c;
};
vector<node> bian[500001];
struct tree {
    int son[2];
    long long MAX, add, cover;
} tr[40000001];
queue<int> q;
inline void pushdown(int k) {
    if (tr[k].cover == -1 && tr[k].add == 0)
        return;
    if (!tr[k].son[0])
        tr[k].son[0] = q.front(), q.pop(), tr[tr[k].son[0]].cover = -1,
        tr[tr[k].son[0]].add = tr[tr[k].son[0]].MAX = 0;
    if (!tr[k].son[1])
        tr[k].son[1] = q.front(), q.pop(), tr[tr[k].son[1]].cover = -1,
        tr[tr[k].son[1]].add = tr[tr[k].son[1]].MAX = 0;
    if (tr[k].cover != -1) {
        if (tr[k].son[0])
            tr[tr[k].son[0]].cover = tr[tr[k].son[0]].MAX = tr[k].cover, tr[tr[k].son[0]].add = 0;
        if (tr[k].son[1])
            tr[tr[k].son[1]].cover = tr[tr[k].son[1]].MAX = tr[k].cover, tr[tr[k].son[1]].add = 0;
        tr[k].cover = -1;
        // if(op)cout<<114514<<tr[tr[k].son[0]].cover<<endl;
    }
    if (tr[k].add) {
        if (tr[k].son[0]) {
            tr[tr[k].son[0]].MAX += tr[k].add;
            if (tr[tr[k].son[0]].cover != -1)
                tr[tr[k].son[0]].cover += tr[k].add;
            else
                tr[tr[k].son[0]].add += tr[k].add;
        }
        if (tr[k].son[1]) {
            tr[tr[k].son[1]].MAX += tr[k].add;
            if (tr[tr[k].son[1]].cover != -1)
                tr[tr[k].son[1]].cover += tr[k].add;
            else
                tr[tr[k].son[1]].add += tr[k].add;
        }
        tr[k].add = 0;
    }
}
inline int merge(int x, int y, int l = 0, int r = n + 1) {
    if (!x || !y)
        return x + y;
    if (l == r) {
        tr[x].MAX += tr[y].MAX;
        return x;
    }
    if (tr[y].cover != -1) {
        if (tr[x].cover == -1)
            tr[x].add += tr[y].cover;
        else
            tr[x].cover += tr[y].cover;
        tr[y].cover = -1;
        q.push(y);
        return x;
    } else {
        if (tr[x].cover == -1)
            tr[x].add += tr[y].add;
        else
            tr[x].cover += tr[y].add;
        tr[y].add = 0;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    tr[x].son[0] = merge(tr[x].son[0], tr[y].son[0], l, mid),
    tr[x].son[1] = merge(tr[x].son[1], tr[y].son[1], mid + 1, r);
    q.push(y);
    return x;
}
inline long long query(int k, int l, int r, int x) {
    // if(op)cout<<k<<' '<<l<<' '<<r<<' '<<tr[k].cover<<' '<<tr[k].MAX<<' '<<tr[k].add<<endl;
    if (l == r)
        return tr[k].MAX;
    pushdown(k);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return query(tr[k].son[0], l, mid, x);
    return query(tr[k].son[1], mid + 1, r, x);
}
inline void cover(int &k, int l, int r, int x, int y, long long v) {
    if (!k) {
        k = q.front();
        q.pop();
        tr[k].cover = -1, tr[k].MAX = tr[k].add = 0;
    }
    if (l >= x && r <= y) {
        tr[k].cover = tr[k].MAX = v;
        return;
    }
    pushdown(k);
    int mid = (l + r) >> 1;
    if (x <= mid)
        cover(tr[k].son[0], l, mid, x, y, v);
    if (y >= mid + 1)
        cover(tr[k].son[1], mid + 1, r, x, y, v);
    tr[k].MAX = max(tr[tr[k].son[0]].MAX, tr[tr[k].son[1]].MAX);
}
inline int read() {
    int x = 0;
    char c;
    while (c = getchar())
        if (c >= '0' && c <= '9')
            break;
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    return x;
}
inline void dfs(int x) {
    dep[x] = dep[fa[x]] + 1;
    vis[x] = 1;
    for (int i = 0; i < bian[x].size(); ++i) {
        int y = bian[x][i].to;
        if (vis[y] && l[x] - l[y] + bian[x][i].c < 0)
            maxdep[x] = max(maxdep[x], dep[y]);
    }
    for (int i = 0; i < son[x].size(); ++i) {
        int y = son[x][i];
        l[y] += l[x];
        dfs(y);
    }
    vis[x] = 0;
}
inline void dp(int x) {
    if (!maxdep[x]) {
        long long sum = 0;
        for (int i = 0; i < son[x].size(); ++i) {
            int y = son[x][i];
            dp(y);
            sum += query(rt[y], 0, n + 1, dep[x] - 1);
            // if(x==5&&i==1)cout<<query(rt[y],0,n+1,0)<<endl;
            rt[x] = merge(rt[x], rt[y]);
            // if(x==5)cout<<query(rt[x],0,n+1,0)<<endl;
        }
        sum += w[x];
        if (x != n) {
            if (query(rt[x], 0, n + 1, 0) > sum) {
                int l = 0, r = dep[x] - 1;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (query(rt[x], 0, n + 1, mid) > sum)
                        l = mid;
                    else
                        r = mid - 1;
                }
                cover(rt[x], 0, n + 1, 0, l, sum);
            }
        }
    } else {
        if (son[x].empty()) {
            cover(rt[x], 0, n + 1, 0, maxdep[x] - 1, w[x]);
            cover(rt[x], 0, n + 1, maxdep[x], dep[x] - 1, 0);
            // cout<<x<<endl;
            // for(int i=0;i<dep[x];++i)f[x][i]=query(rt[x],0,n+1,i);
            // cout<<endl;
            return;
        }
        long long sum = 0;
        for (int i = 0; i < son[x].size(); ++i) {
            int y = son[x][i];
            dp(y);
            sum += query(rt[y], 0, n + 1, dep[x] - 1);
            rt[x] = merge(rt[x], rt[y]);
        }
        cover(rt[x], 0, n + 1, 0, maxdep[x] - 1, 10000000000000);
        sum += w[x];
        if (x != n) {
            if (query(rt[x], 0, n + 1, 0) > sum) {
                int l = 0, r = dep[x] - 1;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (query(rt[x], 0, n + 1, mid) > sum)
                        l = mid;
                    else
                        r = mid - 1;
                }
                cover(rt[x], 0, n + 1, 0, l, sum);
            }
        }
    }
    // for(int i=0;i<dep[x];++i)f[x][i]=query(rt[x],0,n+1,i);
}
int main() {
    freopen("envelope.in", "r", stdin);
    freopen("envelope.out", "w", stdout);
    for (int i = 1; i <= 40000000; ++i) q.push(i);
    n = read(), m = read();
    for (int i = 0; i < n; ++i) {
        fa[i] = read(), l[i] = -read(), w[i] = read();
        son[fa[i]].push_back(i);
    }
    int x, y, c;
    for (int i = 1; i <= m; ++i) {
        x = read(), y = read(), c = read();
        bian[x - 1].push_back((node){ y, c });
    }
    dfs(n);
    dp(n);
    cout << query(rt[n], 0, n + 1, 0);
}
