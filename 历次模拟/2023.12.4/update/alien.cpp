#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
int n, k;
char ch[maxn];
int mp[maxn][maxn];
int cf[maxn][maxn];
void solve(){
    n = read(); k = read();
    for(int i = 0;i <= n + 1;i++)
        for(int j = 0;j <= n + 1;j++)
            cf[i][j] = 0,mp[i][j] = 0;
    int tot = 0;
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1);
        for(int j = 1;j <= n;j++){
            mp[i][j] = (ch[j] == '1');
            if(mp[i][j]){
                int x = max(1,i - k + 1), y = max(1,j - k + 1);
                cf[x][y]++;cf[x][j + 1]--;cf[i + 1][y]--;cf[i + 1][j + 1]++;
            }
            else tot++;
        }
    }
    int cnt = 0;
    for(int i = 1;i <= n;i++)cf[i][n - k + 2] = cf[n - k + 2][i] = n * n;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++){
            cf[i][j] += (cf[i - 1][j] + cf[i][j - 1] - cf[i - 1][j - 1]);
            cnt += (mp[i][j] = (cf[i][j] <= 0));
        }
    if(cnt == 0){puts("Alice");return;}
    if(cnt == 1){puts("Pluto");return;}
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            cf[i][j] = mp[i][j] + cf[i - 1][j] + cf[i][j - 1] - cf[i - 1][j - 1];
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(mp[i][j]){
                int x  = max(1,i - k + 1), y  = max(1,j - k + 1);
                int xx = min(n,i + k - 1), yy = min(n,j + k - 1);
                int sum = cf[xx][yy] - cf[xx][y - 1] - cf[x - 1][yy] + cf[x - 1][y - 1];
                if(sum != cnt){
                    if((tot - k * k * 2) & 1){puts("Pluto");return;}
                    else{puts("Alice");return;}
                }
            }
        }
    }
    puts("Pluto");
}
signed main(){
    freopen("alien.in","r",stdin);
    freopen("alien.out","w",stdout);
    int T = read();
    while(T--)solve();
    return 0;
}