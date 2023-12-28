# Burnside引理与Polya定理

## 例题A题解

Polya模板。  
Polya定理给出，如果设有限集 $D$ 的置换群为 $G$，$C$ 是由全体用 $m$ 种颜色为 $D$ 中颜色染色的方案构成的集合，每个置换 $\sigma$ 的循环总数是 $c(\sigma)$，那么 $G$ 诱导的 $C$ 的等价类数量 $N=\frac{1}{|G|}\sum_{\sigma\in G}m^{c(\sigma)}$。  
在这道题中：

- $D$ 就是珠子的位置 $0,1,\dots,n-1$（这里从 $0$ 开始计数），颜色数量是 $k=n$。
- 每个置换 $\sigma_i=(i,2i,\dots,0),(i+k,2i+k,\dots,k)\dots$（表示整体向右移 $i$ 位的这个循环），一共有 $n$ 个置换。
- 且有 $c(\sigma_i)=\gcd(n,i)$（我们知道一个循环长度应该是 $\frac{lcm(n,i)}{i}$，在一个置换中，所有的 $i$ 都应该出现，故总共置换数应该是 $\frac{n}{(\frac{lcm(n,i)}{i})}=\gcd(n,i)$）。
- 所以最终答案是 $ans=\frac{1}{n}\sum_{i=1}^nk^{\gcd(n,i)}$。

但是这道题的 $n$ 高达 $10^9$，这不直接T飞了？  
怎么办？  
考虑优化这个式子：  
我们发现，对于 $\gcd(n,i)$ 相同的 $i$，贡献是一样的，那么能不能在这上面优化呢？  
设 $\gcd(n,i) = x$，那么就有 $\gcd(\frac{n}{x},\frac{i}{x})=1$，也就是说，我们要统计的 $\gcd(n,i) = x$ 的个数就是 $\gcd(\frac{n}{x},\frac{i}{x})=1$ 的个数。  
后者显然是欧拉函数，也就是说，公约数为 $x$ 的 $i$ 有 $\varphi(\frac{n}{x})$ 个。  
那么我们枚举约数，答案变成 $\frac{1}{n}\sum_{p|n}\varphi(\frac{n}{p})\times k^p$。  
然后就没了。

