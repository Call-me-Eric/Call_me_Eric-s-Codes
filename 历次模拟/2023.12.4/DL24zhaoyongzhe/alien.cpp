#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch  = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
bool mp[maxn][maxn];
int cf[maxn][maxn];
char ch[maxn];
int n, k;
void solve(){
    n = read(); k = read();int cnt = 0;
    for(int i = 0;i <= n + 1;i++)
        for(int j = 0;j <= n + 1;j++)cf[i][j] = 0;
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1);
        for(int j = 1;j <= n;j++){
            mp[i][j] = (ch[j] == '1');
            cnt += mp[i][j];
            if(mp[i][j]){
                int x = max(1,i - k + 1), y = max(1, j - k + 1);
                int xx = i, yy = j;
                cf[x][y]++;cf[x][yy + 1]--;cf[xx + 1][y]--;cf[xx + 1][yy + 1]++;
            }
        }
    }
    for(int i = 1;i <= n;i++)cf[i][n - k + 2] = n * n,cf[n - k + 2][i] = n * n;
    int canput = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++){
            cf[i][j] += (cf[i - 1][j] + cf[i][j - 1] - cf[i - 1][j - 1]);
            if(cf[i][j] <= 0)canput++;
            if(cf[i][j] > n * n)cf[i][j] = n * n;
        }
    // for(int i = 1;i <= n;i++){
    //     for(int j = 1;j <= n;j++){
    //         printf("%d ",cf[i][j]);
    //     }
    //     puts("");
    // }
    if(k == n){
        if(!cnt)puts("Pluto");
        else puts("Alice");
        return;
    }
    // puts("11");
    if(2 * k > n){
        if(canput)puts("Pluto");
        else puts("Alice");
        return;
    }
    // puts("22");
    if(k == 1){
        if(cnt & 1)puts("Pluto");
        else puts("Alice");
        return;
    }
    // puts("33");
    if(canput == 0){puts("Alice");return;}
    // puts("44");
    if(canput == 1){puts("Pluto");return;}
    // puts("55");
    if(canput & 1){puts("Pluto");}
    else puts("Alice");
    return;
}
signed main(){
    freopen("alien.in","r",stdin);
    freopen("alien.out","w",stdout);
    int T = read();
    while(T--)solve();
    return 0;
}
/*
5
1 1
0
1 1
1
2 2
00
00
2 2
01
00
3 2
100
000
001
*/