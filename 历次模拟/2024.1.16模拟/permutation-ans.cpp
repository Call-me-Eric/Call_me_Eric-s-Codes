#include<bits/stdc++.h>
// #define int long long

#define ll __int128
using namespace std;
bool stmemory;
inline ll read(){
    ll x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x * 10) + (ch - '0');ch = getchar();}
    return x * f;
}
void write(ll x){if(x % 10)write(x / 10);putchar(x % 10 + '0');}
const int maxn = 5e5 + 10;
int n, c, q;
int a[maxn];
struct node{
    int l, r;ll w;
    node(int l = 0,int r = 0,ll w = 0):l(l),r(r),w(w){}
    friend bool operator < (node a,node b){return ::a[a.r] < ::a[b.r];}
};
node deq[5][maxn * 10];
ll sumw[5][maxn * 5];
ll ql[5], qr[5];
ll sum[5][maxn];
ll calc_eq(int len,int x){
    if(len <= 1)return x == 0;if(len - 1 < x)return 0;
    ll res = 1;
    for(ll i = len - 1;i >= len - x;i--)res *= i;
    for(ll i = x;i;i--)res /= i;
    return res;
}
ll calc_le(int len,int x){
    ll res = 0;
    for(int i = 0;i <= x;i++)res += calc_eq(len,i);
    return res;
}
void init(){
    for(int s = 1;s <= c;s++){
        ql[s] = maxn * 5, qr[s] = ql[s] - 1;
        for(int i = 1;i <= n;i++)sum[s][i] = 0;
        deq[s][++qr[s]] = node(n,n,1);
        for(int i = n - 1;i;i--){
            int dl = 0,dr = 0;
            for(int j = 1;j <= min(s,n - i);j++){
                ll w = calc_le(n - i - j,s - j);
                if(a[i + j] < a[i]){
                    deq[s][ql[s] - (++dl)] = node(i,i + j,w);
                    sum[s][i + 1]++;
                }
                else deq[s][qr[s] + (++dr)] = node(i,i + j,w);
            }
            if(dl){sort(deq[s] + ql[s] - dl,deq[s] + ql[s]);ql[s] -= dl;}
            if(dr){sort(deq[s] + qr[s] + 1,deq[s] + qr[s] + dr + 1);qr[s] += dr;}
        }
        for(int i = 1;i <= n;i++)sum[s][i] += sum[s][i - 1];
        for(int i = ql[s];i <= qr[s];i++){sumw[s][i - ql[s] + 1] = sumw[s][i - ql[s] - 1 + 1] + deq[s][i].w;}
    }
}
node F(int st,int s,ll rank){
    int i = sum[s][st];int l = i + 1,r = qr[s] - ql[s] + 2;
    while(l < r){
        int mid = l + r >> 1;
        if(rank <= sumw[s][mid] - sumw[s][i])r = mid;
        else l = mid + 1;
    }
    return node(deq[s][ql[s] + l - 1].l,deq[s][ql[s] + l - 1].r,sumw[s][l - 1] - sumw[s][i]);
}
void solve(){
    n = read(); c = read(); q = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    init();const ll lim = calc_le(n, c);
    while(q--){
        ll rank = read();int pos = read();
        if(rank > lim){puts("-1");continue;}
        vector<pair<int,int> > revs;
        int p = 1, s = c;
        while(1){
            node tmp = F(p,s,rank);
            revs.push_back(make_pair(tmp.l,tmp.r));
            rank -= tmp.w; s -= (tmp.r - tmp.l);
            p = tmp.r + 1;
            if(!s || p > n)break;
        }
        bool flag = false;
        for(auto i : revs){
            if(i.first <= pos && pos <= i.second){
                printf("%d\n",a[i.second - (pos - i.first)]);
                flag = true;break;
            }
        }
        if(!flag)printf("%d\n",a[pos]);
    }
}
bool edmemory;
signed main(){
    freopen("permutation.in","r",stdin);
    freopen("permutation.out","w",stdout);
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << "Mib cost.\n";
    solve();
    return 0;
}