## 例题A代码

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int mod, n;
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
int phi(int n){
    int ans = n;
    for(int i = 2;i * i <= n;i++){
        if(n % i == 0){
            ans = ans / i * (i - 1);
            while(n % i == 0)n /= i;
        }
    }
    if(n > 1)ans = ans / n * (n - 1);
    return ans;
}
signed main(){
    for(int Test = read();Test;Test--){
        n = read();mod = read();
        int ans = 0;
        for(int i = 1;i * i <= n;i++){
            if(n % i != 0)continue;
            ans = (ans + phi(i) * qpow(n,n / i - 1) % mod) % mod;
            if(i * i != n)ans = (ans + phi(n / i) * qpow(n,i - 1) % mod) % mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
~~~

## 例题B题解

不难发现，这道题与上一道题的唯一区别是，这道题加入了翻转这个操作。  
我们想想这个操作会带来什么新的置换。  
我们分类讨论下，分成环长度是偶数和环长度是奇数。  

### 先来看环长度是偶数的情况

置换有移位和翻转两种，移位的那种第一篇题解已经说过了，我们主要看翻转这种情况。  
不难发现，每次翻转分为

- 以一对相对顶点顶点连线为对称轴翻转，这种情况共有 $\frac{n}{2}$ 种，每种的循环数量为 $\frac{n}{2} + 1$。
- 以一对相对边的中点连线为对称轴翻转，这种情况共有 $\frac{n}{2}$ 种，每种的循环数量为 $\frac{n}{2}$。

故答案就是
$$
ans=\frac{\sum_{i=1}^n\gcd(i,n)+\frac{n}{2}(m^{\frac{n}{2}+1}+m^{\frac{n}{2}})}{2n}
$$

### 然后再说长度是奇数的情况

置换有移位和翻转两种，移位的那种第一篇题解已经说过了，我们主要看翻转这种情况。  
而翻转相较于偶数情况简单了许多，只有以一个顶点和其相对的边的中点相连的直线翻转的情况，一共有 $n$ 种，每种的循环数量有 $\frac{n}{2}+1$个。  
故答案就是
$$
ans=\frac{\sum_{i=1}^n\gcd(i,n)+n\times m^{\frac{n}{2}+1}}{2n}
$$
没了。

## 例题B代码

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, m;
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x)if(a & 1)res = res * x;return res;}
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
signed main(){
    while((m = read()) , (n = read()), (n || m)){
        int ans = 0;
        for(int i = 1;i <= n;i++){ans += qpow(m,gcd(n,i));}
        if(n & 1){ans += n * qpow(m, n / 2 + 1);}
        else{ans += (n / 2) * (qpow(m,n / 2 + 1) + qpow(m,n / 2));}
        ans /= 2 * n;
        printf("%lld\n",ans);
    }
    return 0;
}
~~~

## 例题C题解

不难发现，计数循环其实不太好做，那就用Burnside吧。  
考虑进行整数拆分，然后统计每一个循环的不动点数量。  
不难发现，循环长度组成的集合相同的置换贡献相同。  
对于一个整数拆分 $n=b_1+b_2+\dots+b_k$，我们有：

- 对于在循环 $i$ 中的边，不动点（不发生改变的边）的数量有 $\lfloor\frac{b_i}{2}\rfloor$ 个
- 对于循环之间的边，不动点的数量有 $\gcd_{1\le i<j\le k}\gcd(b_i,b_j)$ 个。  

一共有 $n!$ 种排列，但是有两种重复情况：

- 同一个循环中，起始位置并不关心，需要乘上 $\frac{1}{b_i}$
- 相同长度循环是可以交换的，所以对于长度为 $l$ 的循环，如果有 $cnt_l$ 个，需要乘上 $\frac{1}{cnt_l}$

没了。

## 例题C代码

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 61;
int n, m, mod, ans, k, a[maxn];
int qpow(int x,int a){int res = 1;for(;a;a >>= 1, x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
int invv[maxn], pw[maxn], invpw[maxn];
void dfs(int sum,int rest,int inv,int lstnum, int cnt){
    if(rest == 0){
        // printf("%lld %lld\n",sum,inv);
        ans = (ans + qpow(m,sum) * inv) % mod;
        return;
    }
    for(int i = min(rest,lstnum);i;i--){
        int g = 0;for(int j = 1;j <= k;j++)g += __gcd(a[j],i);
        a[++k] = i;
        if(i == a[k - 1]){dfs(sum + i / 2 + g,rest - i,inv * invpw[cnt + 1] % mod * pw[cnt] % mod * invv[i] % mod,i,cnt + 1);}
        else dfs(sum + i / 2 + g,rest - i,inv * invv[i] % mod,i,1);
        k--;
    }
}
signed main(){
    n = read(); m = read();mod = read();pw[0] = invpw[0] = 1;
    for(int i = 1;i <= n;i++){
        invv[i] = qpow(i,mod - 2);
        pw[i] = pw[i - 1] * i % mod;
        invpw[i] = invpw[i - 1] * invv[i] % mod;
    }
    dfs(0,n,1,n,0);
    printf("%lld\n",ans);
    return 0;
}
~~~

## 例题D题解

首先看题干，发现这里的每个置换可以构成置换群，那就用Burnside定理。  
考虑对每个置换计数不动点，发现对每一个循环，需要所有的颜色都相同才是不动点。  
然后发现这玩应很像01背包，然后设 $f_{r,g,b}$ 表示已经染过了 $r,g,b$ 颜色的情况一共有多少个不动点。  
如果设第 $i$ 个循环长度是 $siz_i$
显然有：

$$
f_{r,g,b}\gets f_{r-siz_i,g,b} + f_{r,g-siz_i,b}+f_{r,g,b - siz_i}
$$

然后就没了，别忘了单元置换就好了。

## 例题D代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 70;
int n, m, r, g, b, mod;
int p[maxn];
int f[maxn][maxn][maxn];
int siz[maxn], tot;
bool book[maxn];
int calc(){
    for(int i = 1;i <= n;i++)book[i] = 0;
    for(int i = 0;i <= n;i++)
        for(int j = 0;j <= n;j++)
            for(int k = 0;k <= n;k++)
                f[i][j][k] = 0;
    tot = 0;
    for(int i = 1;i <= n;i++){
        if(!book[i]){
            tot++; int len = 0, u = i;
            while(!book[u]){book[u] = 1;u = p[u];len++;}
            siz[tot] = len;
        }
    }
    f[0][0][0] = 1;
    for(int l = 1;l <= tot;l++){
        for(int i = r;i + 1;i--){
            for(int j = g;j + 1;j--){
                for(int k = b;k + 1;k--){
                    if(i >= siz[l])f[i][j][k] += f[i - siz[l]][j][k];
                    if(f[i][j][k] >= mod)f[i][j][k] -= mod;
                    if(j >= siz[l])f[i][j][k] += f[i][j - siz[l]][k];
                    if(f[i][j][k] >= mod)f[i][j][k] -= mod;
                    if(k >= siz[l])f[i][j][k] += f[i][j][k - siz[l]];
                    if(f[i][j][k] >= mod)f[i][j][k] -= mod;
                }
            }
        }
    }
    return f[r][g][b];
}
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
signed main(){
    r = read(); g = read(); b = read(); m = read(); mod = read(); n = r + g + b;
    int ans = 0;
    for(int i = 1;i <= m;i++){
        for(int j = 1;j <= n;j++)p[j] = read();
        ans += calc();if(ans >= mod)ans -= mod;
    }
    for(int j = 1;j <= n;j++)p[j] = j;
    ans += calc();if(ans >= mod) ans -= mod;
    printf("%d\n",ans * qpow(m + 1,mod - 2) % mod);
    return 0;
}
~~~

## 例题E题解

不难发现，这道题有对于置换的限制。  
如果设 $f_{i,j}$ 表示颜色 $i\to j$ 的方案数，那么就有：
$$
ans=\frac{1}{n}\sum_{p|n}\varphi(p)\sum_{i,j}f^{\frac{n}{p}}_{i,j}
$$
没了。

## 例题E代码

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxk = 11, mod = 9973;
int n, m, k;
struct Matrix{
    int a[maxk][maxk];
    Matrix(int x = 0){
        for(int i = 1;i <= m;i++)
            for(int j = 1;j <= m;j++)
                a[i][j] = 0;
        if(x != 0)
            for(int i = 1;i <= m;i++)a[i][i] = 1;
    }
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix(0);
        for(int i = 1;i <= m;i++)
            for(int k = 1;k <= m;k++)
                for(int j = 1;j <= m;j++)
                    c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j] % mod) % mod;
        return c;
    }
}A, B;

