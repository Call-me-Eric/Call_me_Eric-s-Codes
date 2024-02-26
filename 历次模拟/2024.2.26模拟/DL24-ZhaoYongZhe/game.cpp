#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, q;
int a[maxn];
namespace BF{
void main(){
    int opt, l, r,cnt = 0;
    for(int test = 1;test <= q;test++){
        opt = read();
        if(opt == 1){
            l = read(); r = read();
            for(int i = l;i <= r;i++){a[i] ^= 1;}
        }
        else{
            ++cnt;
            printf("test %d:\n",cnt);
            int k = read();int res = 0;
            for(int j = 1;j <= k;j++){
                l = read(); r = read();
                int sum = 0, tmp = 0;
                for(int i = l;i <= r;i++){
                    if(a[i]){
                        int x = i - l + 1, y = r - l + 1 - (i - l + 1) + 1;
                        if(x > y)swap(x, y);
                        tmp = max(tmp,y - x + 1);
                    }
                }
                printf("res = %d\n",tmp);
                res ^= tmp;
            }
            // printf("res = %d\n",res);
            puts(res ? "Yes" : "No");
        }
    }
}
};
namespace Seg{
struct node{
    int sum0,sum1;
    int l0,l1,r0,r1;
    int tag = 0;
    node(int val = -1,int pos = 0){
        l0 = l1 = 0x3f3f3f3f;r0 = r1 = -0x3f3f3f3f;
        sum0 = sum1 = 0;tag = 0;
        if(val == 0){sum0 = 1;l0 = r0 = pos;}
        if(val == 1){sum1 = 1;r1 = l1 = pos;}
    }
    node(int s0,int s1,int l0,int l1,int r0,int r1
    ):sum0(s0),sum1(s1),l0(l0),r0(r0),l1(l1),r1(r1),tag(0){}
};
node mergenode(node l,node r){
    return node(l.sum0 + r.sum0,l.sum1 + r.sum1,
    min(l.l0,r.l0),min(l.l1,r.l1),max(r.r0,l.r0),max(r.r1,l.r1));
}
struct Segment_Tree{
    node d[maxn << 2];
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l],l);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void upd(int p){
        swap(d[p].sum0,d[p].sum1); d[p].tag ^= 1;
        swap(d[p].l0,d[p].l1); swap(d[p].r0,d[p].r1);
    }
    void pushdown(int p){
        if(d[p].tag){
            upd(p << 1);upd(p << 1 | 1);
            d[p].tag = 0;
        }
    }
    void update(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){upd(p);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int l,int r){update(1,n,l,r,1);}
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;
void main(){
    tree.build(1,n,1);
    int opt, l, r, cnt = 0;
    while(q--){
        opt = read();
        if(opt == 1){l = read(); r = read();tree.update(l,r);}
        else{
            // printf("test:%d\n",++cnt);
            int k = read();int ans = 0;
            for(int i = 1;i <= k;i++){
                l = read(); r = read();
                node tmp = tree.query(l,r);
                if(tmp.sum1 == 0)continue;
                int xl = tmp.l1 - l + 1, xr = tmp.r1 - l + 1;
                int m = r - l + 1, res = 0;
                res = abs(m - xl + 1 - xl) + 1;
                res = max(res,abs(m - xr + 1 - xr) + 1);
                // printf("res = %d\n",res);
                ans ^= res;
            }
            puts(ans ? "Yes" : "No");
        }
    }
}
};
void main(){
    n = read(); q = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    Seg::main();
    return;
}
};
bool edmemory;
signed main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}