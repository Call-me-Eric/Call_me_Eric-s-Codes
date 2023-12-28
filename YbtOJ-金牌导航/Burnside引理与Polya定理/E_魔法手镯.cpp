#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxk = 11, mod = 9973;
int n, m, k;
struct Matrix{
    int a[maxk][maxk];
    Matrix(int x = 0){
        for(int i = 1;i <= m;i++)
            for(int j = 1;j <= m;j++)
                a[i][j] = 0;
        if(x != 0)
            for(int i = 1;i <= m;i++)a[i][i] = 1;
    }
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix(0);
        for(int i = 1;i <= m;i++)
            for(int k = 1;k <= m;k++)
                for(int j = 1;j <= m;j++)
                    c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j] % mod) % mod;
        return c;
    }
}A, B;

int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
Matrix qpow(Matrix x,int a){
    Matrix res = Matrix(1);
    while(a){
        if(a & 1)res = res * x;
        x = x * x;a >>= 1;
    }
    return res;
}

int phi(int n){
    int ans = n;
    for(int i = 2;i * i <= n;i++){
        if(n % i)continue;
        ans = ans / i * (i - 1);
        while(n % i == 0)n /= i;
    }
    if(n > 1)ans = ans / n * (n - 1);
    // printf("ans = %d\n",ans);
    return ans;
}
int calc(int x){
    B = qpow(A,n / x - 1);int ans = 0;
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= m;j++){
            if(A.a[i][j])ans = (ans + B.a[i][j]) % mod;
            // printf("(%lld,%lld) = %lld\n",i,j,ans);
        }
    // printf("ans = %lld\n",ans);
    return ans % mod;
}
signed main(){
int T = read();
while(T--){
    n = read();m = read(); k = read();
    memset(A.a,0,sizeof(A.a));
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= m;j++)
            A.a[i][j] = 1;
    for(int i = 1;i <= k;i++){
        int u = read(), v = read();
        A.a[u][v] = A.a[v][u] = 0;
    }
    int ans = 0;
    for(int i = 1;i * i <= n;i++){
        if(n % i == 0){
            ans = (ans + calc(i) * phi(i) % mod) % mod;
            if(n / i == i)continue;
            ans = (ans + calc(n / i) * phi(n / i) % mod) % mod;
        }
    }
    // printf("%lld\n",ans);
    ans = ans * qpow(n,mod - 2) % mod;
    printf("%lld\n",ans);
}
    return 0;
}