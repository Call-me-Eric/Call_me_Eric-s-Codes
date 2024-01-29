#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch  = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 1e5 + 10;
int a[maxn];
struct node{
    int total, lazytag;
}d[maxn * 4];
void build(int l,int r,int p){
    if(l == r){
        d[p].total = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l,mid,p << 1); build(mid + 1,r,(p << 1) | 1);
    d[p].total = d[p << 1].total + d[(p << 1) | 1].total;
}
void update(int l,int r,int s,int t,int p,int addition){
    if(l <= s && t <= r){
        d[p].lazytag += addition;
        d[p].total += (t - s + 1) * addition;
        return;
    }
    int mid = (s + t) >> 1;
    if(d[p].lazytag){
        d[p << 1].lazytag += d[p].lazytag; d[p << 1].total += d[p].lazytag * (mid - s + 1);
        d[(p << 1) | 1].lazytag += d[p].lazytag; d[(p << 1) | 1].total += d[p].lazytag * (t - mid);
    }
    d[p].lazytag = 0;
    if(l <= mid)update(l,r,s,mid,p << 1,addition);
    if(r > mid)update(l,r,mid + 1,t,(p << 1) | 1,addition);
    d[p].total = d[p << 1].total + d[(p << 1) | 1].total;
}
int getsum(int l,int r,int s,int t,int p){
    if(l <= s && t <= r)return d[p].total;
    int mid = (s + t) >> 1;
    if(d[p].lazytag){
        d[p << 1].lazytag += d[p].lazytag; d[p << 1].total += d[p].lazytag * (mid - s + 1);
        d[(p << 1) | 1].lazytag += d[p].lazytag; d[(p << 1) | 1].total += d[p].lazytag * (t - mid);
    }
    d[p].lazytag = 0;
    return ((l <= mid) ? getsum(l,r,s,mid,p << 1) : 0) + ((r > mid) ? getsum(l,r,mid + 1,t,(p << 1) | 1) : 0);
}
signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();
    }
    build(1, n, 1);
    int x,y,z, k;
    for(int i = 1;i <= m;i++){
        x = read(); y = read(); z = read();
        if(x == 1){
            k = read();
            update(y,z,1,n,1,k);
        }
        else{
            printf("%lld\n",getsum(y,z,1,n,1));
        }
    }
    return 0;
}