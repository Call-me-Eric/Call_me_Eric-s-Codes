#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 700 + 10, mod = 998244353;
int n, q;
int a[maxn][maxn], b[maxn][maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res =res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
void gauss(){
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++)
            if(a[j][i] != 0){swap(a[i],a[j]);break;}
        if(!a[i][i])continue;
        int inv = qpow(a[i][i], mod - 2);
        for(int j = i;j <= n + 1;j++){a[i][j] = (a[i][j] * inv) % mod;}
        for(int j = 1;j <= n;j++)
            if(j != i && a[j][i] != 0){
                int pw = a[j][i];
                // printf("j = %lld:\n",j);
                for(int k = i;k <= n + 1;k++){
                    // printf("k = %lld : a[j][k] = %lld, a[i][k] = %lld,a[j][i] = %lld\n",k,a[j][k],a[i][k],a[j][i]);
                    a[j][k] = (a[j][k] - a[i][k] * pw % mod + mod) % mod;
                    // printf("%lld ",a[j][k]);
                }
            }
    // puts("###########################");
    // printf("i = %lld step\n",i);
    // for(int k = 1;k <= n;k++){
    //     for(int j = 1;j <= n + 1;j++){
    //         printf("%lld ",a[k][j]);
    //     }
    //     puts("");
    // }
    // puts("###########################");
    }
}
void printans(){
    int chk = 0;
    for(int i = 1;i <= n;i++){
        if(a[i][i] == 0){
            if(a[i][n + 1] == 0)chk = 1;
            else chk = -1;
            break;
        }
    }
    if(chk == 0){
        for(int i = 1;i <= n;i++)printf("%lld%c",a[i][n + 1]," \n"[i==n]);
    }
    else puts(chk == 1 ? "Many" : "No");
}
signed main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    n =  read(); q = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n + 1;j++)
            b[i][j] = a[i][j] = read();
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++)
            if(a[j][i] != 0)swap(a[j],a[i]);
        if(!a[i][i])continue;
        int inv = qpow(a[i][i],mod - 2);
        for(int j = 1;j <= n + 1;j++)a[i][j] = (a[i][j] * inv) % mod;
    }
    gauss();printans();
    
        while(q--){
            int z = read();for(int i = 1;i <= n + 1;i++)b[z][i] = read();
            for(int i = 1;i <= n;i++)
                for(int j = 1;j <= n + 1;j++)
                    a[i][j] = b[i][j];
            gauss();printans();
        }
    return 0;
}