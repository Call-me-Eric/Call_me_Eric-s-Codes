#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n;

ll res[33], rev[33];
int trie[maxn * 31][2], tot = 1;
ll cnt[maxn * 31];
void insert(int x){
    int u = 1;
    for(int i = 31;i + 1;i--){
        bool v = (x >> i) & 1;
        if(!trie[u][v])trie[u][v] = ++tot;
        if(!v)rev[i] += cnt[trie[u][1]];
        else res[i] += cnt[trie[u][0]];
        u = trie[u][v];cnt[u]++;
    }
}

signed main(){
    n = read();int x = 0;ll ans = 0;
    for(int i = 1;i <= n;i++)insert(read());
    for(int i = 31;i + 1;i--){
        if(rev[i] > res[i]){
            x |= (1 << i);
            ans += res[i];
        }
        else ans += rev[i];
    }
    printf("%lld %d\n",ans,x);
    return 0;
}