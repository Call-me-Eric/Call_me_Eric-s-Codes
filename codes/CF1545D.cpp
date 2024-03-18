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
const int maxn = 1e3 + 10;
int n, k;
int a[maxn][maxn];
int sum[maxn],sum1[maxn];
void main(){
    n = read(); k = read() - 1;
    for(int i = 0;i <= k;i++)for(int j = 1;j <= n;j++){
        sum[i] += (a[i][j] = read());
        sum1[i] += (a[i][j] * a[i][j]);
    }
    int posk = 0, dert = sum[1] - sum[0], cnt = 0;
    for(int i = 1;i < k;i++){
        if(sum[i + 1] - sum[i] != dert){
            cnt++;posk = i;
            if(cnt == 3){posk = 1;break;}
        }
    }
    int sumv = 0, tr = 0;
    dert = (sum[posk] - sum[posk - 1]);
    if(posk >= 3){sumv = (sum1[2] + sum1[0] - 2 * sum1[1]);tr = sum[2] - sum[1];}
    else{sumv = (sum1[k] + sum1[k - 2] - 2 * sum1[k - 1]);tr = sum[k] - sum[k - 1];}
    dert = tr - dert;
    for(int i = 1;i <= n;i++){
        if(sum1[posk + 1] + sum1[posk - 1] - 2 * (sum1[posk] - a[posk][i] * a[posk][i] + (a[posk][i] + dert) * (a[posk][i] + dert)) == sumv){
            printf("%lld %lld\n",posk,a[posk][i] + dert);return;
        }
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