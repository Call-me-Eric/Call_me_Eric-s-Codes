#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n;
int fa[maxn], dist[maxn];
int minn = 0x3f3f3f3f;
int getf(int x){if(fa[x] != x){int tmp = fa[x]; fa[x] = getf(fa[x]); dist[x] += dist[tmp];}return fa[x];}
signed main(){
    scanf("%d",&n); int t;
    for(int i = 1;i <= n;i++)fa[i] = i;
    for(int i = 1;i <= n;i++){
        scanf("%d",&t);
        int fi = getf(i), ft = getf(t);
        if(fi != ft){fa[fi] = ft; dist[i] = dist[t] + 1;}
        else minn = min(minn,dist[i] + dist[t] + 1);
    }
    printf("%d\n",minn);
    return 0;
}