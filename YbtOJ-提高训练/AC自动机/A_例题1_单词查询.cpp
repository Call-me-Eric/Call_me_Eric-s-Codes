#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
char ch[maxn * 100];
int n, ed[maxn * 100];
int trie[maxn * 100][26], tot = 1;
queue<int> que;
int fail[maxn * 100];
void insert(char *s){
    int u = 0, len = strlen(s + 1);
    for(int i = 1;i <= len;i++){
        int v = s[i] - 'a';
        if(!trie[u][v]){trie[u][v] = ++tot;}
        u = trie[u][v];
    }
    ed[u]++;
}
int query(char *s){
    int u = 0, len = strlen(s + 1), ans = 0, k = 0;
    for(int i = 1;i <= len;i++){
        int v = s[i] - 'a'; u = trie[u][v];
        for(int j = u;j && ed[j] != -1;j = fail[j]){
            ans += ed[j];ed[j] = -1;
        }
    }
    return ans;
}
signed main(){
    int T;scanf("%d",&T);
    while(T--){
        tot = 0;
        memset(ed,0,sizeof(ed));
        memset(fail,0,sizeof(fail));
        memset(trie,0,sizeof(trie));
        scanf("%d",&n);
        for(int i = 1;i <= n;i++){
            scanf("%s",ch + 1);
            insert(ch);
        }
        //bfs
        queue<int> que;fail[1] = 0;
        for(int i = 0;i < 26;i++){if(trie[0][i])que.push(trie[0][i]);}
        while(!que.empty()){
            int u = que.front();que.pop();
            for(int v = 0;v < 26;v++){
                if(!trie[u][v])trie[u][v] = trie[fail[u]][v];
                else{
                    que.push(trie[u][v]);
                    fail[trie[u][v]] = trie[fail[u]][v];
                }
            }
        }
        //
        scanf("%s",ch + 1);
        printf("%d\n",query(ch));
    }
    return 0;
}