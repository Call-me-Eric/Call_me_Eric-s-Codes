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
        bool v = (x >> i) & 1;
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
        if(!ki){ans += cnt[trie[u][!v]];u = trie[u][v];}
        else{u = trie[u][!v];}
    }
    return ans;
}

signed main(){
    // freopen("CF665E.out","w",stdout);
    n = read(); K = read();
    for(int i = 1;i <= n;i++){a[i] = read(); c[i] = c[i - 1] ^ a[i];}
    ll ans = 0;
    // for(int i = 1;i <= 40;i++)printf("cnt[%d]=%lld\n",i,cnt[i]);
    for(int i = 0;i <= n;i++){
        ll tmp = query(c[i],K - 1);
        // printf("%lld\n",tmp);
        ans += tmp; insert(c[i]);
    }
    printf("%lld\n",ans);
    return 0;
}