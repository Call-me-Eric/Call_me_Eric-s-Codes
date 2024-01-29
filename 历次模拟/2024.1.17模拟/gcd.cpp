#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch =  getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int a[maxn], n;
int r[maxn], g[maxn];
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
int lcm(int x,int y){return x / gcd(x, y) * y;}
int getans(){
    int ans = 0;g[n + 1] = 1;a[n + 1] = 1;
    for(int i = n;i;i--){
        int rp = i;g[i] = a[i];
        while(gcd(g[i],g[rp + 1]) > 1 && rp <= n){g[i] = gcd(g[i],g[rp + 1]);rp = r[rp + 1];}
        while(gcd(g[i],a[rp + 1]) > 1 && rp <= n){g[i] = gcd(g[i],a[rp + 1]);rp++;}
        r[i] = rp;ans += (r[i] - i + 1);
    }
    return ans;
}
bool book[maxn];
signed main(){
    freopen("gcd.in","r",stdin);
    freopen("gcd.out","w",stdout);
    n = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();
        for(int j = 2;j * j <= a[i];j++){
            int x = j;
            if(a[i] % j == 0){
                while(a[i] % j == 0)a[i] /= j;
                a[i] *= j;
            }
        }
    }
    int ans = getans();
    if(n <= 100){
        for(int i = 1;i <= n;i++){
            int tmp = a[i], pw = a[i];
            if(i != 1){pw = lcm(pw,a[i - 1]);}
            if(i != n){pw = lcm(pw,a[i + 1]);}
            for(int j = 1;j * j <= pw && j <= 5e5;j++){
                if(pw % j == 0){
                    a[i] = j;ans = max(ans,getans());
                    if((pw / j) <= 5e5){a[i] = pw / j;ans = max(ans,getans());}
                }
            }
            a[i] = tmp;
        }
    }
    else{
        srand(time(0));int sd = rand() % 5000;
        for(int i = 1;i <= n;i++)if(r[i] == i)book[i] = 1;
        for(int i = 1;i <= n;i++){
            sd = (sd + rand()) % 5000;
            if(sd < 4998 || !book[i]){continue;}
            int tmp = a[i], pw = a[i];
            if(i != 1){pw = lcm(pw,a[i - 1]);}
            if(i != n){pw = lcm(pw,a[i + 1]);}
            for(int j = 1;j * j <= pw && j <= 5e5;j++){
                if(pw % j == 0){
                    a[i] = j;ans = max(ans,getans());
                    if((pw / j) <= 5e5){a[i] = pw / j;ans = max(ans,getans());}
                }
            }
            a[i] = tmp;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
/*
5
4 5 10 3 7
*/