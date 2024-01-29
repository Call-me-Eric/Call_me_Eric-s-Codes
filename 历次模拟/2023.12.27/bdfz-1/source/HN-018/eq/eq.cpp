#include <bits/stdc++.h>
using namespace std;

#define int long long
#define x first
#define y second
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 710;
const int mod = 998244353;

int n, m, tot, top, ans[N], las[N], ton[N], a[N * 2][N], b[N * 2];
int* stk1[N * N * 2]; int cnt, id[N], stk2[N * N * 2];
vector<int> t[N * 4];
inline int read()
{
    int asd = 0, qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0', zxc = getchar();
    return asd * qwe;
}
inline int power(int x, int y)
{
    int res = 1;
    while(y)
    {
        if(y & 1) res = res * x % mod;
        x = x * x % mod, y /= 2;
    }
    return res;
}
inline int mo(int x) { return (x % mod + mod) % mod; }
inline int inv(int x, int y) { return x % mod * power(y, mod - 2) % mod; }
inline void update(int p, int l, int r, int ls, int rs, int k)
{
    if(ls <= l && r <= rs)
        return t[p].push_back(k), void();
    int mid = (l + r) / 2;
    if(mid >= ls) update(p * 2, l, mid, ls, rs, k);
    if(mid <  rs) update(p * 2 + 1, mid + 1, r, ls, rs, k);
}
inline void back(int x)
{
    while(top > x)
        *stk1[top] = stk2[top], top--;
}
inline void save(int* x)
{
    ++top, stk1[top] = x, stk2[top] = *x;
}
inline void dfs(int p, int l, int r)
{
    int tim = top; save(&cnt);
    for(auto i : t[p])
    {
        id[++cnt] = i;
        fro(k, 1, n) save(&a[i][k]); save(&b[i]);
        fro(j, 1, n)
        {
            if(ton[j])
            {
                int z = inv(a[i][j], a[ton[j]][j]);
                fro(k, 1, n) a[i][k] = mo(a[i][k] - a[ton[j]][k] * z);
                b[i] = mo(b[i] - b[ton[j]] * z);
            }
        }
        fro(j, 1, n)
        {
            if(!ton[j] && a[i][j])
            {
                save(&ton[j]);
                fro(k, 1, n) if(k != j) a[i][k] = inv(a[i][k], a[i][j]);
                b[i] = inv(b[i], a[i][j]), a[i][j] = 1, ton[j] = i; break;
            }
        }
    }
    if(l == r)
    {
        memset(ans, 0, sizeof ans);
        bool flag = 1;
        fro(i, 1, n) save(&b[id[i]]);
        pre(i, n, 1)
        {
            int x = id[i], y = 0;
            fro(j, 1, n) if(ton[j] == x) { y = j; break; }
            if(!y)
            {
                if(b[x] == 0) printf("Many");
                if(b[x] != 0) printf("No");
                flag = 0; break;
            }
            fro(j, 1, n)
                b[x] = mo(b[x] - a[x][j] * ans[j]);
            if(a[x][y] == 0)
            {
                if(b[x] == 0) printf("Many");
                if(b[x] != 0) printf("No");
                flag = 0; break;
            }
            ans[y] = inv(b[x], a[x][y]);
        }
        if(flag) fro(i, 1, n) printf("%lld ", ans[i]);
        printf("\n");
    }
    else
    {
        int mid = (l + r) / 2;
        dfs(p * 2, l, mid), dfs(p * 2 + 1, mid + 1, r);
    }
    back(tim);
}

signed main()
{
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);
    n = read(), m = read();
    fro(i, 1, n)
    {
        fro(j, 1, n) a[i][j] = read();
        b[i] = read();
    }
    tot = n;
    fro(i, 1, n) las[i] = 1, ton[i] = i;
    fro(i, 1, m)
    {
        int z = read();
        update(1, 1, m + 1, las[z], i, ton[z]);
        ton[z] = ++tot, las[z] = i + 1;
        fro(j, 1, n) a[tot][j] = read();
        b[tot] = read();
    }
    fro(i, 1, n) update(1, 1, m + 1, las[i], m + 1, ton[i]);
    memset(ton, 0, sizeof ton);
    dfs(1, 1, m + 1);
    return 0;
}