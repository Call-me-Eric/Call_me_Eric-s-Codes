#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, maxp = 110;
int n, m, p;
int pre[maxn], t[maxn], sum[maxn];

int f[maxp][maxn], now;
int calcy(int x){return sum[x] + f[now][x];}
int calcb(int x,int k){return calcy(x) - t[k] * x;}
int cross(int a,int b,int c){
    int x1__ = b - a, x2__ = c - b, y1__ = calcy(b) - calcy(a), y2__ = calcy(c) - calcy(b);
    return x1__ * y2__ - x2__ * y1__;
}

int que[maxn], head, tail;
signed main(){
    n = read(); m =  read(); p = read();
    for(int i = 2;i <= n;i++){pre[i] = pre[i - 1] + read();}
    for(int i = 1;i <= m;i++){int H = read(),T = read();t[i] = T - pre[H];}
    sort(t + 1,t + 1 + m);
    for(int i = 1;i <= m;i++)sum[i] = sum[i - 1] + t[i];

    for(int i = 1;i <= m;i++){f[1][i] = i * t[i] - sum[i];}
    int ans = f[1][m];
    for(int i = 2;i <= p;i++){
        head = 1;tail = 0;now = i - 1;que[++tail] = 0;
        for(int j = 1;j <= m;j++){
            while(head < tail && calcb(que[head + 1],j) < calcb(que[head],j))head++;
            int pos = que[head];f[i][j] = f[i - 1][pos] + (j - pos) * t[j] + sum[pos] - sum[j];
            while(head < tail && cross(j,que[tail],que[tail - 1]) > 0)tail--;
            que[++tail] = j;
        }
        ans = min(ans,f[i][m]);
    }
    printf("%lld\n",ans);
    return 0;
}