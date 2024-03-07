#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 10;
int n, m;
int opt[maxn], x[maxn], y[maxn];
int tmp[maxn], a[maxn];
struct tree_array{
    int c[maxn];
    void add(int x,int val){for(;x <= m + 1;x += (-x) & x)c[x] += val;}
    int query(int x){int ans = 0;for(;x;x -= (-x) & x)ans += c[x];return ans;}
}arr1,arr2;
signed main(){
    scanf("%d%d",&n,&m);
    char op = ' ';int u, v;
    for(int i = 1;i <= m;i++){
        op = ' ';
        while(op == ' ' || op == '\n')op = getchar();
        scanf("%d%d",&u,&v);
        opt[i] = op == 'Z'; x[i] = u;tmp[i] = y[i] = v;
    }
    tmp[m + 1] = 0;
    sort(tmp + 1,tmp + 2 + m);
    int tot = unique(tmp + 1,tmp + 2 + m) - tmp - 1;
    for(int i = 1;i <= m;i++){
        if(!opt[i]){
            u = lower_bound(tmp + 1,tmp + 1 + tot,a[x[i]]) - tmp;
            v = lower_bound(tmp + 1,tmp + 1 + tot,y[i]) - tmp;
            arr1.add(u,-1);arr1.add(v,1);
            arr2.add(u,-a[x[i]]);arr2.add(v,y[i]);
            a[x[i]] = y[i];
        }
        else{
            u = lower_bound(tmp + 1,tmp + 1 + tot,y[i]) - tmp;
            if(y[i] * (arr1.query(m + 1) - arr1.query(u - 1)) + arr2.query(u - 1) >= y[i] * x[i])
                puts("TAK");
            else{puts("NIE");}
        }
    }
    return 0;
}