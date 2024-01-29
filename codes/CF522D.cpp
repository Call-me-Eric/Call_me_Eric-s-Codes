#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, m, a[maxn];
class Segment_Tree{
private:
    struct node{
        int minn;
        node(int minn = 0):minn(minn){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(min(l.minn,r.minn));}
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p] = node(upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(0x3f3f3f3f);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
public:
    void update(int pos,int upd){update(1,n,pos,1,upd);}
    int query(int l,int r){return query(1,n,l,r,1).minn;}
    void build(){build(1,n,1);}
}tree;
int tot;map<int,int> mp;
int col[maxn];
vector<pair<int,int> > q[maxn];
int ans[maxn];
signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();
        if(!mp[a[i]])mp[a[i]] = ++tot;
        a[i] = mp[a[i]];
    }
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        q[u].push_back(make_pair(v, i));
    }
    tree.build();
    for(int i = 1;i <= tot;i++)col[i] = n + 1;
    // for(int i = 1;i <= n;i++){printf("a[%d]=%d\n",i,a[i]);}
    for(int i = n;i;i--){
        if(col[a[i]] != n + 1){tree.update(col[a[i]],col[a[i]] - i);}
        col[a[i]] = i;
        if(q[i].size()){
            for(auto j : q[i]){
                ans[j.second] = tree.query(i,j.first);
                if(ans[j.second] == 0x3f3f3f3f)ans[j.second] = -1;
            }
        }
    }
    for(int i = 1;i <= m;i++)printf("%d\n",ans[i]);
    return 0;
}