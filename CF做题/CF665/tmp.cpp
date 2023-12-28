#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n, a[maxn], c[maxn], K;

int trie[maxn * 30][2], tot = 1;
ll cnt[maxn * 30];
void insert(int x){
    int u = 1;
    // printf("x=%d\n",x);
    for(int i = 31;i + 1;i--){
        bool v = x >> i;
        if(!trie[u][v])trie[u][v] = ++tot;
        u = trie[u][v];cnt[u]++;
        // printf("u=%d->",u);
    }
    // printf("u=%d\n",u);
}
ll query(int x,int k){
    int u = 1;ll ans = 0;
    for(int i = 31;i + 1;i--){
        bool v = (x >> i) & 1, ki = (k >> i) & 1;
        if(!ki){
            if(!v){
                ans += cnt[trie[u][1]];
                u = trie[u][0];
            }
            else{
                ans += cnt[trie[u][0]];
                u = trie[u][1];
            }
        }
        else{u = trie[u][!v];}
    }
    return ans;
}
int res[maxn];
signed main(){
    freopen("tmp.out","w",stdout);
    n = read(); K = read();
    for(int i = 1;i <= n;i++){a[i] = read(); c[i] = c[i - 1] ^ a[i];}
    ll ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < i;j++){
            if((c[j] ^ c[i]) >= K){
                ans++;res[i]++;
            }
        }
    }
    for(int i = 0;i <= n;i++){printf("%d\n",res[i]);}
    printf("%lld\n",ans);
    return 0;
}