# 期望概率DP

## 例题A题解

首先，对于随机变量 $X$  
如果设随机变量 $Y$ 的取值集合是 $I(Y)$，那么有全期望公式
$$
E(X)=\sum_{y\in I(Y)}E(X|Y=y)\times P(Y=y)
$$
其中，$E(X|Y=y)$ 表示在 $Y=y$ 的条件下 $X$ 的期望取值。  
对于这道题，长度增加一对答案的贡献是 $3E^2(x)+3E(x)+1$，其中 $E^2(x)$ 与 $E(x)$ 分别表示长度平方的期望和长度的期望。  
但是期望没有乘法，也就是说，$E(x)\times E(x)=E^2(x)$ **不成立**。  
那怎么办呢？  
不难发现，长度增加一对长度平方的贡献是 $2x+1$。  
总结一下，如果设第 $x$ 位成功的概率是 $P(x)$，那么有：
$$
E(x)=(E(x-1)+1)\times P(x)\\
E^2(x)=P(x)\times (E^2((x-1))+2\times E(x-1) + 1) + (1 - P(x))\times 0
$$
那么这一位对答案的贡献就是
$$
ans=ans+P(x)\times (3E^2(x)+3E(x)+1)
$$
`question`：为什么不用上面的方法更新答案？  
`answer`：其实你求的长度平方期望和长度期望从某种意义上说，其实是**到这一位为止连续的**长度的期望，如果用上文的方法更新答案，答案的意义就变成了**到最后一位为止连续的**长度的三次方的期望，当然不是答案啦！

## 例题A代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n;double p, pow3, pow1, pow2;
signed main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%lf",&p);
        pow3 += (3.0 * pow2 + 3.0 * pow1 + 1.0) * p;
        pow2 = (pow2 + 2.0 * pow1 + 1.0) * p;
        pow1 = (pow1 + 1.0) * p;
    }
    printf("%.1lf\n",pow3);
    return 0;
}
~~~

## 例题B题解

不难发现，如果 $j$ 在 $i$ 的候选列表中，排名为 $x$，且 $i$ 的候选列表长度为 $M_i$，那么 $i$ 选中 $j$ 的概率为
$$
P(i,j)=(1-p)^{x-1}\sum_{k=0}^{+\infty}p(1-p)^{M_i\times k}\\
=(1-p)^{x-1}p\sum_{k=0}^{+\infty}((1-p)^{M_i})^k
$$
我们知道 $\sum_{k=0}^{+\infty}r^k=\frac{1}{1-r}$  
于是上式变成了
$$
P(i,j)=\frac{(1-p)^{x-1}p}{1-(1-p)^{M_i}}
$$
然后考虑一对 $i,j,i<j$ 的贡献：$ans_{i,j}=\sum_{k=1}^n\sum_{l=1}^{k-1}P(i,k)\times P(j,l)$  
于是总贡献就是
$$
\sum_{i=1}^n\sum_{j=i+1}^n\sum_{k=1}^n\sum_{l=1}^{k-1}P(i,k)\times P(j,l)\\
=\sum_{i=1}^n\sum_{k=1}^nP(i,k)\times\sum_{j=i+1}^n\sum_{l=1}^{k-1}P(j,l)
$$
这玩应显然是二维数点，想怎么做就怎么做。

## 例题B代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, m;
vector<int> vec[maxn];
long double p;
struct BIT{
    long double c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,long double add){for(;x < n;x += lowbit(x))c[x] += add;}
    long double qry(int x){long double ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
}tree;
long double qpow(long double x,int a){
    long double res = 1;
    while(a){
        if(a & 1)res = res * x;
        x = x * x;a >>= 1;
    }
    return res;
}
signed main(){
    scanf("%d%d%Lf",&n,&m,&p);
    for(int i = 1;i <= m;i++){
        int x = read(), y = read();
        vec[x].push_back(y);
    }
    for(int i = 1;i <= n;i++)sort(vec[i].begin(),vec[i].end());
    long double ans = 0;
    for(int i = 1;i <= n;i++){
        if(vec[i].empty())continue;
        long double tm = p / (1.0 - qpow(1.0 - p,vec[i].size())), pw = tm;
        for(int j = 0;j < vec[i].size();j++,pw *= (1.0 - p)){
            ans += pw * tree.qry(n - vec[i][j]);
            // printf("%Lf %Lf\n",pw,tree.qry(n - vec[i][j]));
        }
        pw = tm;
        for(int j = 0;j < vec[i].size();j++,pw *= (1.0 - p)){
            tree.upd(n - vec[i][j] + 1,pw);
            // printf("%Lf\n",pw);
        }
        // printf("%.2Lf\n",ans);
    }
    printf("%.2Lf\n",ans);
    return 0;
}
~~~

## 例题C题解

