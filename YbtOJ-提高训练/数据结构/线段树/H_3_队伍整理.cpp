#include<bits/stdc++.h>
#define int long long

using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, cnt;
const int maxx = 1e8 + 10,maxn = 8e5 + 10, INF = 0x3f3f3f3f;
int a[maxn];
map<int,int> pos;
int sum[maxn];
class Segment_tree{
    private:
    int tr[maxn];
    int pushup(int p){return min(tr[p << 1],tr[p << 1 | 1]);}
    void build(int l,int r,int p){
        if(l == r){
            if(l > n)tr[p] = INF;
            else tr[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        tr[p] = pushup(p);
    }
    void update(int x,int l,int r,int p,int change){
        if(l == r && x == l){tr[p] = change;return;}
        if(l == r)return;
        int mid = (l + r) >> 1;
        if(x <= mid)update(x,l,mid,p << 1,change);
        else update(x,mid + 1,r,p << 1 | 1,change);
        tr[p] = pushup(p);
    }
    int query(int l,int r,int L,int R,int p){
        if(r < l)return INF;
        if(L <= l && r <= R)return tr[p];
        int mid = (l + r) >> 1, res = INF;
        if(L <= mid)res = min(res,query(l,mid,L,R,p << 1));
        if(mid < R)res = min(res,query(mid + 1,r,L,R,p << 1 | 1));
        return res;
    }
    public:
    int query(int x){return query(1,n + m,1,x,1);}
    void build(){build(1,n + m,1);}
    void update(int x,int change){update(x,1,n + m,1,change);}
}tree;
signed main(){
    scanf("%lld%lld",&n,&m);
    cnt = n;
    char ch[5];int x;
    for(int i = 1;i <= n + m;i++)a[i] = INF;
    for(int i = 1;i <= n;i++){scanf("%lld",&a[i]);pos[a[i]] = i;}
    tree.build();
    for(int i = 1;i <= m;i++){
        scanf("%s%lld",ch,&x);
        if(ch[0] == 'M'){
            int tmp = pos[x];cnt++;
            tree.update(tmp,INF);
            tree.update(cnt,x);
            pos[x] = cnt;
        }
        else{
            if(!pos[x])puts("-1");
            else{
                int tmp = tree.query(pos[x] - 1);
                if(tmp == INF)puts("-1");
                else printf("%lld\n",tmp);
            }
        }
    }
    for(int i = 1;i <= n;i++)sum[pos[a[i]]] = 1;
    for(int i = 1;i <= m + n;i++){sum[i] += sum[i - 1];}
    int ans = 0;
    for(int i = 1;i <= m;i++){ans = max(sum[i + n - 1] - sum[i - 1],ans);}
    printf("%lld\n",n - ans);
    return 0;
}