int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
Matrix qpow(Matrix x,int a){
    Matrix res = Matrix(1);
    while(a){
        if(a & 1)res = res * x;
        x = x * x;a >>= 1;
    }
    return res;
}

int phi(int n){
    int ans = n;
    for(int i = 2;i * i <= n;i++){
        if(n % i)continue;
        ans = ans / i * (i - 1);
        while(n % i == 0)n /= i;
    }
    if(n > 1)ans = ans / n * (n - 1);
    // printf("ans = %d\n",ans);
    return ans;
}
int calc(int x){
    B = qpow(A,n / x - 1);int ans = 0;
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= m;j++){
            if(A.a[i][j])ans = (ans + B.a[i][j]) % mod;
            // printf("(%lld,%lld) = %lld\n",i,j,ans);
        }
    // printf("ans = %lld\n",ans);
    return ans % mod;
}
signed main(){
int T = read();
while(T--){
    n = read();m = read(); k = read();
    memset(A.a,0,sizeof(A.a));
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= m;j++)
            A.a[i][j] = 1;
    for(int i = 1;i <= k;i++){
        int u = read(), v = read();
        A.a[u][v] = A.a[v][u] = 0;
    }
    int ans = 0;
    for(int i = 1;i * i <= n;i++){
        if(n % i == 0){
            ans = (ans + calc(i) * phi(i) % mod) % mod;
            if(n / i == i)continue;
            ans = (ans + calc(n / i) * phi(n / i) % mod) % mod;
        }
    }
    // printf("%lld\n",ans);
    ans = ans * qpow(n,mod - 2) % mod;
    printf("%lld\n",ans);
}
    return 0;
}
~~~

## 例题F题解

用Burnside引理，那么这道题相当于求每一个置换的不动点数量。  
发现每一个循环的不动点数目相同，也就是说，我们需要求的是长度为 $k$ 的方案。  
这个想怎么求怎么求，然后就没了。

## 例题F代码

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e3 + 10, mod = 1e8 + 7;
int f[maxn], S[maxn], Si[maxn];
int n, k;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
signed main(){
int T = read();
while(T--){
    n = read(); k = read();
    int ans = 0;Si[0] = 0;
    f[0] = S[0] = 1;
    for(int i = 1;i <= n;i++){
        if(i - 2 >= k)f[i] = (S[i - 1] - S[i - k - 2] + mod) % mod;
        else f[i] = S[i - 1];
        S[i] = (S[i - 1] + f[i]) % mod;
        Si[i] = (Si[i - 1] + f[i] * i) % mod;
    }
    for(int i = 1;i <= n;i++){
        int g =__gcd(i, n);
        if(g - 2 >= k){ans = (ans + g * (S[g - 1] - S[g - k - 2] + mod) % mod - (Si[g - 1] - Si[g - k - 2] + mod) % mod + mod) % mod;}
        else ans = (ans + g * (S[g - 1]) % mod - (Si[g - 1]) % mod + mod) % mod;
        if(k >= n)ans++;ans %= mod;
    }
    ans = ans * qpow(n,mod - 2) % mod;
    printf("%lld\n",ans);
}
    return 0;
}
~~~
