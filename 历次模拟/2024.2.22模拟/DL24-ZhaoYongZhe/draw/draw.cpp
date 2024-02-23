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
const int maxn = 44 + 10;
int n, m, a, b, c;
int f[maxn][maxn][4][4];//f(i,j,x,y)=(i,j)涂上0/1/2/3<=>不涂/竖向涂/横向涂/单独涂，第一层是x，第二层是y
char ch[maxn][maxn];
bool mp[maxn][maxn];
void main(){
    n = read(); m = read(); a = read(); b = read(); c = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= m;j++){
            mp[i][j] = ch[i][j] == '#';
        }
    }
    memset(f,0x3f,sizeof(f));
    f[0][0][0][0] = f[0][1][0][0] = f[1][0][0][0] = 0;
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