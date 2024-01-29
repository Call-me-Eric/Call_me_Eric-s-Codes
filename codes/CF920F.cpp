#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10, maxm = 1e6 + 10;
int n, m;
int a[maxn];

int de[maxm], prime[maxn], tot, num[maxm];
bool book[maxm];

struct Segment_Tree{
    struct node{
        int sum;bool tag;
        node(int sum = 0,bool tag = 0):sum(sum),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum + r.sum,l.tag && r.tag);}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){if(d[p].tag)return;}
        if(l == r){d[p] = node(de[d[p].sum],de[d[p].sum] == 1 || de[d[p].sum] == 2);return;}
        int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int s,int t){update(1,n,s,t,1);}
    int query(int l,int r){return query(1,n,l,r,1).sum;}
}tree;

signed main(){
    n = read(); m = read();int mx = 0;de[1] = 1;
    for(int i = 1;i <= n;i++)mx = max(mx,a[i] = read());
    for(int i = 2;i <= mx;i++){
        if(!book[i]){prime[++tot] = i;de[i] = 2;num[i] = 1;}
        for(int j = 1;j <= tot && i * prime[j] <= mx;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0){
                num[i * prime[j]] = num[i] + 1;
                de[i * prime[j]] = de[i] / (num[i] + 1) * (num[i * prime[j]] + 1);
                break;
            }
            de[i * prime[j]] = de[i] * de[prime[j]];
            num[i * prime[j]] = 1;
        }
    }
    tree.build(1,n,1);int opt, l, r;
    for(int i = 1;i <= m;i++){
        opt = read(); l = read(); r = read();
        if(opt == 1){tree.update(l,r);}
        else printf("%lld\n",tree.query(l,r));
        // for(int j = 1;j <= n;j++){printf("a[%lld] = %lld\n",j,tree.query(j,j));}
    }
    return 0;
}