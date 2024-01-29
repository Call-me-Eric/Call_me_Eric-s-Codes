#include<bits/stdc++.h>
using namespace std;
int n, m, k;
const int inf = 0x3f3f3f3f;
const int maxn = 10000 + 10,maxm = 2000 + 10;
int f[maxn][maxm];//f[i][j] -> (i,j)点在上一次操作后的总次数
int x[maxn],y[maxn];
int high[maxn],low[maxn];
bool e[maxn];
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i = 1;i <= n;i++){
        scanf("%d%d",&x[i],&y[i]);
        low[i] = 1;
        high[i] = m;
    }
    int a,b,c;
    for(int i = 1;i <= k;i++){
        scanf("%d%d%d",&a,&b,&c);
        e[a] = 1;
        high[a] = c - 1;
        low[a] = b + 1;
    }
    memset(f,0x3f,sizeof(f));
    for(int i = 1;i <= m;i++)f[0][i] = 0;
    for(int i = 1;i <= n;i++){
        for(int j = x[i] + 1;j <= m + x[i];j++){
            f[i][j] = min(f[i - 1][j - x[i]] + 1,f[i][j - x[i]] + 1);
        }
        for(int j = m + 1;j <= m + x[i];j++){
            f[i][m] = min(f[i][m],f[i][j]);
        }
        for(int j = 1;j <= m - y[i];j++){
            f[i][j] = min(f[i][j],f[i - 1][j + y[i]]);
        }
        for(int j = 1;j < low[i];j++){
            f[i][j] = f[0][0];
        }
        for(int j = high[i] + 1;j <= m;j++){
            f[i][j] = f[0][0];
        }
    }
    int ans = f[0][0];
    for(int j = 1;j <= m;j++){
        ans = min(ans,f[n][j]);
    }
    if(ans < f[0][0]){
        printf("1\n%d\n",ans);
    }//顺利通关
    else{
        int i, j;
        for(i = n;i >= 1;i--){
            for(j = 1;j <= m;j++){
                if(f[i][j] < f[0][0]){break;}
            }
            if(j <= m){break;}
        }
        ans = 0;
        for(j = 1;j <= i;j++){
            if(e[j])ans++;
        }
        printf("0\n%d\n",ans);
    }
    return 0;
}