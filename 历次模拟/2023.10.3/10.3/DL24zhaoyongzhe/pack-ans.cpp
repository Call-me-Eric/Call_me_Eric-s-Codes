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
    friend bool operator < (node a,node b){return a.cost == b.cost ? a.val < b.val : a.cost < b.cost;}
}a[maxn];
int val[maxn], cost[maxn];
int pack, ans;
int solve(int r){
    int l = 1;
    while(l < r){
        int mid = l + r + 1 >> 1;
        if(a[mid].cost <= pack){l = mid;}
        else r = mid - 1;
    }
    return l;
}
int solve1(int i){
    int l = 0, r = i - 1;
    while(l < r){
        int mid = l + r >> 1;
        // printf("%lld %lld %lld\n",l,r,mid);
        if(cost[i] - cost[mid] <= pack){r = mid;}
        else l = mid + 1;
    }
    return l;
}
signed main(){
    n = read();m = read(); int u, v;
    for(int i = 1;i <= n;i++){
        u = read(); v = read();
        a[i] = node(u, v);
    }
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++){
        val[i] = val[i - 1] + a[i].val;
        cost[i] = cost[i - 1] + a[i].cost;
    }
    while(m--){
        pack = read(); ans = 0;
        int i = n, j = n;
        while(i && pack >= a[1].cost){
            i = solve(i);
            j = solve1(i);
            pack -= cost[i] - cost[j];
            ans += val[i] - val[j];
            i = j;
        }
        printf("%lld\n",ans);
    }
    return 0;
}