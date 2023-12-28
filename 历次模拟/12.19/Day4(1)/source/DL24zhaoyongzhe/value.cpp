#include<bits/stdc++.h>
using namespace std;
inline long long read(){
    long long x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
struct node{
    long long x, y;
    node(long long x = 0,long long y = 0):x(x),y(y){}
    friend bool operator < (node a,node b){
        return a.x != b.x ? a.x < b.x : a.y > b.y;
    }
}a[maxn];
int n;
vector<long long> X, Y;
struct BIT{
    long long c[maxn << 2];
    inline long long lowbit(int x){return x & (-x);}
    long long qry(int x){int ans = 0;for(;x > 0;x -= lowbit(x))ans += c[x];return ans;}
    void upd(int x,long long add){for(;x <= n;x += lowbit(x))c[x] += add;}
}tree;
vector<int> vec[maxn];
long long sum[maxn];
long long calcy(int i,int j){
    return Y[j] * (n - sum[i] - tree.qry(j - 1));
}
signed main(){
    freopen("value.in","r",stdin);
    freopen("value.out","w",stdout);
    n = read();
    for(int i = 1;i <= n;i++){
        X.push_back(a[i].x = read());
        Y.push_back(a[i].y = read());
    }
    X.push_back(-114514);Y.push_back(-114514);
    sort(X.begin(),X.end());sort(Y.begin(),Y.end());sort(a + 1,a + 1 + n);
    X.erase(unique(X.begin(),X.end()),X.end());Y.erase(unique(Y.begin(),Y.end()),Y.end());
    for(int i = 1;i <= n;i++){
        a[i].x = lower_bound(X.begin(),X.end(),a[i].x) - X.begin();
        a[i].y = lower_bound(Y.begin(),Y.end(),a[i].y) - Y.begin();
        vec[a[i].x].push_back(a[i].y);
    }
    for(int i = X.size() - 1;i;i--){sum[i] = sum[i + 1] + vec[i].size();}
    long long ans = 0;int ypos = 1;
    for(int i = 1;i < X.size();i++){
        for(int k = max(1,ypos - 200), r = min((int)Y.size() - 1,ypos + 200);k <= r;k++)
            if(calcy(i,ypos) < calcy(i,k))
                ypos = k;
        ans = max(ans,calcy(i,ypos) + X[i] * sum[i]);
        for(int j : vec[i]){
            tree.upd(j,1);
            ypos = calcy(i + 1,ypos) > calcy(i + 1,j) ? ypos : j;
        }
        // printf("%lld %lld %lld\n",i,ypos,calcy(i,ypos));
    }
    printf("%lld\n",ans);
    return 0;
}