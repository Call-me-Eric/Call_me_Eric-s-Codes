#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int T;
int n, m;
const int maxn = 16;
int b[maxn] ,a[maxn], rev[maxn];
bool dfs(int len,int c[]){
    if(len == m){
        bool flag1 = true, flag2 = true;
        for(int i = 1;i <= m;i++){
            if(c[i] != a[i])flag1 = false;
            if(c[i] != rev[i])flag2 = false;
        }
        return flag1 || flag2;
    }
    int tmp[maxn] = {0}, cnt = 0;
    bool ans = false;
    for(int i = 1;i <= len - 1;i++){
        if(max(len,len - i) < m)continue;
        if(i <= len / 2){
            for(int j = 1, k = len;k >= i + 1;j++,k--){
                tmp[j] = c[k];
            }
            for(int j = len - i, k = i;k >= 1;j--,k--){
                tmp[j] += c[k];
            }
        }else{
            for(int j = 1;j <= i;j++){
                tmp[j] = c[j];
            }
            for(int j = i, k = i + 1;k <= len;j--,k++){
                tmp[j] += c[k];
            }
        }
        ans |= dfs(max(i,len - i),tmp);
    }
    return ans;
}
signed main(){
while(scanf("%d",&n) != -1){
    for(int i = 1;i <= n;i++)b[i] = read();
    m = read(); for(int i = 1;i <= m;i++)a[i] = read();
    for(int i = m;i;i--)rev[i] = a[m - i + 1];
    puts(dfs(1,b) ? "S" : "N");
}
    return 0;
}