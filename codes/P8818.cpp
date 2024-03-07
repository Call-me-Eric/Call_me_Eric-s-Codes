#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10,  MAX = LONG_LONG_MAX,MIN = LONG_LONG_MIN;
int n, m, q;
int lg[maxn];
struct ST{
    int len;
    int maxx[maxn][21],minn[maxn][21];
    void init(){
        for(int j = 1;j <= lg[len];j++)
        for(int i = 1;i + (1 << (j - 1)) <= len;i++){
            maxx[i][j] = max(maxx[i][j - 1],maxx[i + (1 << (j - 1))][j - 1]);
            minn[i][j] = min(minn[i][j - 1],minn[i + (1 << (j - 1))][j - 1]);
        }
    }
    int query(bool opt,int l,int r){//opt == 0 => min;opt == 1 => max
        int k = lg[r - l + 1];
        return (!opt) ? min(minn[l][k], minn[r - (1 << k) + 1][k])
                   : max(maxx[l][k], maxx[r - (1 << k) + 1][k]);
    }
}amax,amin,bmax,bmin,negative,positive;//negative:a负数最大值;positive:a非负最小值
signed main(){
    n = read(); m = read();q = read();
    lg[0] = -1;for(int i = 1;i <= max(n,m);i++)lg[i] = lg[i >> 1] + 1;
    for(int i = 1;i <= n;i++){
        int x = read();
        amax.maxx[i][0] = x;
        amin.minn[i][0] = x;
        negative.maxx[i][0] = (x >= 0 ? MIN : x);
        positive.minn[i][0] = (x < 0 ? MAX : x);
    }
    amax.len = amin.len = negative.len = positive.len = n;
    amax.init();amin.init();negative.init();positive.init();
    for(int j = 1;j <= m;j++){
        int x = read();
        bmax.maxx[j][0] = x;
        bmin.minn[j][0] = x;
    }
    bmax.len = bmin.len = m;
    bmax.init();bmin.init();
    for(int que = 1;que <= q;que++){
        int la = read(), ra = read(), lb = read(), rb = read();
        int am = amax.query(1,la,ra),ai = amin.query(0,la,ra),ne = negative.query(1,la,ra);
        int po = positive.query(0,la,ra), bm = bmax.query(1,lb,rb), bi = bmin.query(0,lb,rb);
        int ans = MIN;
        ans = max(am * (am >= 0 ? bi : bm), ans);
        ans = max(ai * (ai >= 0 ? bi : bm), ans);
        if(ne != MIN) ans = max(ans,ne * (ne >= 0 ? bi : bm));
        if(po != MAX) ans = max(ans,po * (po >= 0 ? bi : bm));
        printf("%lld\n",ans);
    }
    return 0;
}