#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e3 + 10;
int n, m;
char ch[maxn][maxn];
bool f[maxn][maxn], g[maxn][maxn];
vector<int> vec[maxn * 3];
void main(){
    int cnt = 0;
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= m;j++)
            cnt += ch[i][j] == '.';
    }
    char tmp = ch[1][1];
    f[1][1] = 1; ch[1][1] = '.';
    for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)
        if(i + j != 2 && ch[i][j] == '.')
            f[i][j] = f[i][j - 1] | f[i - 1][j];
    g[n][m] = 1; ch[n][m] = '.';ch[1][1] = tmp;
    for(int i = n;i;i--)for(int j = m;j;j--)
        if(i + j != n + m && ch[i][j] == '.')
            g[i][j] = g[i][j + 1] | g[i + 1][j];
    if(n * m == 1){puts("0");return;}
    if(!g[1][1]){printf("%lld\n",cnt * (cnt - 1) / 2);return;}
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(!f[i][j] || !g[i][j])ch[i][j] = '*';
            else{vec[i + j].push_back(i);}
        }
    }
    int ans = 0;
    for(int i = 2;i <= n + m;i++)if(vec[i].size() == 1){cnt--;ans += cnt;}
    for(int i = 2;i <= n + m;i++){
        if(vec[i].size() > 1){
            ans += vec[i].size() == 2;
            int l = vec[i][1], r = vec[i].back();
            for(int j = i + 1;j <= n + m;j++){
                if(ch[l][j - l] != '.')l++;
                if(ch[r + 1][j - r - 1] == '.')r++;
                if(l == r && vec[j].size() != 1)ans++;
            }
            l = vec[i].front(), r = vec[i][vec[i].size() - 2];
            for(int j = i + 1;j <= n + m;j++){
                if(ch[l][j - l] != '.')l++;
                if(ch[r + 1][j - r - 1] == '.')r++;
                if(l == r && vec[j].size() != 1)ans++;
            }
        }
    }
    printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}