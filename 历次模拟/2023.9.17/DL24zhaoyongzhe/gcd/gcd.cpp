#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10, maxm = 1e6 + 10;
int buc[maxm];
int n, a[maxn], k;

int prime[maxn], tot;
bool book[maxn];

void add(int x){
    for(int i = 1;i <= x;i++){
        if(x % i == 0){buc[x / i]++;buc[i]++;}
    }
}
void del(int x){
    for(int i = 1;i <= x;i++){
        if(x % i == 0){buc[x / i]--;buc[i]--;}
    }
}
int getans(int x){
    for(int i = x;i >= 1;i--){
        if(x % i == 0 && buc[x] != 0)return i;
    }
}

signed main(){
    freopen("gcd.in","r",stdin);
    freopen("gcd.out","w",stdout);
    n = read(); k = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    // book[1] = 1;
    // for(int i = 2;i < maxn;i++){
    //     if(!book[i]){prime[++tot] = i;}
    //     for(int j = 1;j <= tot && prime[j] * i < maxn;j++){
    //         book[i * prime[j]] = 1;
    //         if(i % prime[j] == 0)break;
    //     }
    // }
    // for(int i = 1;i <= 30;i++)printf("%d ",prime[i]);
    for(int i = 1;i < k;i++){add(a[i]);}
    int ans = 1;
    for(int i = k + 1;i <= n;i++){
        ans = max(getans(a[i]),ans);
        add(a[i]);
    }
    printf("%d\n",ans);
    return 0;
}