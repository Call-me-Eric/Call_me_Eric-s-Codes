#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int n, m;
int a[maxn];
struct balance_tree{
    typedef long long ll;ll opts;const ll shift = 30;
    __gnu_pbds::tree<ll,__gnu_pbds::null_type,std::less<ll>,__gnu_pbds::rb_tree_tag
    ,__gnu_pbds::tree_order_statistics_node_update> d;
    void insert(int y){ll x = y;d.insert((x << shift) + opts);opts++;}
    void delet(int y){ll x = y;d.erase(d.lower_bound(x << shift));}
    int rks(int y){ll x = y;int ans = d.order_of_key(x << shift) + 1;return ans;}
    int mxrks(int y){ll x = y;return d.order_of_key((x + 1) << shift);}
    int pos(int y){ll x = y;int ans = (*d.find_by_order(x - 1)) >> shift;return ans;}
    int pre(int y){ll x = y;int ans = (*--d.lower_bound(x << shift)) >> shift;return ans;}
    int suf(int y){ll x = y;int ans = (*d.lower_bound((x + 1) << shift)) >> shift;return ans;}
    bool find(int y){return pos(rks(y)) == y;}
};
class Segment_Tree{
private:
    balance_tree d[maxn << 2];
    void build(int l,int r,int p){
        d[p].insert(-2147483647);d[p].insert(2147483647);
        for(int i = l;i <= r;i++)d[p].insert(a[i]);
        if(l == r){return;}int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
    }
    void update(int l,int r,int pos,int p,int upd){
        d[p].delet(a[pos]);d[p].insert(upd);
        if(l == r && l == pos){a[pos] = upd;return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
    }
    int rnk(int l,int r,int s,int t,int p,int x){
        if(s <= l && r <= t){return d[p].rks(x) - 1;}
        int mid = l + r >> 1;
        if(t <= mid)return rnk(l,mid,s,t,p << 1,x);
        if(mid < s)return rnk(mid + 1,r,s,t,p << 1 | 1,x);
        return rnk(l,mid,s,t,p << 1,x) + rnk(mid + 1,r,s,t,p << 1 | 1,x);
    }
    int mxrnk(int l,int r,int s,int t,int p,int x){
        if(s <= l && r <= t){return d[p].mxrks(x) - 1;}
        int mid = l + r >> 1;
        if(t <= mid)return mxrnk(l,mid,s,t,p << 1,x);
        if(mid < s)return mxrnk(mid + 1,r,s,t,p << 1 | 1,x);
        return mxrnk(l,mid,s,t,p << 1,x) + mxrnk(mid + 1,r,s,t,p << 1 | 1,x);
    }
    int pre(int l,int r,int s,int t,int p,int x){
        if(s <= l && r <= t){return d[p].pre(x);}
        int mid = l + r >> 1;
        if(t <= mid)return pre(l,mid,s,t,p << 1,x);
        if(mid < s)return pre(mid + 1,r,s,t,p << 1 | 1,x);
        return max(pre(l,mid,s,t,p << 1,x) , pre(mid + 1,r,s,t,p << 1 | 1,x));
    }
    int suf(int l,int r,int s,int t,int p,int x){
        if(s <= l && r <= t){return d[p].suf(x);}
        int mid = l + r >> 1;
        if(t <= mid)return suf(l,mid,s,t,p << 1,x);
        if(mid < s)return suf(mid + 1,r,s,t,p << 1 | 1,x);
        return min(suf(l,mid,s,t,p << 1,x) , suf(mid + 1,r,s,t,p << 1 | 1,x));
    }
public:
    void build(){build(1,n,1);}
    int rks(int l,int r,int x){return rnk(1,n,l,r,1,x);}
    int mxrks(int l,int r,int x){return mxrnk(1,n,l,r,1,x);}
    int pos(int s,int t,int x){
        int l = 0, r = 1e8, mid = 0;
        while(l < r){
            mid = l + r + 1 >> 1;
            if(mxrks(s,t,mid) < x)l = mid;
            else r = mid - 1;
        }
        return r;
    }
    void update(int pos,int x){update(1,n,pos,1,x);}
    int pre(int l,int r,int x){return pre(1,n,l,r,1,x);}
    int suf(int l,int r,int x){return suf(1,n,l,r,1,x);}
}tree;

signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    tree.build(); int opt, u, v;
    for(int i = 1;i <= m;i++){
        opt = read(); u = read(); v = read();
        switch(opt){
            case 1: printf("%d\n",tree.rks(u,v,read()));break;
            case 2: printf("%d\n",tree.pos(u,v,read()));break;
            case 3: tree.update(u,v);break;
            case 4: printf("%d\n",tree.pre(u,v,read()));break;
            case 5: printf("%d\n",tree.suf(u,v,read()));break;
            default:break;
        }
    }
    return 0;
}