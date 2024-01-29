#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0,f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, mod;
const int maxn = 1e5 + 10;
int a[maxn];
struct node{
    int total, powertag, addtag;
}d[maxn * 4];
void build(int l,int r,int p){
    d[p].powertag = 1;d[p].addtag = 0;
    if(l == r){d[p].total = a[l];return;}
    int mid = (l + r) >> 1;
    build(l,mid,p << 1); build(mid + 1,r, (p << 1) | 1);
    d[p].total = (d[p << 1].total + d[(p << 1) | 1].total) % mod;
}
void pushdown(int p,int l,int r){
    int mid = (l + r) >> 1;
    d[ p << 1     ].total    = (d[ p << 1     ].total * d[p].powertag + d[p].addtag * (mid - l + 1)) % mod;
    d[(p << 1) | 1].total    = (d[(p << 1) | 1].total * d[p].powertag + d[p].addtag * (r - mid)    ) % mod;
    d[ p << 1     ].powertag = (d[ p << 1     ].powertag * d[p].powertag) % mod;
    d[(p << 1) | 1].powertag = (d[(p << 1) | 1].powertag * d[p].powertag) % mod;
    d[ p << 1     ].addtag   = (d[ p << 1     ].addtag   * d[p].powertag + d[p].addtag) % mod;
    d[(p << 1) | 1].addtag   = (d[(p << 1) | 1].addtag   * d[p].powertag + d[p].addtag) % mod;
    d[p].addtag = 0; d[p].powertag = 1; return;
}
void powupdate(int l,int r,int s,int t,int p,int addition){
    if(r < s || l > t)return;
    if(l <= s && t <= r){
        d[p].powertag = (d[p].powertag * addition) % mod;
        d[p].total    = (d[p].total    * addition) % mod;
        d[p].addtag   = (d[p].addtag   * addition) % mod;
        return;
    } pushdown(p,s,t); int mid = (s + t) >> 1;
    if(l <= mid) powupdate(l,r,   s   ,mid, p << 1     ,addition);
    if(mid < r)  powupdate(l,r,mid + 1,t  ,(p << 1) | 1,addition);
    d[p].total = (d[p << 1].total + d[(p << 1) | 1].total) % mod;
    return;
}
void addupdate(int l,int r,int s,int t,int p,int addition){
    if(r < s || l > t)return;
    if(l <= s && t <= r){
        d[p].total    = (d[p].total  + addition * (t - s + 1)) % mod;
        d[p].addtag   = (d[p].addtag + addition              ) % mod;
        return;
    } pushdown(p,s,t); int mid = (s + t) >> 1;
    if(l <= mid) addupdate(l,r,   s   ,mid, p << 1     ,addition);
    if(mid < r)  addupdate(l,r,mid + 1,t  ,(p << 1) | 1,addition);
    d[p].total = (d[p << 1].total + d[(p << 1) | 1].total) % mod;
    return;
}
int getsum(int l,int r,int s,int t,int p){
    if(l <= s && t <= r) return d[p].total; pushdown(p,s,t); int mid = (s + t) >> 1;
    return (((l <= mid) ? getsum(l,r,s,mid,p << 1) : 0) + ((mid < r) ? getsum(l,r,mid + 1,t,(p << 1) | 1) : 0)) % mod;
}
signed main(){
    n = read(); m = read(); mod = read();
    for(int i = 1;i <= n;i++) a[i] = read();
    build(1,n,1); int x, y, op, k;
    for(int i = 1;i <= m;i++){
        op = read();
        if(op == 1){
            x = read(); y = read(); k = read();
            powupdate(x,y,1,n,1,k);
        }
        else if(op == 2){
            x = read(); y = read(); k = read();
            addupdate(x,y,1,n,1,k);
        }
        else {
            x = read(); y = read();
            printf("%lld\n",getsum(x,y,1,n,1) % mod);
        }
    }
    return 0;
}