#include<bits/stdc++.h>
using namespace std;
int n, m, maxR;
int mincost = 0x3f3f3f3f;
int minv[20], mins[20];
void dfs(int step,int lastr,int lasth,int V,int S){
    if(step == 0){
        if(V == n && S < mincost) mincost = S;
        return;
    }
    if(S + 2 * (n - V) / lastr >= mincost)return;
    if(V + minv[step] > n)return;
    if(S + mins[step] > mincost)return;
    for(int i = lastr - 1;i >= step;i--){
        if(step == m)S = i * i;
        for(int j = min(lasth - 1,(n - V - minv[step - 1]) / (i * i));j >= step;j--){
            dfs(step - 1, i, j, V + i * i * j, S + 2 * i * j);
        }
    }
}
signed main(){
    scanf("%d%d",&n,&m);
    maxR = sqrt(n);
    for(int i = 1;i <= m;i++){
        minv[i] = minv[i - 1] + i * i * i;
        mins[i] = mins[i - 1] + 2 * i * i;
    }
    dfs(m,maxR,n,0,0);
    printf("%d\n",mincost == 0x3f3f3f3f ? 0 : mincost);
    return 0;
}