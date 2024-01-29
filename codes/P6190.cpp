#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f  =-1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 110, maxm = 2510;
int n, m, k;
struct Matrix{
    int a[maxn][maxn];
    Matrix(){memset(a,0x3f,sizeof(a));}
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix();
        for(int k = 1;k <= n;k++)
            for(int i = 1;i <= n;i++)
                for(int j = 1;j <= n;j++)
                    c.a[i][j] = min(c.a[i][j],a.a[i][k] + b.a[k][j]);
        return c;
    }
}B;
int e[maxn][maxn];
int fr[maxm], to[maxm], wei[maxm];
Matrix qpow(Matrix x,int a){
    Matrix res = x;a--;
    while(a){
        if(a & 1)res = res * x;
        x = x * x;a >>= 1;
    }
    return res;
}
signed main(){
    n = read(); m = read(); k = read(); memset(e,0x3f,sizeof(e));
    for(int i = 1;i <= n;i++)e[i][i] = 0;
    for(int i = 1;i <= m;i++){
        fr[i] = read();to[i] = read();
        e[fr[i]][to[i]] = wei[i] = read();
    }
    for(int l = 1;l <= n;l++)
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                e[i][j] = min(e[i][j],e[i][l] + e[l][j]);

    for(int l = 1;l <= m;l++)
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                B.a[i][j] = min(B.a[i][j],min(e[i][j],e[i][fr[l]] - wei[l] + e[to[l]][j]));

    // for(int i = 1;i <= m;i++){printf("%d %d %d\n",fr[i],to[i],wei[i]);}
    // for(int i = 1;i <= n;i++)
    //     for(int j = 1;j <= n;j++){
    //         printf("a[%d][%d] = %d\n",i,j,B.a[i][j]);
    //     }

    if(!k)printf("%lld\n",e[1][n]);
    else printf("%lld\n",qpow(B,k).a[1][n]);
    return 0;
}