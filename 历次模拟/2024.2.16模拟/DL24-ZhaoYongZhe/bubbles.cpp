#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxN = 1e7 + 10,maxn = 2e3 + 10;
bool f[maxn][maxn];
char ch[maxN];
int n;
void main(){
    fread(ch + 1, 1, 1e7, stdin);while(isdigit(ch[n + 1]))n++;ch[n + 1] = 0;
    f[1][0] = 1;f[n + 1][n] = 1;
    for(int i = 1;i < n;i++){
        f[i + 1][i] = 1;
        f[i][i + 1] = ch[i] == ch[i + 1];
        if(i + 2 <= n)f[i][i + 2] = (ch[i] == ch[i + 1] && ch[i + 1] == ch[i + 2]);
    }
    for(int len = 4;len <= n;len++){
        for(int i = 1;i + len - 1 <= n;i++){
            int j = i + len - 1;
            for(int k = i;k < j;k++){if(f[i][k] && f[k + 1][j]){f[i][j] = 1;break;}}
            if(f[i][j])continue;
            //1+1
            for(int a = i;a <= j;a++){
                if(!f[i][a - 1])continue;
                for(int b = a + 1;b <= j;b++){
                    if(ch[a] == ch[b] && f[a + 1][b - 1] && f[b + 1][j]){
                        f[i][j] = 1;break;
                    }
                }
                if(f[i][j])break;
            }
            if(f[i][j])continue;
            //1+1+1
            for(int a = i;a <= j;a++){
                if(!f[i][a - 1])continue;
                for(int b = a + 1;b <= j;b++){
                    if(ch[a] != ch[b] || !f[a + 1][b - 1])continue;
                    for(int c = b + 1;c <= j;c++){
                        if(ch[a] == ch[c] && f[i][a - 1] && f[a + 1][b - 1] && f[b + 1][c - 1] && f[c + 1][j]){
                            f[i][j] = 1;break;
                        }
                    }
                    if(f[i][j])break;
                }
                if(f[i][j])break;
            }
        }
    }
    long long ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++){
            ans += f[i][j];
            // if(f[i][j])printf("[%d,%d]\n",i,j);
        }
    }
    printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    freopen("bubbles.in","r",stdin);
    freopen("bubbles.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}