设 $f_{i,j}$ 表示在第 $i$ 秒，一共有 $j$ 个人进入了电梯的概率。  
于是有 $f_{i,j}=f_{i-1,j}\times(1-p)+f_{i-1,j-1}\times p$  
特别的，在所有人都进入电梯之后，不会再有人进入电梯，也就是说，$f_{i,n}\gets f_{i-1,n}$。

## 例题C代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e3 + 10;
int n, t;
double p, f[maxn][maxn];
signed main(){
    n = read();scanf("%lf",&p);t = read();
    f[0][0] = 1;
    for(int i = 1;i <= t;i++){
        f[i][0] = f[i - 1][0] * (1.0 - p);
        for(int j = 1;j <= n;j++){
            f[i][j] = f[i - 1][j - 1] * p + f[i - 1][j] * (1.0 - p);
        }
        f[i][n] += f[i - 1][n] * p;
    }
    double ans = 0;
    for(int i = 0;i <= n;i++)ans += 1.0 * i * f[t][i];
    printf("%.7lf\n",ans);
    return 0;
}
~~~

## 例题D题解

首先发现边数量很大，不太好做，考虑算经过点的期望。  
如果设 $f_i$ 表示经过点 $i$ 的期望次数，那么有：
$$
f_1=1+\sum_{(1,j)\in E}\frac{f_j}{deg_j}\\
f_i=\sum_{(i,j)\in E}\frac{f_j}{deg_j}
$$
这个东西显然可以[高斯消元](https://oi-wiki.org/math/numerical/gauss/)。  
然后经过每条边 $E_k:(i,j)$ 的期望次数就是
$$
F_k=\frac{f_i}{deg_i}+\frac{f_j}{deg_j}
$$
显然贪心的让经过期望次数较大的边赋予较小的编号，然后就没了。

## 例题D代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 501;
int nn, m, st[maxn * maxn], ed[maxn * maxn];
double a[maxn][maxn],ans[maxn],d[maxn * maxn],E[maxn * maxn];
vector<int> e[maxn];
void gauss(int n){
    for(int i = 1;i <= n;i++){
        int Max = i;
        for(int j = i + 1;j <= n;j++){
            if(a[j][i] > a[Max][i]){
                Max = j;
            }
        }
        if(Max != i)
            for(int j = 1;j <= n + 1;j++){
                swap(a[i][j],a[Max][j]);
            }
        if(!a[i][i]){
            puts("No Solution");
            return;
        }
        for(int j = 1 + i;j <= n;j++){
            if(a[i][j]){
                double tmp = a[j][i] / a[i][i];
                for(int k = 1;k <= n + 1;k++){
                    a[j][k] -= (a[i][k] * tmp);
                }
            }
        }
    }
    for(int i = n;i > 0;i --){
        for(int j = i + 1;j <= n;j++){
            a[i][n + 1] -= a[i][j] * ans[j];
        }
        ans[i] = a[i][n + 1] / a[i][i];
    }
    return;
}
signed main(){
    scanf("%d%d",&nn,&m);
    int x, y;
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
        d[x] += 1.0;d[y] += 1.0;
        st[i] = x;ed[i] = y;
    }
    for(int i = 1;i < nn;i++){
        a[i][i] = 1.0;
        for(int j = 0,len = e[i].size();j < len;j++){
            if(e[i][j] != nn){
                a[i][e[i][j]] = -1.0 / d[e[i][j]];
            }
        }
    }
    a[1][nn] = 1.0;
    gauss(nn - 1);
    for(int i = 1;i <= m;i++){
        E[i] = ans[st[i]] / d[st[i]] + ans[ed[i]] / d[ed[i]];
    }
    sort(E + 1,E + 1 + m);
    double res = 0;
    for(int i = 1;i <= m;i++){
        res += E[i] * (m + 1.0 - i);
    }
    printf("%.3lf\n",res);
    return 0;
}

~~~

## 例题E题解

我们不妨设 $f_{i,0/1}$ 分别表示与第一位颜色 相同/不同 的期望答案。  
于是有
$$
f_{i,0}=\sum_{j=1}^{i-1}f_{j,0}\times\frac{1}{m^{i-j-1}}\times(i-j)\times(1-\frac{2}{m})+f_{j,1}\times\frac{1}{m^{i-j-1}}\times(i-j)\times(1-\frac{1}{m})\\
f_{i,1}=\sum_{j=1}^{i-1}f_{j,0}\times(i-j)\times\frac{1}{m^{i-j}}
$$
最终答案就是
$$
\frac{1}{m^n}\times n+\sum_{i=1}^{n-1}\frac{1}{m^{i-1}}\times f_{n-i+1,0}\times i^2
$$
其中 $i^2$ 的意义是 给第一颗珠子找起始位置 $\times$ 相同的颜色的贡献。

