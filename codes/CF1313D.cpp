#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, k;
const int maxn = 1e5 + 10, INF = 0x3f3f3f3f;
struct node{int op, w ,d;node(int o = 0,int w = 0,int d = 0):op(o),w(w),d(d){}}p[maxn * 2];
int tot;
int d[10], tmp[10 + (1 << 8)];
int f[maxn * 2][10 + (1 << 8)];
bool operator < (node a,node b){if(a.w == b.w)return a.op < b.op;return a.w < b.w;}
signed main(){
    n = read(); m = read(); k = read();
    for(int i = 1;i <= n;i++){
        p[++tot] = node(1,read(),i);
        p[++tot] = node(-1,read() + 1,i);
    }
    sort(p + 1,p + 1 + tot);
    for(int i = 1;i < (1 << k);i++)tmp[i] = tmp[i - (i & (-i))] + 1;
    for(int i = 0;i <= tot;i++)
        for(int j = 0;j < (1 << k);j++)
            f[i][j] = -INF;
    f[0][0] = 0;
    for(int j = 1;j <= k;j++)d[j] = -1;
    int now = 0;
    for(int i = 1;i <= tot;i++){
        int at = -1;
        if(p[i].op == 1){
            for(int j = 1;j <= k;j++)
                if(d[j] == -1){at = j; d[j] = p[i].d;break;}
            for(int j = 0;j <= now;j++){
                if((j & now) == j){
                    f[i][j] = max(f[i][j],f[i - 1][j] + (tmp[j] & 1) * (p[i].w - p[i - 1].w));
                    f[i][j | (1 << (at - 1))] = max(f[i][j | (1 << (at - 1))],f[i - 1][j] + (tmp[j] & 1) * (p[i].w - 1 - p[i - 1].w) + ((tmp[j] + 1) & 1));
                }
            }
            now |= (1 << (at - 1));
        }
        else {
            for(int j = 1;j <= k;j++)
                if(d[j] == p[i].d){at = j; d[j] = -1;break;}
            now ^= (1 << (at - 1));
            for(int j = 0;j <= now;j++){
                if((j & now) == j){
                    f[i][j] = max(f[i][j],f[i - 1][j] + (tmp[j] & 1) * (p[i].w - p[i - 1].w));
                    f[i][j] = max(f[i][j],f[i - 1][j | (1 << (at - 1))] + ((tmp[j] + 1) & 1) * (p[i].w - 1 - p[i - 1].w) + (tmp[j] & 1));
                }
            }
        }
    }
    printf("%lld\n",f[tot][0]);
    return 0;
}