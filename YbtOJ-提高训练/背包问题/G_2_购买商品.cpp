#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch  =getchar();}
    return x * f;
}
int n, m, M, _M, _val;
const int maxn = 21, maxm = 51;//什么**网站啊这数据范围都写得啥呀
int a[maxn],b[maxn];
int a1[maxm],b1[maxm];
int f[1010000];
void dfs(int step,int value,int cost){
    if(cost > M)return;
    if(step > m){
        if(value > _val || (value == _val && cost < _M)){
            _M = cost;
            _val = value;
        }
        return;
    }
    dfs(step + 1,value + b[step],cost + a[step]);
    dfs(step + 1,value,cost);
}
signed main(){
    M = read(); m = read();
    for(int i = 1;i <= m;i++){a[i] = read();b[i] = read();}
    n = read();
    for(int i = 1;i <= n;i++){a1[i] = read();b1[i] = read();}
    dfs(1,0,0);
    M -= _M;
    for(int i = 1;i <= n;i++){
        for(int j = a1[i];j <= M;j++){
            f[j] = max(f[j],f[j - a1[i]] + b1[i]);
        }
    }
    printf("%d\n",f[M]);
    return 0;
}