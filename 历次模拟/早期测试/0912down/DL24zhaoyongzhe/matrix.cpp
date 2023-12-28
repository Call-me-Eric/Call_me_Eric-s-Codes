#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1010;
int T, n,mod ,A[maxn][maxn], B[maxn][maxn], res[maxn][maxn],C[maxn][maxn];
signed main(){
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    T = read();
    while(T--){
        mod = read();
        n = read();
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                A[i][j] = read();
                res[i][j] = 0;
            }
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                B[i][j] = read();
            }
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                C[i][j] = read();
            }
        }
            bool flag = 1;
            for(int i = 1;i <= n && flag;i++){
                for(int j = 1;j <= n && flag;j++){
                    for(int k = 1;k <= n && flag;k++){
                        res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % mod;
                    }
                    if(res[i][j] != C[i][j]){puts("No");flag = 0;break;}
                }
            }
            if(flag)puts("Yes");
    }
    return 0;
}