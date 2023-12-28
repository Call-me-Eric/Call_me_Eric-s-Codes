#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10,INF = 0x3f3f3f3f;
struct Matrix{
    int a[2][2];
    Matrix(){a[0][0] = a[0][1] = a[1][0] = a[1][1] = INF;}
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c;
        c.a[0][0] = min(a.a[0][0] + b.a[0][0],a.a[0][1] + b.a[1][0]);
        c.a[0][1] = min(a.a[0][0] + b.a[0][1],a.a[0][1] + b.a[1][1]);
        c.a[1][0] = min(a.a[1][0] + b.a[0][0],a.a[1][1] + b.a[1][0]);
        c.a[1][1] = min(a.a[1][0] + b.a[0][1],a.a[1][1] + b.a[1][1]);
        return c;
    }
};
struct ansmtx{
    Matrix mtx[2][2];
    ansmtx(){mtx[0][0] = mtx[0][1] = mtx[1][0] = mtx[1][1] = Matrix();}
    friend ansmtx merg(ansmtx a,ansmtx b,int la,int ra,int lb,int rb){
        ansmtx c = ansmtx();
        c.mtx[0][0] = a.mtx[la ^ 0][ra ^ 0] * b.mtx[lb ^ 0][rb ^ 0];
        c.mtx[0][1] = a.mtx[la ^ 0][ra ^ 1] * b.mtx[lb ^ 0][rb ^ 1];
        c.mtx[1][0] = a.mtx[la ^ 1][ra ^ 0] * b.mtx[lb ^ 1][rb ^ 0];
        c.mtx[1][1] = a.mtx[la ^ 1][ra ^ 1] * b.mtx[lb ^ 1][rb ^ 1];
        return c;
    }
};
struct Segment_Tree{
    struct node{
        ansmtx val;bool lz, rz;
        node(ansmtx val = ansmtx(),bool lz = 0,bool rz = 0):val(val),lz(lz),rz(rz){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(merg(l.val,r.val,l.lz,l.rz,r.lz,r.rz));}
    void pushdown(int p){
        if(d[p].lz){d[p << 1].lz ^= 1;d[p << 1 | 1].lz ^= 1;d[p].lz = 0;}
        if(d[p].rz){d[p << 1].rz ^= 1;d[p << 1 | 1].rz ^= 1;d[p].rz = 0;}
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void build(int l,int r,int p){}
};
signed main(){
    return 0;
}