#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 998244353;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int n;
int x[maxn], v[maxn], ps[maxn];
struct node{
    int pos;int dist, speed;
    int lvec, rvec;//0 <=> <-,1 <=> ->
    node(int pos = 0,int dist = 0,int speed = 0,int lvec = 0,int rvec = 0
        ):pos(pos),dist(dist),speed(speed),lvec(lvec),rvec(rvec){}
    friend bool operator < (node a,node b){
        return a.dist * b.speed < b.dist * a.speed;
    }
}d[maxn << 1];
struct Matrix{
    int a[2][2];
    Matrix(){a[0][0] = a[1][0] = a[0][1] = a[1][1] = 0;}
    Matrix(int a1,int a2,int a3,int a4){//[a1,a2]\n[a3,a4]
        a[0][0] = a1;a[0][1] = a2;
        a[1][0] = a3;a[1][1] = a4;
    }
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix();
        for(int i = 0;i < 2;i++)for(int j = 0;j < 2;j++)
            for(int k = 0;k < 2;k++)c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j] % mod) % mod;
        return c;
    }
};
struct Segment_Tree{
    struct node{
        Matrix sum;
        node(Matrix sum = Matrix()):sum(sum){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum * r.sum);}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(Matrix(ps[l],ps[l],(1 - ps[l] + mod) % mod,(1 - ps[l] + mod) % mod));return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int l,int r,int pos,int p,int x,int y){
        if(l == r && l == pos){d[p].sum.a[x][y] = 0;return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,x,y);
        else update(mid + 1,r,pos,p << 1 | 1,x,y);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
}tree;
void main(){
    int inv100 = qpow(100,mod - 2);n = read();
    for(int i = 1;i <= n;i++){x[i] = read();v[i] = read();ps[i] = (1 - read() * inv100 % mod + mod) % mod;}
    if(n == 1){puts("0");return;}
    int cnt = 0;
    for(int i = 1;i < n;i++){
        d[++cnt] = node(i,x[i + 1] - x[i],v[i + 1] + v[i],1,0);
        if(v[i] > v[i + 1]){d[++cnt] = node(i,x[i + 1] - x[i],v[i] - v[i + 1],1,1);}
        if(v[i] < v[i + 1]){d[++cnt] = node(i,x[i + 1] - x[i],v[i + 1] - v[i],0,0);}
    }
    sort(d + 1,d + 1 + cnt);tree.build(1,n,1);
    int lst = 1, ans = 0;
    for(int i = 1;i <= cnt;i++){
        tree.update(1,n,d[i].pos,1,d[i].lvec,d[i].rvec);
        Matrix tmp = tree.query(1,n,1,n,1).sum * Matrix(1,0,0,0);
        int now = (tmp.a[0][0] + tmp.a[1][0]) % mod;
        ans = (ans + (d[i].dist) * qpow(d[i].speed,mod - 2) % mod * ((lst - now + mod) % mod) % mod) % mod;
        lst = now;
    }
    printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}