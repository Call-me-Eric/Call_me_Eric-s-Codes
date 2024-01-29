#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch =getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
const int mod = 998244353;
int n, a[maxn], b[maxn];
bool book[maxn];int rev = 0;
vector<int> edg[maxn];
vector<int> vec;
void dfs(int u){
    book[u] = 1;vec.push_back(u);
    for(int v : edg[u]){
        if(v == u)rev = 1;
        else if(!book[v])dfs(v);
    }
}

int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}

signed main(){
    n = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++)b[i] = read();
    for(int i = 1;i <= n;i++){
        edg[a[i]].push_back(b[i]);
        if(a[i] != b[i])edg[b[i]].push_back(a[i]);
    }

    int res = 1;
    for(int i = 1;i <= n;i++)
        if(!book[i]){
            int tmp = 0; vec.clear(); rev = 0; dfs(i);
            for(int u : vec)
                for(int v : edg[u])
                    if(v <= u)tmp++;
            if(tmp > (int)vec.size())res = 0;
            else if(rev)res = res * n % mod;
            else res = res * 2ll % mod;
        }
    printf("%lld\n",(qpow(n,n) - res + mod) % mod);
    return 0;
}