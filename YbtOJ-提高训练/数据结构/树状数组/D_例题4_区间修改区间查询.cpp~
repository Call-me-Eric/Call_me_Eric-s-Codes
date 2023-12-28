#include<bits/stdc++.h>
#define lowbit(x) (x) & (-(x))
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 1e6 + 10;
int a[maxn], c1[maxn * 4],c2[maxn * 4];
void upd1(int x,int k){for(;x <= n;x += lowbit(x))c1[x] += k;}
void upd2(int x,int k){for(;x <= n;x += lowbit(x))c2[x] += k;}
void update(int l,int r,int k){
    upd1(l,k);upd1(r + 1,-k);
    upd2(l,k * (l - 1));upd2(r + 1,-k * r);
}
int sum1(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c1[x];return ans;}
int sum2(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c2[x];return ans;}
int sum(int l,int r){
    return (r * sum1(r) - sum2(r)) - ((l - 1) * sum1(l - 1) - sum2(l - 1));
}
signed main(){
    n = read(); m = read();int op, x, y, z;
    for(int i = 1;i <= n;i++){a[i] = read();update(i,i,a[i]);}
    while(m--){
        op = read(); x = read(); y = read();
        if(op == 1){
            z = read();
            update(x,y,z);
        }
        else {
            printf("%d\n",sum(x,y));
        }
    }
    return 0;
}
