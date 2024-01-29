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
const int maxn = 200 + 10, mod = 998244353;
struct Matrix{
    int n, m;
    int a[maxn][maxn];
    Matrix(int n = 0,int m = 0):n(n),m(m){for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)a[i][j] = 0;}
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix(a.n,b.m);
        for(int i = 1;i <= a.n;i++)
            for(int k = 1;k <= b.n;k++)
                for(int j = 1;j <= b.m;j++)
                    c.a[i][j] = (c.a[i][j] + (a.a[i][k] * b.a[k][j] % mod)) % mod;
        return c;
    }
}A,B;
int det(int n,int mod,int a[][maxn]){
    int res = 1, f = 1;
    for(int i = 1;i <= n;i++){
        int k = i;
        for(int j = i;j <= n;j++)if(a[j][i]){k = j;break;}
        if(!a[k][i])return 0;
        for(int j = k + 1;j <= n;j++)if(a[j][i] && a[j][i] < a[k][i])k = j;
        if(i != k){swap(a[i],a[k]);f = -f;}
        for(int j = i + 1;j <= n;j++){
            if(a[j][i] > a[i][i]){swap(a[j],a[i]);f = -f;}
            while(a[j][i]){
                int l = a[i][i] / a[j][i];
                for(int k = i;k <= n;k++)a[i][k] = (a[i][k] + (-l + mod) % mod * a[j][k] % mod) % mod;
                swap(a[j],a[i]);f = -f;
            }
        }
        res = res * a[i][i] % mod;
    }
    return (res * f + mod) % mod;
}

int k;
int n[maxn], m[maxn];
void solve(){
    k = read();
    for(int i = 1;i <= k;i++)n[i] = read();
    A = Matrix(n[1],n[1]);
    for(int i = 1;i <= n[1];i++)A.a[i][i] = 1;
    for(int i = 2;i <= k;i++)m[i] = read();
    for(int i = 2;i <= k;i++){
        B = Matrix(n[i - 1],n[i]);
        for(int j = 1;j <= m[i];j++){
            int u = read(), v = read();
            B.a[u][v] = 1;
        }
        A = A * B;
    }
    printf("%lld\n",det(n[1],mod,A.a));
}
void main(){
    int T = read();
    while(T--){solve();}
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