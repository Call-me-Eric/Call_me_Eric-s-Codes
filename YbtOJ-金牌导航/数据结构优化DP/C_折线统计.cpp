#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10, mod = 1e5 + 7;
int n, k;
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] = (c[x] + add) % mod;}
    int qry(int x){int ans = 0;for(;x;x -= lowbit(x))ans = (ans + c[x]) % mod;return ans;}
    void clear(){for(int i = 1;i <= n;i++)c[i] = 0;}
}tr[2];//[][0]=up,[][1]=down

struct node{
    int x, y;
    node(int x = 0,int y = 0):x(x),y(y){}
    friend bool operator < (node a,node b){return a.x < b.x;}
}a[maxn];
vector<int> X, Y;

int f[maxn][11][2];

signed main(){
    n = read(); k = read();
    for(int i = 1;i <= n;i++){
        a[i].x = read();
        Y.push_back(a[i].y = read());
    }
    sort(Y.begin(),Y.end());Y.erase(unique(Y.begin(),Y.end()),Y.end());
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++){
        a[i].y = lower_bound(Y.begin(),Y.end(),a[i].y) - Y.begin() + 1;
        f[i][0][0] = f[i][0][1] = 1;
    }
    int ans = 0;
    for(int j = 1;j <= k;j++){
        tr[0].clear();tr[1].clear();
        for(int i = 1;i < n;i++){
            tr[0].upd(a[i].y,f[i][j][0] + f[i][j - 1][1]);
            tr[1].upd(a[i].y,f[i][j][1] + f[i][j - 1][0]);
            f[i + 1][j][0] = tr[0].qry(a[i + 1].y - 1);
            f[i + 1][j][1] = (tr[1].qry(n) - tr[1].qry(a[i + 1].y) + mod) % mod;
        }
    }
    for(int i = 1;i <= n;i++){ans = (ans + f[i][k][0] + f[i][k][1]) % mod;}
    printf("%d\n",ans % mod);
    return 0;
}