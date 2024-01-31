#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 7100;
bool ans[maxn][2], vis[maxn][2];
int cnt[maxn][2];
int n;
vector<int> s[2];
void dfs(int u,int opt){
    // printf("%d %d\n",u,opt);
    if(vis[u][opt])return; vis[u][opt] = 1;
    for(int i : s[opt ^ 1]){
        int to = (u - i + n - 1) % n + 1;
        // printf("%d %d %d\n",u,to,i);
        if(to != 1){
            if(!ans[u][opt]){
                ans[to][opt ^ 1] = 1;
                dfs(to,opt ^ 1);
            }
            else if((++cnt[to][opt ^ 1]) == s[opt ^ 1].size()){
                ans[to][opt ^ 1] = 0;
                dfs(to,opt ^ 1);
            }
        }
    }
}
signed main(){
    n = read();
    for(int j = 0;j <= 1;j++)for(int i = read();i;i--)s[j].push_back(read());
    dfs(1, 0);dfs(1, 1);
    for(int i = 0;i <= 1;i++){
        for(int j = 2;j <= n;j++){
            printf(vis[j][i] ? (ans[j][i] ? "Win" : "Lose") : "Loop");
            putchar(' ');
        }
        puts("");
    }
    return 0;
}