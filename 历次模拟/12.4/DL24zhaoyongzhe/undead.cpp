#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10,maxm = 1e5 + 10, mod = 998244353;
int sum[maxn][maxn];
int pw[maxm], inv[maxm];
int n[maxm], m[maxm];

int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}

int C(int x,int y){
    if(x < y)return 0;
    return pw[x] * inv[x - y] % mod * inv[y] % mod;
}

signed main(){
    freopen("undead.in","r",stdin);
    freopen("undead.out","w",stdout);
    
    pw[0] = 1;inv[0] = 1;
    for(int i = 1;i < maxm;i++)pw[i] = pw[i - 1] * i % mod;
    inv[maxm - 1] = qpow(pw[maxm - 1], mod - 2);
    for(int i = maxm - 2;i;i--)inv[i] = inv[i + 1] * (i + 1) % mod;

    for(int i = 0;i <= 5e3;i++){
        for(int j = 0;j <= 5e3;j++){
            if(i == 0){
                if(j == 0)sum[i][j] = 1;
                else sum[i][j] = sum[i][j - 1] + C(i,j);
            }
            else if(j == 0)sum[i][j] = sum[i - 1][j] + C(i,j);
            else sum[i][j] = (sum[i][j - 1] - sum[i - 1][j - 1] + sum[i - 1][j] + C(i,j) + mod) % mod;
            if((i + j) & 1)sum[i][j] = (sum[i][j] - C(i,j) + mod) % mod;
        }
    }
    int T = read();
    bool test1 = true, test2 = true;
    for(int i = 1;i <= T;i++){
        n[i] = read(); m[i] = read();
        if(i != 1){
            test1 &= (n[i] == n[i - 1]);
            test2 &= (m[i] == m[i - 1]);
        }
    }
    if(test1){
        
    }
    else if(test2){
    }
    else{
    for(int i = 1;i <= T;i++){
        int u = n[i], v = m[i];
        if(u <= 5e3 && v <= 5e3)printf("%lld\n",sum[u][v]);
        else{
            int cnt = 0;
            for(int i = 0;i <= u;i++)
                for(int j = 0;j <= v;j++)
                    cnt = (cnt + C(i,j) * (((i + j) & 1) == 0)) % mod;
            printf("%lld\n",cnt);
        }
    }
    }
    return 0;
}