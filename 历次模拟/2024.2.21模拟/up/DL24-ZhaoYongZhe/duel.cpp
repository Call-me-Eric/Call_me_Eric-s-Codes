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
const int maxn = 33, maxm = 44, mod = 998244353;
int n, m;
int c[maxn];
int S[maxn][maxm];
char ch[maxm];
int a[maxn], ans;
bool check(){
    for(int i = 1;i <= n;i++){
        if(c[i] == 2)continue;
        int l = i, r = i;
        while(l != 1 || r != n){
            while(a[l - 1] <= a[i] + (r - l))l--;
            while(a[r + 1] <= a[i] + (r - l))r++;
            if(a[l - 1] > a[i] + (r - l) && a[r + 1] > a[i] + (r - l))break;
        }
        if((l == 1 && r == n) != c[i])return false;
    }
    return true;
}
void dfs(int u){
    if(u == n + 1){ans += check();return;}
    for(int j = 1;j <= m;j++){if(S[u][j]){a[u] = j;dfs(u + 1);a[u] = 0;}}
}
void main(){
    n = read(); m = read();bool sub1 = true;
    for(int i = 1;i <= n;i++){
        c[i] = read();
        if(i >= 2 && c[i] != 2)sub1 = false;
    }
    sub1 |= (c[1] == 1);
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1);
        for(int j = 1;j <= m;j++){S[i][j] = ch[j] - '0';}
    }
    if(sub1){
        for(int i = 2;i <= n;i++)
            for(int j = 1;j <= m;j++)
                S[i][j] += S[i][j - 1];
        int res = 0;
        for(int j = 1;j <= m;j++){
            if(S[1][j]){
                int pw = 1;
                for(int i = 2;i <= n;i++){
                    pw = (pw * S[i][min(m,i - 2 + j)]) % mod;
                }
                res = (res + pw) % mod;
            }
        }
        printf("%lld\n",res);
    }
    else{
        a[0] = a[n + 1] = 0x3f3f3f3f;
        dfs(1);
        printf("%lld\n",ans);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("duel.in","r",stdin);
    freopen("duel.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
5 5
0 1 2 2 2
10100
01000
01000
00010
00001
*/