## 例题E代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 300;
int n, m;
double pw[maxn], f[maxn][2];
signed main(){
    n = read(); m = read();pw[0] = 1;
    for(int i = 1;i <= n;i++)pw[i] = pw[i - 1] / (double)m;
    f[1][1] = 1;
    for(int i = 2;i <= n;i++){
        for(int j = 1;j < i;j++){
            f[i][0] += f[j][0] * (i - j) * pw[i - j - 1] * (1 - 2.0 / (double)m) + f[j][1] * (i - j) * pw[i - j - 1] * (1 - 1.0 / (double)m);
            f[i][1] += f[j][0] * (i - j) * pw[i - j];
        }
    }
    double ans = n * pw[n - 1];
    for(int i = 1;i < n;i++){
        ans += i * i * f[n - i + 1][0] * pw[i - 1];
    }
    printf("%.5lf\n",ans);
    return 0;
}
~~~

## 例题F题解

非常神奇的一道期望DP。  
首先，对一个数字进行操作，一定无法通过操作其他数字来等效替代。  
于是从大到小进行操作，遇到是一的就操作，最后会得出必须操作的总数量 $cnt$。  
然后考虑怎么继续。  
如果设 $f_i$ 表示从需要操作 $i$ 个点转移到需要操作 $i-1$ 个点需要进行的次数，那么显然有以下两种情况：

- 本次操作正确，选中了一个需要但没被操作的点，概率 $\frac{i}{n}$，期望次数 $1$。
- 本次操作错误，选中了一个不需要操作的点，那么这个时候需要操作的点数就变成了 $i+1$ 个。这个时候，选中了错误点进行一次操作，想要再变回 $i-1$ 个点，还需要从 $i+1$ 变成 $i$，再从 $i$ 变成 $i-1$，概率 $\frac{n - i}{n}$，期望次数 $1+f_{i+1}+f_{i}$。

综上所述，我们得到柿子
$$
f_{i}=\frac{i}{n}+(1+f_{i+1}+f_{i})\frac{n-i}{n}\\
\iff f_{i}=\frac{n+(n-i)f_{i+1}}{i}
$$
然后回头看题干要求：剩余步数小于等于 $k$ 时直接走到位置。  
那么比较一下需要进行的操作次数和剩余步数，如果需要的小于剩余的，显然进行需要的就可以直接到达答案，否则答案就是 $k+\sum_{i=k+1}^{cnt}f_i$

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
const int maxn = 1e5 + 10, mod = 1e5 + 3;
int n, k;bool book[maxn];
int f[maxn];
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
signed main(){
    n = read();k = read();int cnt = 0, pw = 1;
    for(int i = 1;i <= n;i++){book[i] = read();}
    for(int i = n;i;i--){
        pw = pw * i % mod;
        if(book[i]){
            cnt++;
            for(int j = sqrt(i);j;j--){
                if(i % j)continue;
                book[i / j] ^= 1;
                if(j * j != i)book[j] ^= 1;
            }
        }
    }
    f[n + 1] = 0;int ans = 0;
    if(cnt > k){
        ans = k;
        for(int i = n;i;i--){f[i] = (n + (n - i) * f[i + 1] % mod) % mod * qpow(i,mod - 2) % mod;}
        for(int i = k + 1;i <= cnt;i++)ans = (ans + f[i]) % mod;
    }
    else ans = cnt;
    printf("%lld\n",ans * pw % mod);
    return 0;
}
~~~

## 例题G题解

设 $f_{i,j,k}$ 表示现在有 $i$ 个挑战，其中成功了 $j$ 次，剩余背包容量是 $k$（$k$ 可以为负）这种情况出现的概率。  
那么显然有：
$$
f_{i,j,k}=f_{i - 1,j-1,k-a_i}\frac{p_i}{100}+f_{i-1,j,k}\frac{100-p_i}{100}
$$
很好理解，一个是成功，一个是不成功。  
最后答案就是 $\sum_{j=m}^n\sum_{i=0}^{200}f_{n,j,i}$。  
对于出现背包容量为负的情况，直接加上一个 $200$ 就解决了。

## 例题G代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e2 + 10;
int n, m, k, a[maxn], p[maxn];
double f[maxn][maxn][maxn * 2];
signed main(){
    n = read(); m = read(); k = min(read(), n) + 2e2;
    for(int i = 1;i <= n;i++)p[i] = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    f[0][0][k] = 1;
    for(int i = 1;i <= n;i++)
        for(int j = 0;j <= n;j++)
            for(int k = 4e2;k + 1;k--){
                f[i][j][k] = f[i - 1][j][k] * (100.0 - p[i]) / 100.0;
                if(j != 0)f[i][j][k] += f[i - 1][j - 1][k - a[i]] * p[i] / 100.0;
            }
    double ans = 0;
    for(int j = m;j <= n;j++)
        for(int i = 2e2;i <= 4e2;i++)
            ans += f[n][j][i];
    printf("%.6lf\n",ans);
    return 0;
}
~~~
