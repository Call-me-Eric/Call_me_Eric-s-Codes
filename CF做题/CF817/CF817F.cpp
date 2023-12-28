#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0 , f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, tot;
int tag[maxn], x[maxn], y[maxn];
vector<int> vec;
struct Segment_Tree{
    int mxxxx;
    struct node{
        int sum, tag, l, r;//sum:count 1
        node(int sum = 0,int l = 0,int r = 0,int tag = 0):sum(sum),l(l),r(r),tag(tag){}
    }d[maxn << 4];
    node mergenode(node l,node r){return node(l.sum + r.sum,l.l,r.r);}
    void gettag(int p,int t){
        if(p > mxxxx || d[p].r == 0)return;
        if(t == 1){d[p].sum = d[p].r - d[p].l + 1;}
        if(t == 2){d[p].sum = 0;}
        if(t == 3){d[p].sum = d[p].r - d[p].l + 1 - d[p].sum;}
        d[p].tag = t;
    }
    void build(int l,int r,int p){
        if(l == tot)mxxxx = p << 1;
        if(l == r){d[p] = node(0,l,r,0);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1, r ,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void pushdown(int p){
        if(p > mxxxx || d[p].r == 0)return;
        if(d[p].tag && (d[p].r != d[p].l)){
            if(d[p].tag == 3){
                if(d[p << 1].tag == 1 || d[p << 1].tag == 2){gettag(p << 1,d[p << 1].tag ^ 3);}
                else{d[p << 1].tag ^= 3;d[p << 1].sum = d[p << 1].r - d[p << 1].l + 1 - d[p << 1].sum;}

                if(d[p << 1 | 1].tag == 1 || d[p << 1 | 1].tag == 2){gettag(p << 1 | 1,d[p << 1 | 1].tag ^ 3);}
                else{d[p << 1 | 1].tag ^= 3;d[p << 1 | 1].sum = d[p << 1 | 1].r - d[p << 1 | 1].l + 1 - d[p << 1 | 1].sum;}
            }
            else {
                // if(d[p << 1].tag == 3)pushdown(p << 1);
                gettag(p << 1,d[p].tag);
                // if(d[p << 1 | 1].tag == 3)pushdown(p << 1 | 1);
                gettag(p << 1 | 1,d[p].tag);
            }
            d[p].tag = 0;
        }
    }
    void update(int l,int r,int s,int t,int p,int tags){
        if(s <= l && r <= t){pushdown(p);gettag(p,tags);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,tags);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,tags);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
        // printf("l=%lld r=%lld p=%lld sum=%lld\n",l,r,p,d[p].sum);
    }
    int query(int l,int r,int p){
        if(l == r)return l;
        int mid = l + r >> 1;pushdown(p);
        // printf("l=%lld r=%lld p=%lld sum=%lld\n",l,r,p,d[p].sum);
        // printf("lsum=%lld,rsum=%lld\n",d[p << 1].sum,d[p << 1 | 1].sum);
        if(d[p << 1].sum < d[p << 1].r - d[p << 1].l + 1)
            return query(l,mid,p << 1);
        else return query(mid + 1,r,p << 1 | 1);
    }
    void update(int s,int t,int tags){update(1,tot,s,t,1,tags);}
    int query(){return query(1,tot,1);}
}tree;
signed main(){
    n = read();vec.push_back(-1);
    for(int i = 1;i <= n;i++){
        tag[i] = read(); x[i] = read(); y[i] = read();
        vec.push_back(x[i]);vec.push_back(y[i]);
        vec.push_back(y[i] + 1);if(x[i] != 1)vec.push_back(x[i] - 1);
    }
    sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());tot = vec.size() - 1;
    // printf("tot=%lld : ",tot);
    // for(int i : vec)printf("%d ",i);puts("");
    if(vec[1] > 1){for(int i = 1;i <= n;i++)puts("1");return 0;}
    tree.build(1,tot,1);
    for(int i = 1;i <= n;i++){
        x[i] = lower_bound(vec.begin(),vec.end(),x[i]) - vec.begin();
        y[i] = lower_bound(vec.begin(),vec.end(),y[i]) - vec.begin();
        // printf("%lld %lld %lld\n",x[i],y[i],tag[i]);
        tree.update(x[i],y[i],tag[i]);
        printf("%lld\n",vec[tree.query()]);
        // for(int i = 1;i <= 13;i++){printf("i=%lld,l=%lld,r=%lld,sum=%lld,tag=%lld\n",i,tree.d[i].l,tree.d[i].r,tree.d[i].sum,tree.d[i].tag);}       
    }
    return 0;
}