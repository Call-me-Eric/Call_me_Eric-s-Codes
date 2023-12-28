#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 70;
int n, a[maxn];
int m, b[maxn];
int q, ans, len;
void dfs(int step){
    if(step == q + 1){
        for(int i = 1;i <= 15;i++)if(a[i] != b[i])return;
        ans++; return;
    }
    for(int i = 1;i <= 15;i++){
        if(a[i] - 1 >= a[i + 1]){
            a[i]--;dfs(step + 1);a[i]++;
        }
        if(a[i] + 1 <= a[i - 1]){
            a[i]++;dfs(step + 1);a[i]--;
        }
    }
}
signed main(){
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    a[0] = 0x3f3f3f3f;
    n = read();for(int i = 1;i <= n;i++)a[i] = read();
    m = read();for(int i = 1;i <= m;i++)b[i] = read();
    for(int test = read();test;test--){
        q = read();dfs(1);printf("%d\n",ans);
    }
    return 0;
}