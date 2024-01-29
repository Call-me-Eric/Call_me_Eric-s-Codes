#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, k;
struct BIT{
    int c[maxn << 2], len;
    inline int lowbit(int x){return x & (-x);}
    inline void upd(int x,int add){for(;x <= len;x += lowbit(x))c[x] += add;}
    inline int qry(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
}tree;
struct node{
    int x, y, z, w, ans;
    node(int x = 0,int y = 0,int z = 0,int w = 0):x(x),y(y),z(z),w(w){}
}a[maxn], b[maxn];

struct cmp1{bool operator()(node a,node b){return a.x != b.x ? a.x < b.x : (a.y != b.y ? a.y < b.y : a.z < b.z);}};
struct cmp2{bool operator()(node a,node b){return a.y != b.y ? a.y < b.y : a.z < b.z;}};

int cnt[maxn];
void cdq(int l,int r){
    if(l == r)return; int mid = l + r >> 1;
    cdq(l,mid); cdq(mid + 1,r);
    sort(a + l,a + mid + 1,cmp2());
    sort(a + mid + 1,a + r + 1,cmp2());
    int i = mid + 1,j = l;
    while(i <= r){
        while(a[j].y <= a[i].y && j <= mid)
            tree.upd(a[j].z,a[j].w),j++;
        a[i].ans += tree.qry(a[i].z);i++;
    }
    for(i = l;i < j;i++)tree.upd(a[i].z,-a[i].w);
}

signed main(){
    n = read();tree.len = k = read();int x, y, z;
    for(int i = 1;i <= n;i++){
        x = read(); y = read(); z = read();
        b[i] = node(x,y,z);
    }
    sort(b + 1,b + 1 + n,cmp1());x = 0;z = n;n = 0;
    for(int i = 1;i <= z;i++){
        x++;
        if(b[i].x != b[i + 1].x || b[i].y != b[i + 1].y || b[i].z != b[i + 1].z){
            a[++n] = b[i]; a[n].w = x; x = 0;
        }
    }
    cdq(1,n);
    for(int i = 1;i <= n;i++)cnt[a[i].ans + a[i].w - 1] += a[i].w;
    for(int i = 0;i < z;i++)printf("%d\n",cnt[i]);
    return 0;
}