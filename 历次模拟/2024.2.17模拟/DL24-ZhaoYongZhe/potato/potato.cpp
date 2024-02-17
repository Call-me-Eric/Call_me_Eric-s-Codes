#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
#define ll long long
inline ll read(){
    ll x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10;
int T, n, m, t; unsigned int seed;
bool a[maxn][maxn];
bool Rand(unsigned int &x) {
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    return (x & 65535) < t;
}
void getdata(){for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)a[i][j] = Rand(seed);}
int sum[maxn][maxn];
inline int getsum(int x,int y,int i,int j){
    return sum[i][j] - sum[x - 1][j] - sum[i][y - 1] + sum[x - 1][y - 1];
}
void main(){
    n = read(); m = read(); t = read();seed = read(); getdata();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
        }
    long long ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            int p = 1, k = i;
            while(k > 0){
                while(p + 1 <= j &&getsum(k,p + 1,i,j) >= 2)p++;
                if(getsum(k,p,i,j) >= 2)ans += p;
                k--;
            }
        }
    }
    printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    freopen("potato.in","r",stdin);
    freopen("potato.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}