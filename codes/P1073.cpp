#include<bits/stdc++.h>
using namespace std;
int n, m;
const int inf = 0x3f3f3f3f;
const int maxn = 100010;
int C[maxn];
vector<int> e[maxn];
int minn[maxn];
int f[maxn];
void dfs(int x,int minx,int pre){//TODO dfs()
    bool flag = 1;
    minx = min(minx,C[x]);
    if(minn[x] > minx){
        minn[x] = minx;
        flag = 0;
    }
    int maxx = max(f[pre],C[x] - minx);
    if(maxx > f[x]){
        f[x] = maxx;
        flag = 0;
    }
    if(flag)return;
    for(int i = 0,len = e[x].size();i < len;i++){
        dfs(e[x][i],minx,x);
    }
}
int main(){//TODO main()
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        scanf("%d",&C[i]);
        minn[i] = inf;
    }
    int x, y, z;
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&x,&y,&z);
        e[x].push_back(y);
        if(z == 2){
            e[y].push_back(x);
        }
    }
    dfs(1,inf,0);
    printf("%d\n",f[n]);
    return 0;
}