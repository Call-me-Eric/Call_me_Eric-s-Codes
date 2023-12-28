#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 110, mod = 2017;
struct Matrix{
    int data[maxn][maxn];
    void clear(){memset(data,0,sizeof(data));}
}e,I;
Matrix operator * (Matrix a,Matrix b){
    Matrix c;c.clear();
    for(int i = 0;i <= n;i++){
        for(int k = 0;k <= n;k++){
            for(int j = 0;j <= n;j++){
                c.data[i][j] = (c.data[i][j] + a.data[i][k] * b.data[k][j]) % mod;
            }
        }
    }
    return c;
}
Matrix qpow(Matrix a,int k){
    Matrix ans;ans.clear();
    if(k == 0)return I;
    if(k == 1)return a;
    Matrix tmp = qpow(a * a,k / 2);
    if(k & 1)tmp = tmp * a;
    return tmp;
}
signed main(){
    n = read(); m = read();
    int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v= read();
        e.data[u][v] = e.data[v][u] = 1;
    }
    for(int i = 0;i <= n;i++){e.data[i][0] = 1;e.data[i][i] = I.data[i][i] = 1;}
    e = qpow(e,read());
    int ans = 0;
    for(int i = 0;i <= n;i++){
        ans += e.data[1][i];
    }
    printf("%d\n",(ans % mod + mod) % mod);
    return 0;
}
