#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch =  getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int cf[maxn];
int n;
signed main(){
    n = read();int u = 0;
    for(int i = 1;i <= n;i++){
        u = read();
        if(!u)continue;
        cf[max(0,i - u)]++;
        cf[i]--;
    }
    int ans = n;
    for(int i = 1;i <= n;i++){
        cf[i] += cf[i - 1];
        if(cf[i] != 0){ans--;}
    }
    printf("%d\n",ans);
    return 0;
}