#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1010;
double x[maxn], y[maxn];
struct point{
    int x, y, opt;
    point(int x = 0,int y = 0,int n = 0):x(x),y(y),opt(n){}
};
double edge[maxn][maxn];
double f[maxn][maxn][2];//f[i][j][opt]表示从顶点开始向左的第i个到向右的第j个连线最短长度,且终点在opt?j:i时的最小值
point fa[maxn][maxn][2];//fa[i][j][opt]表示对应的f[][][]由哪一个状态递推而来
int n;
stack<int> stk;
int pos(int x){return x <= 0 ? (x + n) : (x > n ? (x - n) : x);}
signed main(){
    n = read(); double high = -1e9;int top = 0;
    for(int i = 1;i <= n;i++){scanf("%lf%lf",&x[i],&y[i]);if(high < y[i]){high = y[i];top = i;}}
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            edge[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
    for(int i = 0;i <= n;i++)
        for(int j = 0;j <= n;j++)
            f[i][j][0] = f[i][j][1] = 1e18;
    f[0][0][1] = f[0][0][0] = 0;
    for(int len = 1;len < n;len++)
        for(int l = 0;l <= len;l++){
            int r = len - l;
            if(l && f[l][r][0] > f[l - 1][r][0] + edge[pos(top + l)][pos(top + l - 1)]){
                f[l][r][0] = f[l - 1][r][0] + edge[pos(top + l)][pos(top + l - 1)];
                fa[l][r][0] = point(l - 1,r,0);
            }
            if(l && f[l][r][0] > f[l - 1][r][1] + edge[pos(top + l)][pos(top - r)]){
                f[l][r][0] = f[l - 1][r][1] + edge[pos(top + l)][pos(top - r)];
                fa[l][r][0] = point(l - 1,r,1);
            }
            if(r && f[l][r][1] > f[l][r - 1][0] + edge[pos(top - r)][pos(top + l)]){
                f[l][r][1] = f[l][r - 1][0] + edge[pos(top - r)][pos(top + l)];
                fa[l][r][1] = point(l,r - 1,0);
            }
            if(r && f[l][r][1] > f[l][r - 1][1] + edge[pos(top - r)][pos(top - r + 1)]){
                f[l][r][1] = f[l][r - 1][1] + edge[pos(top - r)][pos(top - r + 1)];
                fa[l][r][1] = point(l,r - 1,1);
            }
        }
    point tmp = point(0,0,0);
    double ans = 1e18;
    for(int i = 0;i < n;i++){
        if(f[i][n - i - 1][0] < ans){
            ans = f[i][n - i - 1][0];
            tmp = point(i,n - 1 - i,0);
        }
        if(f[i][n - i - 1][1] < ans){
            ans = f[i][n - i - 1][1];
            tmp = point(i,n - i - 1,1);
        }
    }
    printf("%d ",top);
    while(tmp.x > 0 || tmp.y > 0){
        stk.push(tmp.opt ? pos(top - tmp.y) : pos(top + tmp.x));
        tmp = fa[tmp.x][tmp.y][tmp.opt];
    }
    while(!stk.empty()){printf("%d ",stk.top());stk.pop();}
    return 0;
}