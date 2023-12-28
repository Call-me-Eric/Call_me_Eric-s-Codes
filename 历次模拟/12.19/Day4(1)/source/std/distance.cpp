#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin(),(a).end()
#define pw(x) (1LL<<(x))
#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl
using namespace std;
typedef long long ll;
typedef double dbl;
const int INF = 1.01e9;
struct pt {
    int x, y;
    int id;
    pt() {}
    pt(int xx, int yy) : x(xx), y(yy) {}
    pt operator+(pt A) {return pt(x + A.x, y + A.y);}
    pt operator-(pt A) {return pt(x - A.x, y - A.y);}
    int len() {return max(abs(x), abs(y));}
    void read() {scanf("%d%d", &x, &y);}
    bool operator< (const pt &c) const {return x < c.x || (x == c.x && y < c.y);}
};
const int SZ = 60;
const ll BASE = pw(SZ);
struct node;
const ll PP = 1000000007;
struct Hash {
    ll operator() (const pair<pair<int, int>, int> &x) {
        return 1ll * PP * (x.first.second - x.first.first) + x.second;
    }
} hasher;
unordered_map<ll, node*> mp;
const int N = 1 << 14;
const ll Q = 239;
ll P[N];
struct node {
    node *l, *r;
    int mn;
    int len;
    ll hash;
    node() {}
    node(int value) {
        l = r = 0;
        mn = value;
        len = 1;
        hash = value * P[0];
    }
    node(node *_l, node *_r) {
        l = _l;
        r = _r;
        mn = min(l->mn, r->mn);
        len = l->len + r->len;
        hash = l->hash + r->hash * P[l->len];
    }
};
const int NODES = (int)4.5e8 / sizeof(node);
node nodes[NODES];
int cnodes;
node* makeNode(int tl, int tr, int value) {
    auto o = hasher(make_pair(make_pair(tl, tr), value));
    if (!mp.count(o)) {
        if (tl == tr) {mp[o] = new (nodes + cnodes++) node(value);}
        else {
            int tm = (tl + tr) >> 1;
            mp[o] = new (nodes + cnodes++) node(makeNode(tl, tm, value), makeNode(tm + 1, tr, value));
        }
    }
    return mp[o];
}
ll Hash(node *t) {return 1ll * t->len * PP + t->hash;}
ll Hash(node *l, node *r) {
    ll h1 = Hash(l);
    ll h2 = Hash(r);
    return h1 * PP + h2;
}
node* makeNode(node *l, node *r) {
    return new(nodes + cnodes++) node(l, r);
}
int findFirst(node *t, int tl, int tr, int l) {
    if (l > tr) return INF;
    if (tl >= l) if (t->mn == 1) return INF;
    if (tl == tr) return tl;
    int tm = (tl + tr) >> 1;
    int res = findFirst(t->l, tl, tm, l);
    if (res == INF) res = findFirst(t->r, tm + 1, tr, l);
    return res;
}
node* upd(node *t, int tl, int tr, int l, int r, int x) {
    if (l > r) return t;
    if (l == tl && r == tr) return makeNode(tl, tr, x);
    int tm = (tl + tr) >> 1;
    return makeNode(upd(t->l, tl, tm, l, min(r, tm), x), upd(t->r, tm + 1, tr, max(l, tm + 1), r, x));
}
struct fastnum {
    node *t;
    fastnum() {}
    fastnum(int val) {t = makeNode(0, N - 1, val);}
    void add1(int x) {
        int id = findFirst(t, 0, N - 1, x);
        t = upd(t, 0, N - 1, x, id - 1, 0);
        t = upd(t, 0, N - 1, id, id, 1);
    }
    bool operator< (const fastnum &n) const {
        if (t->hash == n.t->hash) return 0;
        int tl = 0, tr = N - 1;
        node *t1 = t, *t2 = n.t;
        while (tl != tr) {
            int tm = (tl + tr) >> 1;
            if (t1->r->hash != t2->r->hash) {
                t1 = t1->r;
                t2 = t2->r;
                tl = tm + 1;
            } else {
                t1 = t1->l;
                t2 = t2->l;
                tr = tm;
            }
        }
        return t1->mn < t2->mn;
    }
};
struct SmartEdge {
    int l, r, id;
    bool operator<(SmartEdge A) {
        if (l != A.l) return l < A.l;
        if (r != A.r) return r < A.r;
        return id < A.id;
    }
};
const int BOUND = 100;
struct SegTree {
    vector<vector<pair<int,int>>> tree;
    vector<SmartEdge> e;
    vector<int> localUse;
    int n;
    SegTree(vector<SmartEdge> ee, int nn) {
        e = ee;
        n = nn;
        if (sz(e) >= BOUND) {
            tree.resize(n * 4);
            localUse.resize(e.size());
            for (int i = 0; i < sz(e); i++)
                add(0, 0, n, min(n, max(0, e[i].l)), min(n, max(0, e[i].r + 1)), e[i].id, i);
        }
    }
    void add(int v, int tl, int tr, int l, int r, int id, int localId) {
        if (r <= tl || tr <= l) return;
        if (l <= tl && tr <= r) {
            tree[v].pb({id, localId});
            return;
        }
        add(v * 2 + 1, tl, (tl + tr) / 2, l, r, id, localId);
        add(v * 2 + 2, (tl + tr) / 2, tr, l, r, id, localId);
    }
    void get(int pos, vector<int>& dst) {
        if (sz(e) >= BOUND) get(0, 0, n, pos, dst);
        else {
            int cur = 0;
            for (int i = 0; i < sz(e); i++)
                if (e[i].l <= pos && pos <= e[i].r) dst.pb(e[i].id);
                else e[cur++] = e[i];
            e.resize(cur);
        }
    }
    void get(int v, int tl, int tr, int pos, vector<int>& dst) {
        for (auto x: tree[v])
            if (localUse[x.S] == 0) {
                localUse[x.S] = 1;
                dst.pb(x.F);
            }
        if (tl + 1 == tr) return;
        if (pos < (tl + tr) / 2) get(v * 2 + 1, tl, (tl + tr) / 2, pos, dst);
        else get(v * 2 + 2, (tl + tr) / 2, tr, pos, dst);
    }
};
void init() {
    P[0] = 1;
    for (int i = 1; i < N; i++) P[i] = P[i - 1] * Q;
}
vector <int> qx, qy;
struct Seg {
    int s;
    Seg *lc, *rc;
} *rt[10005];
Seg *ins(Seg *rt, int l, int r, int x) {
    Seg *ret = new Seg;
    if (rt) {*ret = *rt; ++ret -> s;}
    else {
        ret -> s = 1;
        ret -> lc = ret -> rc = NULL;
    }
    if (l == r) return ret;
    int mid = l + r >> 1;
    if (x <= mid) ret -> lc = ins(ret -> lc, l, mid, x);
    else ret -> rc = ins(ret -> rc, mid + 1, r, x);
    return ret;
}
int sum(Seg *rt, int l, int r, int L, int R) {
    if (!rt || L > R) return 0;
    if (L <= l && r <= R) return rt -> s;
    int mid = l + r >> 1, ret = 0;
    if (L <= mid) ret = sum(rt -> lc, l, mid, L, R);
    if (R > mid) ret += sum(rt -> rc, mid + 1, r, L, R);
    return ret;
}
int qry(int x1, int y1, int x2, int y2) {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    int l = lower_bound(all(qx), x1) - qx.begin(), r = lower_bound(all(qx), x2 + 1) - qx.begin(),
        tl = lower_bound(all(qy), y1) - qy.begin() + 1, tr = lower_bound(all(qy), y2 + 1) - qy.begin();
    return sum(rt[r], 1, qy.size(), tl, tr) - sum(rt[l], 1, qy.size(), tl, tr);
}
int findD(int sx, int sy, int x, int y, int dx, int dy) {
    int l = 0, r = INF, mid, tx, ty;
    while (l + 1 < r) {
        mid = (l + r) / 2;
        tx = x + mid * dx; ty = y + mid * dy;
        if (qry(x + dx, y + dy, tx, ty)) r = mid; else l = mid;
    }
    return r;
}
vector<int> fast(int sx, int sy, vector<pt> p) {
    init();
    int k = p.size();
    vector<vector<int>> e(k);
    for (int i = 0; i < k; i++) p[i].id = i;
    for (int tt = 0; tt < 2; tt++) {
        sort(all(p), [](pt A, pt B) {return A.x < B.x || (A.x == B.x && A.y < B.y);});
        for (int i = 0; i < k;) {
            int j = i;
            for (; i < k && p[i].x == p[j].x; i++);
            for (int t = j + 1; t < i; t++) {
                e[p[t].id].pb(p[t - 1].id);
                e[p[t - 1].id].pb(p[t].id);
            }
        }
        for (int i = 0; i < k; i++) swap(p[i].x, p[i].y);
    }
    sort(all(p), [](pt A, pt B) {return A.id < B.id;});
    vector<pt> dir = {{1,  1}, {1,  -1}, {-1, -1}, {-1, 1}};
    vector<vector<SmartEdge>> row(sx);
    vector<vector<SmartEdge>> col(sy);
    for (int i = 0; i < k; i++) 
        for (int t = 0; t < 4; t++) {
            int best = findD(sx, sy, p[i].x, p[i].y, dir[t].x, dir[t].y);
            if (best == INF) continue;
            int y1 = p[i].y + dir[t].y * best;
            int y2 = p[i].y + dir[t].y;
            if (y1 > y2) swap(y1, y2);
            int x = p[i].x + dir[t].x * best;
            if (0 <= x && x < sx) row[x].pb({y1, y2, i});
            int x1 = p[i].x + dir[t].x * best;
            int x2 = p[i].x + dir[t].x;
            int y = p[i].y + dir[t].y * best;
            if (x1 > x2) swap(x1, x2);
            if (0 <= y && y < sy) col[y].pb({x1, x2, i});
        }
    vector<SegTree> rr;
    vector<SegTree> cc;
    for (int i = 0; i < sx; i++) rr.emplace_back(row[i], sy);
    for (int i = 0; i < sy; i++) cc.emplace_back(col[i], sx);
    vector<fastnum> dist(k);
    vector<int> par(k, -1);
    for (int i = 0; i < k; i++) dist[i] = fastnum(1);
    set<pair<fastnum, int>> q;
    q.insert({fastnum(0), 0});
    dist[0] = fastnum(0);
    while (!q.empty()) {
        int v = q.begin()->S;
        q.erase(q.begin());
        vector<int> go = e[v];
        rr[p[v].x].get(p[v].y, go);
        cc[p[v].y].get(p[v].x, go);
        for (auto u: go) {
            auto tmp = dist[v];
            int len = (p[v] - p[u]).len();
            tmp.add1(len);
            if (tmp < dist[u]) {
                q.erase({dist[u], u});
                dist[u] = tmp;
                par[u] = v;
                q.insert({dist[u], u});
            }
        }
    }
    vector<int> path;
    int v = k - 1;
    for (;v != -1; v = par[v]) path.pb(v);
    return path;
}
int main() {
    freopen("distance.in", "r", stdin);
    freopen("distance.out", "w", stdout);
    int sx, sy, k;
    scanf("%d%d%d", &sx, &sy, &k);
    vector<pt> p(k);
    for (int i = 0; i < k; i++) {
        p[i].read();
        qx.pb(--p[i].x);
        qy.pb(--p[i].y);
    }
    sort(all(qx)); qx.resize(unique(all(qx)) - qx.begin());
    sort(all(qy)); qy.resize(unique(all(qy)) - qy.begin());
    vector<pt> q = p;
    sort(all(q));
    Seg *cur;
    for (int i = 1, j = 0; i <= qx.size(); ++i) {
        cur = rt[i - 1];
        for (; j < q.size() && q[j].x == qx[i - 1]; ++j)
            cur = ins(cur, 1, qy.size(), lower_bound(all(qy), q[j].y) - qy.begin() + 1);
        rt[i] = cur;
    }
    auto path = fast(sx, sy, p);
    reverse(all(path));
    printf("%d\n", sz(path));
    for (auto x: path) printf("%d ", x + 1);
    puts("");
    return 0;
}
