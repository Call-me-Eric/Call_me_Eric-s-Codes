#include<bits/stdc++.h>
#define int long long
using namespace std;
int a, b;
const int maxn = 1e6 + 10;
bool book[maxn];int prime[maxn], cnt;
int x[maxn], p[maxn], tot;
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
int f(int n,int m){
    int ans = 0;
    while(1){
        int mx = 0, pos = 0;
        for(int i = 1;i <= tot && x[i] <= m;i++)
            if(p[i] && (m / x[i] * x[i] > mx))mx = m / x[i] * x[i], pos = i;
        ans += m - mx;m = mx;
        if(!m)return ans;
        // if(m == 1){return ans + 1;}
        --p[pos];n /= x[pos]; m /= x[pos];
    }
    return -114514;
}
signed main(){
    scanf("%lld%lld",&a,&b);
    // book[1] = 1;int g = gcd(a, b);a /= g;b /= g;

    for(int i = 2;i <= 1e6;i++){
        if(!book[i]){prime[++cnt] = i;}
        for(int j = 1;j <= cnt && i * prime[j] <= 1e6;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    // for(int i = 1;i <= 10;i++)printf("prime[%lld] = %lld\n",i,prime[i]);
    int tmp = a;
    // tot++;x[tot] = 1;p[tot] = 1e18;
    for(int i = 1;i <= cnt && tmp >= prime[i];i++){
        if(tmp % prime[i] == 0){
            tot++;x[tot] = prime[i];while(tmp % prime[i] == 0){tmp /= prime[i];p[tot]++;}
        }
    }
    if(tmp != 1){tot++;x[tot] = tmp;p[tot] = 1;}
    // printf("%lld\n",tot);
    // for(int i = 1;i <= tot;i++)printf("x[%lld] = %lld,p[%lld] = %lld\n",i,x[i],i,p[i]);
    
    printf("%lld\n",f(a,b));

    return 0;
}
