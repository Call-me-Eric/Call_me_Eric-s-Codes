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
const int maxn = 1e5 + 10;
char ch[maxn];
int f[maxn][13];
int n;
void main(){
    scanf("%s",ch + 1);n = strlen(ch + 1);
    auto nxt = [](int x,int c)->int{return ((x * (x - 1) >> 1) + c + 10) % 11;};
    int ans = 0;
    for(int i = 1;i <= n;i++){
        int x = ch[i] - '0';
        for(int j = x + 1;j <= 10;j++){f[i][nxt(j,x)] += f[i - 1][j];}
        if(x)f[i][x]++;
        for(int j = 0;j <= 10;j++)ans += f[i][j];
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