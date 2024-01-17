#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch =  getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch  = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int a, b, c, d;
int ans;
signed main(){
    freopen("theatre.in","r",stdin);
    freopen("theatre.out","w",stdout);
    read();read();
    a = b = c = d = INT_MIN; ans = INT_MAX;
    int u, v, id = 0, res = 0;
    for(int i = read();i;i--){
        u = read(); v = read();
        a = max(a,u + v);
        b = max(b,u - v);
        c = max(c,-u + v);
        d = max(d,-u - v);
    }
    int m = read();
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        res = max(max(a - u - v,b - u + v),max(c + u - v,d + u + v));
        if(res < ans){
            ans = res;
            id = i;
        }
    }
    printf("%lld\n%lld\n",ans,id);
    return 0;
}