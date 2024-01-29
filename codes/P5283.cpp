#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
    ll x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = - 1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
const ll maxx = (1LL << 32LL) - 1;
int n, k;
ll a[maxn];

struct Trie{
    int trie[maxn * 50][2], tot = 1;
    int cnt[maxn * 50];
    void insert(ll x){
        int u = 1;
        for(ll i = 33;i + 1;i--){
            bool v = (x >> i) & 1LL;
            if(!trie[u][v])trie[u][v] = ++tot;
            u = trie[u][v];cnt[u]++;
        }
    }
    ll query(ll x,int k){
        ll ans = 0;int u = 1;
        for(ll i = 33;i + 1;i--){
            bool v = (x >> i) & 1LL;
            // printf("cnt[trie[%d][%d]] = %d, k = %d\n",u,v,cnt[trie[u][v]],k);
            if(k > cnt[trie[u][v]]){k -= cnt[trie[u][v]];u = trie[u][!v];ans |= (1LL << i);}
            else{u = trie[u][v];}
        }
        // printf("%lld %lld %d\n",x,ans,k);
        return ans;
    }
    void DEBUG(){for(int i = 1;i <= 30;i++){printf("cnt[%d] = %d\n",i,cnt[i]);}}
}trie;

struct node{
    int id, rks;ll val;
    node(ll val = 0,int id = 0, int rks = 0):val(val),id(id),rks(rks){}
    friend bool operator < (node a,node b){return a.val < b.val;}
    friend bool operator > (node a,node b){return a.val > b.val;}
};
priority_queue<node,vector<node>, less<node> >que;

signed main(){
    n = read(); k = read() * 2; trie.insert(0); ll ans = 0;
    for(int i = 1;i <= n;i++)trie.insert(a[i] = (read() ^ a[i - 1]));
    for(int i = 0;i <= n;i++)que.push(node(trie.query(a[i],n + 1),i,n + 1));

    while(k--){
        node u = que.top();que.pop();ans += u.val;
        if(u.rks)que.push(node(trie.query(a[u.id],u.rks - 1),u.id,u.rks - 1));
    }
    printf("%lld\n",ans / 2LL);
    return 0;
}