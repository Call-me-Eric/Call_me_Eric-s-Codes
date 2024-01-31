#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int q;

int trie[maxn * 80][2], tot = 1;
int cnt[maxn * 80];
void update(int x,int add){
    int u = 1;
    for(int i = 31;i + 1;i--){
        bool v = x & (1 << i);
        if(!trie[u][v])trie[u][v] = ++tot;
        cnt[trie[u][v]] += add;
        u = trie[u][v];
    }
}
int query(int x,int l){
    int u = 1, res = 0;
    for(int i = 31;i + 1;i--){
        bool v = x & (1 << i);
        if(l & (1 << i))res += cnt[trie[u][v]],u = trie[u][v ^ 1];
        else u = trie[u][v];
    }
    return res;
}

signed main(){
    q = read();int opt, u;
    for(int i = 1;i <= q;i++){
        opt = read(); u = read();
        if(opt == 1)update(u, 1);
        if(opt == 2)update(u,-1);
        if(opt == 3)printf("%lld\n",query(u,read()));
    }
    return 0;
}