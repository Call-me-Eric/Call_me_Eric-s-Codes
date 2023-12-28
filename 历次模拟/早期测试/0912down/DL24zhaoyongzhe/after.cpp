#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 5050;
int a[maxn], res[50000][maxn], ans;
bool check(){
    for(int i = 1;i <= ans;i++){
        bool flag = 1;
        for(int j = 1;j <= n;j++){
            if(a[j] != res[i][j]){flag = 0;break;}
        }
        if(flag)return false;
    }
    for(int i = 1;i <= n;i++){
        res[ans + 1][i] = a[i];
    }
}
void dfs(int step){
    if(step == n + 1){
        if(check())ans++;
        return;
    }
    int tmp = a[step];
    a[step] = (a[step] < a[step - 1]) ? a[step - 1] : tmp;
    dfs(step + 1);
    a[step] = (a[step] < a[step + 1]) ? a[step + 1] : tmp;
    dfs(step + 1);
    a[step] = tmp;
}
signed main(){
    freopen("after.in","r",stdin);
    freopen("after.out","w",stdout);
    n = read();
    bool flag = 1;
    for(int i = 1;i <= n;i++){
        a[i] = read();
        if(a[i] <= a[i - 1])flag = 0;
    }
    dfs(1);
    printf("%d\n",ans);
    return 0;
}