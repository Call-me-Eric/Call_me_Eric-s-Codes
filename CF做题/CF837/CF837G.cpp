#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 75100, mod = 1e9;
int n, m;
int a[maxn][3], b[maxn][3], x[maxn][2];
struct Segment_Tree{
    struct node{
        int l, r;int a, b;
        node(int a = 0,int b = 0,int l = 0,int r = 0):a(a),b(b),l(l),r(r){}
    }d[maxn * 160];
    int tot;
    int newnode(int p){d[++tot] = d[p];return tot;}
    void update(int &p,int l,int r,int s,int t,int a,int  b){
        p = newnode(p);
        if(s <= l && r <= t){d[p].a += a;d[p].b += b;return;}
        int mid = l + r >> 1;
        if(s <= mid)update(d[p].l,l,mid,s,t,a,b);
        if(mid < t)update(d[p].r,mid + 1,r,s,t,a,b);
    }
    int query(int p,int l,int r,int x){
        if(!p)return 0;
        int res = x * d[p].a + d[p].b;
        if(l == r)return res;
        int mid = l + r >> 1;
        if(x <= mid)res += query(d[p].l,l,mid,x);
        else res += query(d[p].r,mid + 1,r,x);
        return res;
    }
}tree;
int head[maxn << 2], sum[maxn];
signed main(){
    n = read();int mx = 0;
    for(int i = 1;i <= n;i++){
        x[i][0] = read();x[i][1] = read();b[i][0] = read();
        a[i][1] = read();b[i][1] = read();b[i][2] = read();
        head[i] = head[i - 1];
        tree.update(head[i],0,mod,0          ,x[i][0],a[i][0],b[i][0]);
        tree.update(head[i],0,mod,x[i][0] + 1,x[i][1],a[i][1],b[i][1]);
        tree.update(head[i],0,mod,x[i][1] + 1,mod    ,a[i][2],b[i][2]);
        sum[i] = sum[i - 1] + b[i][2];mx = max(mx,x[i][1] + 1);
    }
    m = read();int lastans = 0;
    for(int i = 1;i <= m;i++){
        int l = read(), r = read(), pos = (read() + lastans) % mod;
        if(pos >= mx)printf("%lld\n",lastans = sum[r] - sum[l - 1]);
        else printf("%lld\n",lastans = tree.query(head[r],0,mod,pos) - tree.query(head[l - 1],0,mod,pos));
    }
    return 0;
}