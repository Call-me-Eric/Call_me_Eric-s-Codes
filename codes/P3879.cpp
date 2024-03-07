#include<bits/stdc++.h>
using namespace std;
int trie[500010][26], tot;
const int maxn = 1e3 + 10, maxm = 1e4 + 10;
int n, m;
bitset<1001> book[500010];
int x; char ch[30];
void insert(int p){
    scanf("%s",ch);
    int u = 0, len = strlen(ch);
    for(int i = 0;i < len;i++){
        int v = ch[i] - 'a';
        if(!trie[u][v])trie[u][v] = ++tot;
        u = trie[u][v];
    }
    book[u][p] = true;
}
void find(){
    scanf("%s",ch);
    int u = 0, len = strlen(ch);
    for(int i = 0;i < len;i++){
        int v = ch[i] - 'a';
        if(!trie[u][v]){
            puts("");
            return;
        }
        u = trie[u][v];
    }
    for(int i = 1;i <= n;i++)
        if(book[u][i])printf("%d ",i);
    puts("");
}
signed main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&x);
        for(int j = 1;j <= x;j++)
            insert(i);
    }
    scanf("%d",&m);
    for(int i = 1;i <= m;i++)find();
    return 0;
}