#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int  x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, m;
char ch[maxn];
struct Matrix{
    int a[2][2];
    Matrix(){memset(a,0,sizeof a);}
    friend Matrix operator *(Matrix a,Matrix b){
        Matrix c = Matrix();
        for(int i = 0;i < 2;i++)
            for(int j = 0;j < 2;j++){
                c.a[i][j] = 0x3f3f3f3f;
                for(int k = 0;k < 2;k++)
                    c.a[i][j] = min(c.a[i][j],a.a[i][k] + b.a[k][j]);
            }
        return c;
    }
};
class Segment_Tree{
private:
    struct node{
        Matrix x;
        node(char ch = '0'){
            if(ch == '0'){x.a[0][0] = 0;x.a[0][1] = 2;x.a[1][0] = x.a[1][1] = 1;}
            else{x.a[1][1] = 0;x.a[1][0] = 2;x.a[0][0] = x.a[0][1] = 1;}
        }
        node(Matrix x):x(x){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.x * r.x);}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(ch[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p,char upd){
        if(l == r && l == pos){d[p] = node(upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;
        if(t <= mid){return query(l,mid,s,t,p << 1);}
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
public:
    void build(){build(1,n,1);}
    void update(int pos,char upd){update(1,n,pos,1,upd);}
    Matrix query(int l,int r){return query(1,n,l,r,1).x;}
}tree;
signed main(){
    n = read();scanf("%s",ch + 1);
    for(int i = 1;i <= n / 2;i++){swap(ch[i],ch[n - i + 1]);}
    tree.build();
    int u, v, opt; m = read();
    for(int i = 1;i <= m;i++){
        opt = read();u = read(); v = read();
        if(opt == 1){
            u = n - u + 1;v = n - v + 1;swap(u, v);
            Matrix A = Matrix();
            A.a[0][0] = 0;A.a[0][1] = A.a[1][0] = A.a[1][1] = 0x3f3f3f3f;
            A = A * tree.query(u,v);
            printf("%d\n",min(A.a[0][0],A.a[0][1] + 1));
        }
        else{
            u = n - u + 1;ch[u] = v + '0';
            tree.update(u,ch[u]);
        }
    }
    return 0;
}