#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, q;
int a[maxn];

class Segment_Tree{
private:
    struct node{
        vector<int> minn; node(){}
        node(int x){minn.push_back(x);}
        node(vector<int> vec):minn(vec){}
    }d[maxn << 2];
    node mergenode(node l,node r){
        vector<int> vec;
        for(int i : r.minn)l.minn.push_back(i);
        sort(l.minn.begin(),l.minn.end());
        for(int i = 0;i < 31 && i < l.minn.size();i++)
            vec.push_back(l.minn[i]);
        return node(vec);
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(a[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
public:
    void build(){build(1,n,1);}
    vector<int> query(int s,int t){return query(1,n,s,t,1).minn;}
}tree;

signed main(){
int T = read();
while(T--){
    n = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    tree.build();
    q = read();int l, r;
    for(int i = 1;i <= q;i++){
        l = read(); r = read();
        int ans = 0x3f3f3f3f3f3f;
        vector<int> vec = tree.query(l,r);
        for(int i = 0;i < vec.size();i++)
            for(int j = 0;j < vec.size();j++){
                if(i == j)continue;
                ans = min(ans,vec[i] | vec[j]);
            }
        printf("%lld\n",ans);
    }
}
    return 0;
}