#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n;
char ch[maxn];
int trie[maxn][2], dep[maxn], tot;
int ed[maxn];
void insert(char *s){
    int n = strlen(s + 1), u = 1;
    for(int i = 1;i <= n;i++){
        int v = s[i] - '0';
        if(!trie[u][v]){trie[u][v] = ++tot;dep[tot] = dep[u] + 1;}
        u = trie[u][v];
    }
    ed[u]++;
}
long long ans;
typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> > que[maxn];
void dfs(int u){
    int l = trie[u][0], r = trie[u][1];
    if(l)dfs(l);    if(r)dfs(r);
    if(!l && !r){que[u].push(make_pair(dep[u] + 2,1));ed[u]--;}
    else if(!l || !r){swap(que[u],que[l | r]);que[u].push(make_pair(dep[u] + 1,2));}
    else{
        int x = 0;
        if(que[l].size() < que[r].size()){swap(que[u],que[r]);x = l;}
        else{swap(que[u],que[l]);x = r;}
        while(!que[x].empty()){que[u].push(que[x].top());que[x].pop();}
    }
    while(ed[u]--){
        pii tmp = que[u].top();que[u].pop();
        int k = tmp.first, typ = tmp.second;
        ans += k - dep[u];
        if(typ == 1){que[u].push(make_pair(k + 1,1));que[u].push(make_pair(k + 1,1));}
        else que[u].push(make_pair(k + 2,1));
    }
}
void main(){
    n = read();dep[1] = 0;tot = 1;
    for(int i = 1;i <= n;i++){scanf("%s",ch + 1);insert(ch);}
    dfs(1);printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}