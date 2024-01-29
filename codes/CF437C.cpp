#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int val[maxn];
int n, m;
signed main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        scanf("%d",&val[i]);
    }
    int ans = 0, u, v;
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&u,&v);
        ans += min(val[u],val[v]);
    }
    printf("%d\n",ans);
    return 0;
}