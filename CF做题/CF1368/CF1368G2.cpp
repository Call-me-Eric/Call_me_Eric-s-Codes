#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10,INF = 0x3f3f3f3f;
int n, m, q;
int L[maxn], R[maxn], U[maxn], D[maxn];
char ch[maxn];
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
    ansmtx(int x){
        mtx[0][0].a[0][0] = 2;    mtx[0][0].a[0][1] = x;
        mtx[0][0].a[1][0] = x + 2;mtx[0][0].a[1][1] = 0;
        
        mtx[1][0].a[0][0] = 1;    mtx[1][0].a[0][1] = x + 1;
        mtx[1][0].a[1][0] = x + 1;mtx[1][0].a[1][1] = 1;
        
        mtx[0][1].a[0][0] = 1;    mtx[0][1].a[0][1] = x + 1;
        mtx[0][1].a[1][0] = x + 1;mtx[0][1].a[1][1] = 1;
        
        mtx[1][1].a[0][0] = 0;    mtx[1][1].a[0][1] = x + 2;
        mtx[1][1].a[1][0] = x;    mtx[1][1].a[1][1] = 2;
    }
    friend ansmtx merg(ansmtx a,ansmtx b,int la,int ra,int lb,int rb){
        ansmtx c = ansmtx(0);
        c.mtx[0][0] = a.mtx[la ^ 0][ra ^ 0] * b.mtx[lb ^ 0][rb ^ 0];
        c.mtx[0][1] = a.mtx[la ^ 0][ra ^ 1] * b.mtx[lb ^ 0][rb ^ 1];
        c.mtx[1][0] = a.mtx[la ^ 1][ra ^ 0] * b.mtx[lb ^ 1][rb ^ 0];
        c.mtx[1][1] = a.mtx[la ^ 1][ra ^ 1] * b.mtx[lb ^ 1][rb ^ 1];
        return c;
    }
};
struct Segment_Tree{
    int tot;bool opt;//opt = 0 : f[i]i\in[1,n];OW:i\in[1,m]
    bool leaf[maxn << 2];
    struct node{
        ansmtx val;bool lz, rz;int suml, sumr, l, r;
        node(bool lz = 0,bool rz = 0,int l = 0,int r = 0,int suml = 0,int sumr = 0,ansmtx val = ansmtx(0)
        ):val(val),lz(lz),rz(rz),suml(suml),sumr(sumr),l(l),r(r){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(0,0,l.l,r.r,
    l.suml + r.suml,l.sumr + r.sumr,merg(l.val,r.val,l.lz,l.rz,r.lz,r.rz));}
    void pushdown(int p){
        if(leaf[p])return;
        if(d[p].lz){
            d[p << 1].lz ^= 1;d[p << 1 | 1].lz ^= 1;
            d[p << 1].suml = d[p << 1].r - d[p << 1].l + 1 - d[p << 1].suml;
            d[p << 1 | 1].suml = d[p << 1 | 1].r - d[p << 1 | 1].l + 1 - d[p << 1 | 1].suml;
        }
        if(d[p].rz){
            d[p << 1].rz ^= 1;d[p << 1 | 1].rz ^= 1;
            d[p << 1].sumr = d[p << 1].r - d[p << 1].l + 1 - d[p << 1].sumr;
            d[p << 1 | 1].sumr = d[p << 1 | 1].r - d[p << 1 | 1].l + 1 - d[p << 1 | 1].sumr;
        }
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void build(int l,int r,int p){
        if(l == r){
            leaf[p] = 1;
            if(!opt){
                d[p].lz = L[l];d[p].rz = R[l]; d[p].l = d[p].r = l;
                d[p].suml = L[l];d[p].sumr = R[l]; d[p].val = ansmtx(m);
            }
            else{
                d[p].lz = U[l];d[p].rz = D[l]; d[p].l = d[p].r = l;
                d[p].suml = U[l];d[p].sumr = D[l]; d[p].val = ansmtx(n);
            }
            return;
        }
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void build(int x,bool o){opt = o;tot = x;build(1,tot,1);}
    void update(int l,int r,int s,int t,int p,bool op){//op=0<=>L or U;OW: R or D
        if(s <= l && r <= t){
            if(!op){
                d[p].suml = d[p].r - d[p].l + 1 - d[p].suml;
                d[p].lz ^= 1; return;
            }
            else {
                d[p].sumr = d[p].r - d[p].l + 1 - d[p].sumr;
                d[p].rz ^= 1; return;
            }
        }
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,op);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,op);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int s,int t,int op){update(1,tot,s,t,1,op);}
    node query(){pushdown(1);return d[1];}
    void DEBUG(int l,int r,int p){
        printf("l = %d, r = %d, p = %d,suml = %d,sumr = %d\n",d[p].l,d[p].r,p,d[p].suml,d[p].sumr);
        if(l == r)return; int mid = l + r >> 1;
        DEBUG(l,mid,p << 1);DEBUG(mid + 1,r,p << 1 | 1);
    }
    void DEBUG(){DEBUG(1,tot,1);}
}tree[2];
int getans(){
    // printf("tree0 : \n");tree[0].DEBUG();
    // printf("tree1 : \n");tree[1].DEBUG();
    Segment_Tree::node tmp0 = tree[0].query(),tmp1 = tree[1].query();
    Matrix a, b;
    a.a[0][0] = tmp1.suml;a.a[0][1] = m - tmp1.suml;
    a.a[1][0] = a.a[1][1] = INF;

    b.a[0][0] = tmp0.suml;b.a[0][1] = n - tmp0.suml;
    b.a[1][0] = b.a[1][1] = INF;
    
    a = a * tmp0.val.mtx[1 ^ tmp0.lz][1 ^ tmp0.rz];
    b = b * tmp1.val.mtx[1 ^ tmp1.lz][1 ^ tmp1.rz];
    
    // printf("n = %d:suml = %d sumr = %d, l = %d, r = %d\n",n,tmp0.suml,tmp0.sumr,tmp0.l,tmp0.r);
    // printf("m = %d:suml = %d sumr = %d, l = %d, r = %d\n",m,tmp1.suml,tmp1.sumr,tmp1.l,tmp1.r);
    a.a[0][0] += tmp1.sumr;a.a[0][1] += m - tmp1.sumr;
    b.a[0][0] += tmp0.sumr;b.a[0][1] += n - tmp0.sumr;
    return min(min(a.a[0][0],a.a[0][1]),min(b.a[0][0],b.a[0][1]));
}
signed main(){
    n = read(); m = read(); q = read();
    scanf("%s",ch + 1);for(int i = 1;i <= n;i++)L[i] = (ch[i] == 'B');
    scanf("%s",ch + 1);for(int i = 1;i <= n;i++)R[i] = (ch[i] == 'B');
    scanf("%s",ch + 1);for(int i = 1;i <= m;i++)U[i] = (ch[i] == 'B');
    scanf("%s",ch + 1);for(int i = 1;i <= m;i++)D[i] = (ch[i] == 'B');

    tree[0].build(n,0);tree[1].build(m,1);int u, v;
    printf("%d\n",getans());
    for(int i = 1;i <= q;i++){
        scanf("%s%d%d",ch,&u,&v);
        if(ch[0] == 'L'){tree[0].update(u, v, 0);}
        if(ch[0] == 'R'){tree[0].update(u, v, 1);}
        if(ch[0] == 'U'){tree[1].update(u, v, 0);}
        if(ch[0] == 'D'){tree[1].update(u, v, 1);}
        printf("%d\n",getans());
    }
    return 0;
}
/*
1 1 19
R
R
R
B
L 1 1
R 1 1
L 1 1
D 1 1
U 1 1
L 1 1
R 1 1
R 1 1
D 1 1
D 1 1
L 1 1
D 1 1
L 1 1
R 1 1
R 1 1
U 1 1
D 1 1
L 1 1
U 1 1
*/