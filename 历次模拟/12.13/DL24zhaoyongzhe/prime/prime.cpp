#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e7 + 10, mod = 998244353;
int prime[maxn], tot;
bool book[maxn];
int sum[maxn];
bool isprime(int x){
    for(int i = 2;i * i <= x;i++){
        if(x % i == 0)return false;
    }
    return true;
}
bool check(int i){
    int ar[10] = {0};int top = 0, x = i;
    while(x){
        ar[++top] = x % 10;x /= 10;
    }
    int chk = 1;
    for(int l = top;l;l--){
        x = 0;
        for(int r = l;r;r--){
            x = x * 10 + ar[r];
            if(x < maxn){if(!book[x]){chk = 0;break;}}
            else{ if(isprime(x)){chk = 0;break;}}
        }
        if(!chk)break;
    }
    return chk;
}
signed main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    for(int i = 2;i < maxn;i++){
        if(!book[i])prime[++tot] = i;
        for(int j = 1;j <= tot && i * prime[j] < maxn;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    book[0] = book[1] = 1;
    for(int i = 1;i < maxn;i++){
        sum[i] = check(i);
        // if(!book[i] && chk)printf("%d\n",i);
    }
    for(int i = 1;i < maxn;i++)sum[i] += sum[i - 1];
    for(int test = read();test;test--){
        int l = read(), r = read();
        if(r < maxn)printf("%d\n",sum[r] - sum[l - 1]);
        else{
            int ans = 0;
            for(int i = l;i <= r;i++)ans += check(i);
            printf("%d\n",ans);
        }
    }
    return 0;
}