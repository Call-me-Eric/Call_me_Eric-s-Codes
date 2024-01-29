#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
struct node{
    int a, b, typ;
    unordered_map<int,int> val;
    node(int a = 0,int b = 0,int typ = 0):a(a),b(b),typ(typ){val.clear();}
}a[maxn];
int n, k, q;
int minn[maxn], maxx[maxn];
int calc(int id, int x){
    if(a[id].val.count(x))return a[id].val[x];
    int l = a[id].a, r = a[id].b;
    if(a[id].typ ^ a[l].typ){
        if(a[l].a == r || a[l].b == r){
            return a[id].val[x] = calc(r,x);
        }
    }
    if(a[id].typ ^ a[r].typ){
        if(a[r].a == l || a[r].b == l){
            return a[id].val[x] = calc(l,x);
        }
    }
    int i = calc(a[id].a,x);
    if(a[id].typ == 1 && i == maxx[x])return a[id].val[x] = i;
    if(a[id].typ == 2 && i == minn[x])return a[id].val[x] = i;
    int j = calc(a[id].b,x);
    if(a[id].typ == 1)a[id].val[x] = max(i,j);
    else a[id].val[x] = min(i, j);
    return a[id].val[x];
}
signed main(){
    freopen("compose.in","r",stdin);
    freopen("compose.out","w",stdout);
    n = read(); k = read(); q = read();
    int opt, x, y;
    for(int i = 1;i <= k;i++)
        for(int j = 1;j <= n;j++){
            a[i].val[j] = read();
            minn[j] = min(minn[j],a[i].val[j]);
            maxx[j] = max(maxx[j],a[i].val[j]);
        }
    for(int i = 1;i <= q;i++){
        opt = read(); x = read(); y = read();
        if(opt <= 2){a[++k] = node(x,y,opt);}
        else{printf("%d\n",calc(x,y));}
    }
    return 0;
}