#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x= 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 21, mod = 1e9 + 7;
int siz;
struct Matrix{
    int d[maxn][maxn];
    Matrix(int x = 0,bool opt = 0){
        memset(d,0,sizeof(d));
        if(opt == 0){
            d[1][1] = 1;
            for(int i = 1;i < x;i++)
                d[i + 1][i] = d[i][i + 1] = d[i + 1][i + 1] = 1;
        }
        else for(int i = 1;i <= siz;i++)d[i][i] = 1;
    }
    void DEBUG(){
        for(int i = 1;i < maxn;i++){
            for(int j = 1;j < maxn;j++)
                printf("%lld ",d[i][j]);
            puts("");
        }
    }
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix(0);c.d[1][1] = 0;
        for(int i = 1;i <= siz;i++)
            for(int k = 1;k <= siz;k++)
                for(int j = 1;j <= siz;j++)
                    c.d[i][j] = (c.d[i][j] + a.d[i][k] * b.d[k][j] % mod) % mod;
        return c;
    }
    friend Matrix operator ^ (Matrix x,int a){
        Matrix res = Matrix(0,1);
        while(a){
            if(a & 1)res = res * x;
            x = x * x;a >>= 1;
        }
        return res;
    }
}A;
int n, k;
signed main(){
    n = read();k = read();
    A = Matrix(0,0);
    for(int i = 1;i <= n;i++){
        int a = read(), b = read(), c = read();
        siz = c + 1;
        A = A * (Matrix(siz,0) ^ (min(b,k) - a));
        if(b >= k)break;
    }
    printf("%lld\n",A.d[1][1]);
    return 0;
}