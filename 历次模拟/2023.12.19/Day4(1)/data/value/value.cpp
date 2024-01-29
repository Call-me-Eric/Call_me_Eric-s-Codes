#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
struct node{
    int x, y;
    node(int x = 0,int y = 0):x(x),y(y){}
    friend bool operator < (node a,node b){
        return a.x != b.x ? a.x < b.x : a.y > b.y;
    }
}a[maxn];
int n;
vector<int> X, Y;
struct BIT{
    int c[maxn << 2];
    inline int lowbit(int x){return x & (-x);}
    int qry(int x){int ans = 0;for(;x > 0;x -= lowbit(x))ans += c[x];return ans;}
    void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] += add;}
}tree;
vector<int> vec[maxn];
int sum[maxn];
int calcy(int i,int j){
    return Y[j] * (n - sum[i] - tree.qry(j - 1));
}
signed main(){
    // freopen("value.in","r",stdin);
    // freopen("value.out","w",stdout);
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
    int ypos = 1, ans = 0;
    for(int i = 1;i < X.size();i++){
        for(int k = max(1LL,ypos - 200), r = min((int)Y.size() - 1,ypos + 200);k <= r;k++)
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