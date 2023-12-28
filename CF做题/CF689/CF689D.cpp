#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int a[maxn], b[maxn];
int n, lg[maxn];
int minn[23][maxn], maxx[23][maxn];

int qrymin(int l,int r){
    if(r - l + 1 <= 0)return 0x3f3f3f3f3f3f3f;
    int k = lg[r - l + 1];return min(minn[k][l],minn[k][r - (1 << k) + 1]);
}
int qrymax(int l,int r){
    if(r - l + 1 <= 0)return -0x3f3f3f3f3f3f3f;
    int k = lg[r - l + 1];return max(maxx[k][l],maxx[k][r - (1 << k) + 1]);
}

int qryl(int x){
    int l = x, r = n, mid = 0;
    while(r - l >= 0){
        mid = l + r >> 1;
        if(qrymax(x,mid) < qrymin(x,mid)){l = mid + 1;}
        else r = mid - 1;
    }
    if(l <= n && qrymin(x,l) == qrymax(x,l))return l;
    return -1;
}
int qryr(int x){
    int l = x, r = n, mid = 0;
    while(r - l >= 0){
        mid = l + r >> 1;
        if(qrymax(x,mid) > qrymin(x,mid)){r = mid - 1;}
        else l = mid + 1;
    }
    if(r > 0 && qrymin(x,r) == qrymax(x,r))return r;
    return -1;
}
int query(int x){
    int l = qryl(x), r = qryr(x);
    // printf("x = %lld, l = %lld, r = %lld\n",x,l,r);
    // for(int i = x;i <= n;i++){
    //     printf("i = %lld : min=%lld max=%lld\n",i,qrymin(x,i),qrymax(x,i));
    // }
    if(l == -1 || r == -1)return 0;
    return r - l + 1;
}

signed main(){
    n = read();lg[0] = -1;
    for(int i = 1;i <= n;i++){lg[i] = lg[i >> 1] + 1;a[i] = read();maxx[0][i] = a[i];}
    for(int i = 1;i <= n;i++){b[i] = read();minn[0][i] = b[i];}
    for(int k = 1;k <= 22;k++)
        for(int i = 1;i + (1 << k) -  1 <= n;i++){
            maxx[k][i] = max(maxx[k - 1][i],maxx[k - 1][i + (1 << k - 1)]);
            minn[k][i] = min(minn[k - 1][i],minn[k - 1][i + (1 << k - 1)]);
        }
    int ans = 0;
    for(int l = n;l;l--){ans += query(l);}
    printf("%lld\n",ans);
    return 0;
}