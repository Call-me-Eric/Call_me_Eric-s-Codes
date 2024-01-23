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
const int maxn = 600 + 10;
int n, mod;
int a[maxn][maxn];
int solve(int n,int mod,int a[][maxn]){//注：这个是可以解决mod非质数的情况，且时间复杂度也是 $O(n^3)$
    int res = 1, f = 1;
    for(int i = 1;i <= n;i++){
        int k = i;
        for(int j = i;j <= n;j++)if(a[j][i]){k = j;break;}//先找到一个a_{i,i}\neq0的
        if(!a[k][i])return 0;
        for(int j = k + 1;j <= n;j++)if(a[j][i] && a[j][i] < a[k][i])k = j;//然后找一个尽可能小的（后面要辗转相除）
        if(i != k){swap(a[i],a[k]);f = -f;}//交换两行，行列式取值取反
        for(int j = i + 1;j <= n;j++){
            if(a[j][i] > a[i][i]){swap(a[j],a[i]);f = -f;}//交换两行，行列式取值取反
            while(a[j][i]){//辗转相除
                int l = a[i][i] / a[j][i];
                for(int k = i;k <= n;k++){a[i][k] = (a[i][k] + (-l + mod) % mod * a[j][k] % mod) % mod;}
                swap(a[j],a[i]);f = -f;
            }
        }
        res = res * a[i][i] % mod;
    }
    return (mod + f * res) % mod;
}
void main(){
    n = read(); mod = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            a[i][j] = read();
    printf("%lld\n",solve(n,mod,a));
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