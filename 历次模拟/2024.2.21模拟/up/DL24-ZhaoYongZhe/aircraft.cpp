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
const int maxn = 2e4 + 10, mod = 998244353;
int k, n, q;
bool op[4];
int a[maxn];
int f[maxn][1 << 6];
int to[1 << 6][1 << 6];
bool book[20][20];
int lim;
int dfs(int x,int y){
    if(y >= k){x++;y = 0;}
    if(x >= lim){return 1;}
    if(book[x][y])return dfs(x,y + 1);
    if(x >= 1 && !book[x - 1][y])return 0;
    int sum = 0;
    if(op[0]){
        if(!book[x][y]){
            book[x][y] = 1;
            sum += dfs(x,y + 1);
            book[x][y] = 0;
        }
    }
    if(op[1]){
        if(!book[x][y] && !book[x][y + 1]){
            book[x][y] = book[x][y + 1] = 1;
            sum += dfs(x,y + 2);
            book[x][y] = book[x][y + 1] = 0;
        }
        if(!book[x][y] && !book[x + 1][y]){
            book[x][y] = book[x + 1][y] = 1;
            sum += dfs(x,y + 1);
            book[x][y] = book[x + 1][y] = 0;
        }
    }
    if(op[2]){
        if(!book[x][y] && !book[x + 1][y] && !book[x + 1][y + 1]){
            book[x][y] = book[x + 1][y] = book[x + 1][y + 1] = 1;
            sum += dfs(x,y + 1);
            book[x][y] = book[x + 1][y] = book[x + 1][y + 1] = 0;
        }
        if(y > 0 && !book[x][y] && !book[x + 1][y] && !book[x + 1][y - 1]){
            book[x][y] = book[x + 1][y] = book[x + 1][y - 1] = 1;
            sum += dfs(x,y + 1);
            book[x][y] = book[x + 1][y] = book[x + 1][y - 1] = 0;
        }
        if(!book[x][y] && !book[x + 1][y] && !book[x][y + 1]){
            book[x][y] = book[x + 1][y] = book[x][y + 1] = 1;
            sum += dfs(x,y + 1);
            book[x][y] = book[x + 1][y] = book[x][y + 1] = 0;
        }
        if(!book[x][y] && !book[x][y + 1] && !book[x + 1][y + 1]){
            book[x][y] = book[x][y + 1] = book[x + 1][y + 1] = 1;
            sum += dfs(x,y + 1);
            book[x][y] = book[x][y + 1] = book[x + 1][y + 1] = 0;
        }
    }
    if(op[3]){
        if(!book[x][y] && !book[x + 1][y] && !book[x][y + 1] && !book[x + 1][y + 1]){
            book[x][y] = book[x + 1][y] = book[x][y + 1] = book[x + 1][y + 1] = 1;
            sum += dfs(x,y + 2);
            book[x][y] = book[x + 1][y] = book[x][y + 1] = book[x + 1][y + 1] = 0;
        }
    }
    return sum;
}
int sum[maxn];
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    int qry(int x){int s = 0;for(;x;x -= lowbit(x))s = (s + c[x]) % mod;return s;}
    void upd(int x,int upd){for(;x <= n;x += lowbit(x))c[x] = (c[x] + upd) % mod;}
    int qry(int l,int r){return qry(r) - qry(l - 1);}
}tr;
void main(){
    k = read(); char tmp[6];scanf("%s",tmp + 1);
    int opt, u = 1, v;
    while(isupper(tmp[u])){op[tmp[u] - 'A'] = 1;u++;}
    n = read(); q = read();
    for(int i = 1;i <= n;i++)a[i] = read();
if(u == 2 && op[0]){
    for(int j = 1;j <= q;j++){
        opt = read(); u = read(), v = read();
        if(opt == 1)read();
        else{printf("%lld\n",v - u + 1);}
    }
}
else{
    for(int i = 0;i <= 11;i++){book[i][k] = 1;book[10][i] = 1;}
    for(int i = 1;i <= 10;i++){
        for(int j = 0;j < k;j++) book[i][j] = 1;
        lim = i,sum[i] = dfs(0,0);
        for(int j = 0;j < k;j++) book[i][j] = 0;
    }
    for(int i = 1;i <= n;i++)tr.upd(i,sum[a[i]]);
    for(int j = 1;j <= q;j++){
        opt = read(); u = read(); v = read();
        if(opt == 1){
            int x = read();
            for(int i = u;i <= v;i++){
                tr.upd(i,-sum[a[i]]);a[i] += x;
                tr.upd(i,sum[a[i]]);
            }
        }
        else printf("%lld\n",(tr.qry(u,v) + mod) % mod);
    }
}
    return;
}
};
bool edmemory;
signed main(){
    freopen("aircraft.in","r",stdin);
    freopen("aircraft.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}