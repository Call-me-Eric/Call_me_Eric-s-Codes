#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n;
int a, b, c, d;
ll x[maxn], y[maxn];
ll u[maxn], v[maxn];
pair<int,int> s[maxn];

struct Segment_Tree{
    int tot;
    struct node{
        int maxx;
        node(int maxx = 0):maxx(maxx){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx));}
    void build(int l,int r,int p){
        if(l == r){d[p] = node();return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p].maxx = max(upd,d[p].maxx);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void build(int x){tot = x;build(1,tot,1);}
    void update(int pos,int upd){update(1,tot,pos,1,upd);}
    int query(int s,int t){if(s > t)return 0;return query(1,tot,s,t,1).maxx;}
}tree;

signed main(){
    n = read();scanf("%d/%d",&b,&a); scanf("%d/%d",&d,&c);
    for(int i = 1;i <= n;i++){
        x[i] = read(); y[i] = read();
        u[i] = -(ll)y[i] * c + x[i] * d;
        v[i] = -(ll)x[i] * b + y[i] * a;
        if(u[i] < 0 || v[i] < 0){n--;i--;continue;}
        // printf("i = %d, u = %lld, v = %lld\n",i,x[i],y[i]);
        x[i] = u[i]; y[i] = v[i];
    }
    if(n == 0){puts("0");return 0;}
    // printf("n = %d\n", n);
    sort(x + 1,x + 1 + n);int totx = unique(x + 1,x + 1 + n) - x - 1;
    sort(y + 1,y + 1 + n);int toty = unique(y + 1,y + 1 + n) - y - 1;
    for(int i = 1;i <= n;i++){
        u[i] = lower_bound(x + 1,x + 1 + totx,u[i]) - x;
        v[i] = lower_bound(y + 1,y + 1 + toty,v[i]) - y;
        s[i] = make_pair(u[i],v[i]);
        // printf("i = %d, u = %d, v = %d\n",i,s[i].first,s[i].second);
    }
    sort(s + 1,s + 1 + n,[](pair<int,int> a,pair<int,int> b)
    {return a.first != b.first ? a.first < b.first : a.second > b.second;});
    tree.build(toty);int ans = 0;
// puts("1111111");
    for(int i = 1;i <= n;i++){
        int cnt = 1 + tree.query(1,s[i].second - 1);
        ans = max(ans,cnt);
        tree.update(s[i].second,cnt);
    }
    printf("%d\n",ans);
    return 0;
}