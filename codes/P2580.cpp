#include<bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 1e4 + 10, maxm = 1e5 + 10;
int trie[maxm * 80][26], tot;
int cnt[maxm * 80];bool book[maxm * 80];
char ch[51];
void insert(char *s){
    int len = strlen(s);
    int u = 0, v = 0;
    for(int i = 0;i < len;i++){
        v = s[i] - 'a';
        if(!trie[u][v])trie[u][v] = ++tot;
        u = trie[u][v];
    }
    book[u] = true;
}
int find(char *s){
    int len = strlen(s);
    int u = 0, v = 0;
    for(int i = 0;i < len;i++){
        v = s[i] - 'a';
        if(!trie[u][v])return 2;
        u = trie[u][v];
    }
    cnt[u]++;
    if(!book[u])return 2;
    if(cnt[u] > 1)return 3;
    return 1;
}
signed main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%s",ch);
        insert(ch);
    }
    scanf("%d",&m);
    for(int i = 1;i <= m;i++){
        scanf("%s",ch);
        switch(find(ch)){
            case 1:{puts("OK"); break;}
            case 2:{puts("WRONG"); break;}
            case 3:{puts("REPEAT"); break;}
            default:{break;}
        }
    }
    return 0;
}