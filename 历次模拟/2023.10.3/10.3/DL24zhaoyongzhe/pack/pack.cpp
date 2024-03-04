#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
struct node{
    int cost, val;
    node(int c = 0,int v = 0):cost(c),val(v){}
    friend bool operator < (node a,node b){return a.cost == b.cost ? a.val  > b.val : a.cost > b.cost;}
}a[maxn];
int val[maxn];
signed main(){
    freopen("pack.in","r",stdin);
    freopen("pack.out","w",stdout);
    n = read();m = read(); int u, v;
    for(int i = 1;i <= n;i++){
        u = read(); v = read();
        a[i] = node(u, v);
    }
    int pack = 0, ans = 0;
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++)val[n - i + 1] = a[i].cost;
    for(int i = 1; i<= m;i++){
        pack = read();ans = 0;
        // for(int j = 1;j <= n;j++){
        //     if(pack >= a[j].cost){
        //         pack -= a[j].cost;
        //         ans += a[j].val;
        //     }
        // }
        int j = n, cnt = 0;
        while(1){
            j = upper_bound(val + 1,val + j + 1,pack) - val - 1;
            if(j <= 0)break;
            pack -= a[n - j + 1].cost;ans += a[n - j + 1].val;j--;
            // printf("::%lld-%lld+1=%lld,%lld,pack=%lld\n",n,j,n - j + 1,j,pack);
            // cnt++;if(cnt >= 10){getchar();cnt = 0;}
        }
        printf("%lld\n",ans);
    }
    return 0;
}