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
const int maxn = 32 + 10, maxm = 1e6 + 10;
int n, k;
map<int,int> mp;
int cntfac2(int x){
    if(mp.count(x))return mp[x];
    int res = 1, t = x;
    while((x & 1) == 0){res <<= 1;x >>= 1;}
    return mp[t] = res;
}
int s[maxn][maxn], h[maxn][maxn];
int val[maxn][maxn];
pair<int,int> ans[maxm];
void main(){
    n = read();k = read();
    for(int i = 0;i < n;i++)for(int j = 0;j < n - 1;j++)
        printf("%d%c",h[i][j] = cntfac2(j + 1) * cntfac2(j + 1)," \n"[j == n - 2]);
    for(int i = 0;i < n - 1;i++)for(int j = 0;j < n;j++)
        printf("%d%c",s[i][j] = cntfac2(i + 1) * cntfac2(i + 1) * 2," \n"[j == n - 1]);
    fflush(stdout);
    for(int i = 0;i < n;i++)for(int j = 0;j < n;j++){
        if(!i && !j)continue;
        if(!i)val[i][j] = val[i][j - 1] ^ h[i][j - 1];
        else val[i][j] = val[i - 1][j] ^ s[i - 1][j];
        ans[val[i][j]] = make_pair(i,j);
    }
    int x = 0;
    while(k--){
        x ^= read();
        printf("%d %d\n",ans[x].first + 1,ans[x].second + 1);
        fflush(stdout);
    }
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