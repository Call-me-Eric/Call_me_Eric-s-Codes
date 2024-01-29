#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int trie[maxn << 6][2], tot;
int cnt[maxn << 6], history[maxn << 2];
int n, m;
int sum, a[maxn];
void insert(int x,int ver){
    history[ver] = ++tot;
    int u = history[ver], w = history[ver - 1];
    for(int i = 25;i + 1;i--){
        bool v = (x >> i) & 1;
        trie[u][v] = ++tot;
        trie[u][!v] = trie[w][!v];
        u = trie[u][v]; w = trie[w][v];
        cnt[u] = cnt[w] + 1;
    }
}
int query(int l,int r,int x){
    int u1 = history[l], u2 = history[r],ans = 0;
    for(int i = 25;i + 1;i--){
        bool v = ((x >> i) & 1);
        int tmp = cnt[trie[u2][!v]] - cnt[trie[u1][!v]];
        if(tmp > 0){ans += (1 << i);v = !v;}
        u1 = trie[u1][v];u2 = trie[u2][v];
    }
    return ans;
}
signed main(){
    scanf("%d%d",&n,&m);
    insert(0,0);
    for(int i = 1;i <= n;i++){
        int tmp; scanf("%d",&tmp);
        sum ^= tmp;
        insert(sum, i);
    }
    char opt = ' ';int u, v, w;
    for(int i = 1;i <= m;i++){
        scanf(" %c",&opt);
        scanf("%d",&u);
        if(opt == 'A'){
            sum ^= u;
            insert(sum,n + 1);
            n++;
        }
        else if(opt == 'Q'){
            scanf("%d%d",&v,&w);
            int tmp = sum ^ w;
            u--; v--;
            printf("%d\n",query(u - 1,v,tmp));
        }
    }
    return 0;
}