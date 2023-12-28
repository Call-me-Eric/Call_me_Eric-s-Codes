# include <bits/stdc++.h>

using namespace std;

# define ll long long

const int N = 2e5 + 5 , mod = 998244353;
int m , tp;
int rt , lc[N*60] , rc[N*60] , tag[N*60] , tot;
ll val[N*60];

void PushUp(int x) {val[x] = (val[lc[x]] + val[rc[x]]) % mod;}

void PushDown(int x , ll l , ll r)
{
    if(tag[x])
    {
        ll mid = l + r >> 1;
        if(lc[x]) val[lc[x]] = (val[lc[x]] + tag[x] * (mid - l + 1)) % mod , tag[lc[x]] = tag[x];
        if(rc[x]) val[rc[x]] = (val[rc[x]] + tag[x] * (r - (mid + 1) + 1)) % mod , tag[rc[x]] = tag[x];
        tag[x] = 0;
    }
}
 
void Upt(int &x , ll l , ll r , ll L , ll R , ll v)
{
    if(!x) x = ++tot;
    if(L <= l && r <= R) return val[x] = (val[x] + v * (r - l + 1) % mod) % mod , tag[x] = v , void();
    PushDown(x , l , r);
    ll mid = l + r >> 1;
    if(mid >= L) Upt(lc[x] , l , mid , L , R , v);
    if(mid < R) Upt(rc[x] , mid + 1 , r , L , R , v);
    PushUp(x);
} 

ll Query(int x , ll l , ll r , ll L , ll R)
{
    if(!x) return 0;
    if(L <= l && r <= R) return val[x] % mod;
    PushDown(x , l , r);
    ll res = 0 , mid = l + r >> 1;
    if(mid >= L) res = (res + Query(lc[x] , l , mid , L , R)) % mod;
    if(mid < R) res = (res + Query(rc[x] , mid + 1 , r , L , R)) % mod;
    return res % mod;
}

int main()
{
    freopen("maze.in" , "r" , stdin);
    freopen("maze.out" , "w" , stdout);
    cin >> m >> tp;
    for(int i = 1; i <= m; i++)
    {
        ll opt , l , r , v;
        cin >> opt;
        if(opt == 1) cin >> l >> r >> v , Upt(rt , 1 , 1e10 , l , r , v);
        else cin >> l >> r , cout << Query(rt , 1 , 1e10 , l , r) << '\n';
    }
    return 0;
}