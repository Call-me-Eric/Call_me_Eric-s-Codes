#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
typedef long long ll;
const int maxn = 1e5 + 10;
int Q;ll M;
struct Segment_Tree{
    int d[maxn << 2];
    void build(int l,int r,int p){
        if(l == r){d[p] = 1;return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1, r, p << 1 | 1);
        ll a = d[p << 1], b = d[p << 1 | 1], c = a * b % M;
        d[p] = c;
    }
    void update(int l,int r,int goal,int p,int add){
        if(l == r && l == goal){d[p] = add;return;}
        int mid = l + r >> 1;
        if(goal <= mid)update(l,mid,goal,p << 1,add);
        else update(mid + 1,r,goal,p << 1 | 1,add);
        ll a = d[p << 1], b = d[p << 1 | 1], c = a * b % M;
        d[p] = c;
    }
    int query(){return d[1];}
}tree;
signed main(){
int T = read();
while(T--){
    Q = read(); M = read();
    tree.build(1,Q,1); int opt, u;
    for(int i = 1;i <= Q;i++){
        opt = read(); u = read();
        if(opt == 1){tree.update(1,Q,i,1,u);}
        else {tree.update(1,Q,u,1,1);tree.update(1,Q,i,1,1);}
        printf("%d\n",tree.query());
    }
}
    return 0;
}