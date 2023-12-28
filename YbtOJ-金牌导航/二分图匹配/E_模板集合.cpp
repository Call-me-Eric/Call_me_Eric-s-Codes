#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e3 + 10, INF = 0x3f3f3f3f;

int n, m;
char ch[21];
int a[maxn], cnt;
vector<int> edg[maxn];

int match[maxn];
bool vis[maxn];
bool dfs(int u){
    if(vis[u])return false;vis[u] = 1;
    for(int v : edg[u]){
        if(!match[v] || dfs(match[v])){
            match[v] = u;match[u] = v;
            return true;
        }
    }
    return false;
}

int popcount(int x){
    int res = 0;
    while(x){res += (x & 1);x >>= 1;}
    return res;
}
bool book[maxn];

signed main(){
while((m = read()) | (n = read())){
    cnt = 0;
    for(int i = 1;i <= n;i++){
        scanf("%s",ch);int pos = -1, tmp = 0;
        for(int j = 0;j < m;j++){
            if(ch[j] == '1'){tmp |= (1 << j);}
            if(ch[j] == '*'){pos = j;}
        }
        a[++cnt] = tmp;
        if(pos != -1)a[++cnt] = tmp | (1 << pos);
    }
    n = cnt; sort(a + 1,a + 1 + n);
    n = unique(a + 1,a + 1 + n) - a - 1;
    for(int i = 1;i <= n;i++){edg[i].clear(),match[i] = 0;book[i] = popcount(a[i]) & 1;}
    for(int i = 1;i <= n;i++){
        if(book[i])
        for(int j = 1;j <= n;j++){
            if(i == j || book[j])continue;
            int x = a[i] ^ a[j];
            if(popcount(x) > 1)continue;
            edg[i].push_back(j);
        }
    }
    cnt = 0;
    for(int i = 1;i <= n;i++){
        memset(vis,0,sizeof(vis));
        if(!match[i]) cnt += dfs(i);
    }
    // printf("n = %d\n", n);
    // for(int i = 1;i <= n;i++){
    //     printf("i = %d, a[i] = %d, match[i]=%d\n",i,a[i],match[i]);
    // }
    printf("%d\n",n - cnt);
}
    return 0;
}