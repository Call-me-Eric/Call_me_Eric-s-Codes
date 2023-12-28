#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template<int MOD>
struct ModInt {
  int x;
 
  ModInt() : x(0) {}
  ModInt(i64 y) : x(y >= 0 ? y % MOD : (MOD - (-y) % MOD) % MOD) {}

  inline int inc(const int &x) {
    return x >= MOD ? x - MOD : x;
  }
  inline int dec(const int &x) {
    return x < 0 ? x + MOD : x;
  }
 
  ModInt &operator+= (const ModInt &p) {
    x = inc(x + p.x);
    return *this;
  } 
  ModInt &operator-= (const ModInt &p) {
    x = dec(x - p.x);
    return *this;
  }
 
  ModInt &operator*= (const ModInt &p) {
    x = (int)(1ll * x * p.x % MOD);
    return *this;
  }
  ModInt &operator/= (const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }
 
  ModInt operator-() const { return ModInt(-x); } 

  friend ModInt operator + (const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) += rhs;
  }
  friend ModInt operator - (const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) -= rhs;
  }
  friend ModInt operator * (const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) *= rhs;
  }
  friend ModInt operator / (const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) /= rhs;
  }
 
  bool operator == (const ModInt &p) const { return x == p.x; } 
  bool operator != (const ModInt &p) const { return x != p.x; }
 
  ModInt inverse() const {
    int a = x, b = MOD, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }

  ModInt pow(i64 n) const {
    ModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
 
  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.x;
  }
 
  friend istream &operator>>(istream &is, ModInt &a) {
    i64 t;
    is >> t;
    a = ModInt<MOD>(t);
    return (is);
  }
  static int get_mod() { return MOD; }
};

const int MOD = 1e9 + 7;
using MInt = ModInt<MOD>;

const int N = 500000 + 5 , MAXN = N * 30;

int n , m;
vector<int> G[N];

struct Node {
  int lson , rson;

  int cnt;
  MInt sum , ans;
  Node() : lson(0) , rson(0) , cnt(0) , sum(0) , ans(0) {}
} t[MAXN];

int cnt = 0 , root[N];

#define mid (((l) + (r)) >> 1)

void pushup(int rt) {
  int ls = t[rt].lson , rs = t[rt].rson;
  t[rt].cnt = t[ls].cnt + t[rs].cnt;
  t[rt].sum = t[ls].sum + t[rs].sum;
  t[rt].ans = t[ls].ans + t[rs].ans + t[rs].sum * t[ls].cnt - t[ls].sum * t[rs].cnt;  
}

void insert(int &rt , int pre , int l , int r , int p , int v) {
  if (!rt) rt = ++cnt;  
  t[rt] = t[pre];
  t[rt].cnt++;
  t[rt].sum += v;
  if (l == r) return ;
  if (p <= mid) {
    insert(t[rt].lson , t[pre].lson , l , mid , p , v); 
  } else {
    insert(t[rt].rson , t[pre].rson , mid + 1 , r , p , v);
  }
  pushup(rt);
}

int merge(int u , int v , int l , int r) {
  if (!u || !v) return u + v;
  if (l == r) {
    t[u].cnt += t[v].cnt;
    t[u].sum += t[v].sum;
    t[u].ans += t[v].ans;
    return u;
  }
  t[u].lson = merge(t[u].lson , t[v].lson , l , mid);
  t[u].rson = merge(t[u].rson , t[v].rson , mid + 1 , r);
  pushup(u);
  return u;
}

MInt ans[N];

int LIM;

void dfs(int u , int fa , const vector<int> &a , const vector<int> &b , const MInt &coef) {
  for (int v : G[u]) {
    if (v == fa) {
      continue;
    }
    dfs(v , u , a , b , coef);
    root[u] = merge(root[u] , root[v] , 1 , LIM);
  }
  // cout << a[u] << endl;
  insert(root[u] , root[u] , 1 , LIM , a[u] , b[u]);
  ans[u] += t[root[u]].ans * coef;
  // cout << "u=" << u << endl;
  // debug(root[u] , -MAXV , MAXV);
}

// min(|ai-aj|,|bi-bj|) = |ai-aj|+|bi-bj|-max(|ai-aj|,|bi-bj|)
// max(|ai-aj|,|bi-bj|) = 1/2 * (|pi-pj|+|qi-qj|)
// pi = ai+bi , qi = ai-bi

int a[N] , b[N] , p[N] , q[N];

void solve(int *arr , const MInt &coef) {

  vector<int> veca(n + 1) , vecb(n + 1);
  for (int i = 1 ; i <= n ; i++) {
    veca[i] = int(arr[i]);
  }

  auto buc = veca;
  sort(buc.begin() , buc.end());
  buc.resize(unique(buc.begin() , buc.end()) - buc.begin());

  LIM = buc.size();

  for (int i = 1 ; i <= n ; i++) {
    int d = lower_bound(buc.begin() , buc.end() , veca[i]) - buc.begin() + 1;
    vecb[i] = veca[i];
    veca[i] = d;
  }

  dfs(1 , 0 , veca , vecb , coef);

  for (int i = 1 ; i <= n ; i++) {
    root[i] = 0;
  }
  for (int i = 1 ; i <= cnt ; i++) {
    t[i] = Node();
  }
  cnt = 0;
}

int main() {
  // freopen("young.in", "r", stdin);
  // freopen("young.out", "w", stdout);
  cin.tie(nullptr)->sync_with_stdio(0);

  cin >> n;
  for (int i = 1 ; i < n ; i++) {
    int u , v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  for (int i = 1 ; i <= n ; i++) {
    cin >> a[i] >> b[i];
    p[i] = a[i] + b[i];
    q[i] = a[i] - b[i];

    // cout << p[i] << endl;
  }

  solve(a , 1);
  solve(b , 1);
  solve(p , MInt(-1) / 2);
  solve(q , MInt(-1) / 2);

  for (int i = 1 ; i <= n ; i++) {
    cout << ans[i] * 2 << '\n';
  }

  return 0;
}