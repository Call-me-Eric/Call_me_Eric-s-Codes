#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 105;
int n;
char ch[maxn];
int f[maxn][maxn];
bool check(int i,int j,int l,int r){
    if((r - l + 1) % (r - l + 1))return false;
    for(int q = 0;l <= r;q ++,l++){
        q %= (j - i + 1);
        if(ch[i + q] != ch[l])return false;
    }
    return true;
}
signed main(){
    scanf("%s",ch + 1);
    n = strlen(ch + 1);
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++){
            f[i][j] = j - i + 1;
        }
    }
    for(int l = 1;l <= n;l++){
        for(int i = 1;i + l - 1 <= n;i++){
            int j = i + l - 1;
            for(int k = i;k < j;k++){
                if(check(i,k,k + 1,j)){
                    int numlen(1 + (int)log10(l / (k - i + 1)));
                    f[i][j] = min(f[i][j],f[i][k] + 2 + numlen);
                }
                f[i][j] = min(f[i][j],f[i][k] + f[k + 1][j]);
            }
        }
    }
    printf("%d\n",f[1][n]);
    return 0;
}
