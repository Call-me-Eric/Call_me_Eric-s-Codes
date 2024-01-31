#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10,INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
int x[maxn], y[maxn];
int minn[maxn];
signed main(){
    n = read(); m = read();read();read();
    for(int i = 1;i <= n;i++)x[i] = read();
    for(int i = 1;i <= m;i++)y[i] = read();
    int ans = 0;
    y[0] = -INF, y[m + 1] = INF;m++;sort(y,y + m + 1);
    memset(minn,0x3f,sizeof(minn));
    for(int i = 1;i <= n;i++){
        int j = lower_bound(y,y + m + 1,x[i]) - y;j--;
        // printf("j=%lld\n",j);
        int dis = min(x[i] - y[j],y[j + 1] - x[i]);
        if(y[j + 1] - x[i] > dis || (x[i] - y[j] == dis && (minn[j] == INF || minn[j] == dis))){j--;}
        if(minn[j + 1] == INF || minn[j + 1] == dis)ans++;
        minn[j + 1] = min(minn[j + 1],dis);
        // printf("i=%lld : %lld\n",i,ans);
    }
    printf("%lld\n",n - ans);
    return 0;
}