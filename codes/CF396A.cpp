#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 1e9 + 7;
int n;

int prime[maxn], tot;
bool book[maxn];

unordered_map<int,int> mp;

int pw[maxn], invpw[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int C(int n,int m){return pw[n] * invpw[m] % mod * invpw[n - m] % mod;}

signed main(){
    n = read();pw[0] = 1;pw[1] = 1;
    for(int i = 2;i <= 1e5;i++){
        pw[i] = pw[i - 1] * i % mod;
        if(!book[i])prime[++tot] = i;
        for(int j = 1;j <= tot && prime[j] * i <= 1e5;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    invpw[(int)1e5] = qpow(pw[(int)1e5],mod - 2);
    for(int i = 1e5 - 1;i + 1;i--){invpw[i] = invpw[i + 1] * (i + 1) % mod;}

    for(int i = 1;i <= n;i++){
        int x = read();
        for(int j = 1;j <= tot;j++)
            while(x % prime[j] == 0){
                mp[prime[j]]++;x /= prime[j];
            }
        if(x != 1)mp[x]++;
    }
    int ans = 1;
    for(auto it = mp.begin();it != mp.end();it++){
        // printf("it = %lld\n",it->second);
        ans = ans * C(n + (it->second) - 1,n - 1) % mod;
    }
    printf("%lld\n",ans);
    return 0;
}