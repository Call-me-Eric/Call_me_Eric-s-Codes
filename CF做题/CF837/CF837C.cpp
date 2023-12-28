#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 110;
int x[maxn], y[maxn];
int n, a, b;
bool check(int xi,int yi,int xj,int yj){
    if(xi > a || xj > a || yi > b || yj > b)return false;
    if(xi + xj > a && yi + yj > b)return false;
    return true;
}
signed main(){
    int ans = 0;n = read();a = read(); b = read();
    for(int i = 1;i <= n;i++)x[i] = read(), y[i] = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(i == j)continue;
            if(check(x[i],y[i],x[j],y[j]))ans = max(ans,x[i] * y[i] + x[j] * y[j]);
            if(check(y[i],x[i],x[j],y[j]))ans = max(ans,x[i] * y[i] + x[j] * y[j]);
            if(check(x[i],y[i],y[j],x[j]))ans = max(ans,x[i] * y[i] + x[j] * y[j]);
            if(check(y[i],x[i],y[j],x[j]))ans = max(ans,x[i] * y[i] + x[j] * y[j]);
        }
    }
    printf("%d\n",ans);
    return 0;
}