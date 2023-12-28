#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f  = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch= getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int b, p, f, h, c;
signed main(){
int T = read();
while(T--){
    b = read(); p = read(); f = read();
    h = read(); c = read();
    if(h < c){swap(h, c);swap(p, f);}
    int a = min(b / 2, p);
    int ans = a * h;
    ans += min((b - 2 * a) / 2,f) * c;
    printf("%d\n",ans);
}
    return 0;
}