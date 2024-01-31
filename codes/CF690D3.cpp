#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=  0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 110, mod = 1e6 + 3;
int M, H, C;
struct Matrix{
    int a[maxn][maxn];
    Matrix(){memset(a,0,sizeof(a));}
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix();
        for(int i = 0;i <= M;i++)
            for(int j = 0;j <= M;j++)
                for(int k = 0;k <= M;k++)
                    c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
        return c;
    }
}A, B;
signed main(){
    C = read();M = read(); H = read();
    A.a[0][0] = 1;
    for(int i = 0;i <= M;i++){B.a[i][0] = 1;}
    for(int i = 1;i <= M;i++){B.a[i - 1][i] = H;}
    while(C){
        if(C & 1){A = A * B;}
        B = B * B;C >>= 1;
    }
    int ans = 0; for(int i = 0;i <= M;i++){ans = (ans + A.a[0][i]) % mod;}
    printf("%lld\n",ans);
    return 0;
}