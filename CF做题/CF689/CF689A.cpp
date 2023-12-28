#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n;
int opt[12];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){scanf("%1d",&opt[i]);}
    bool l = true, r = true,u = true, d = true;
    for(int i = 1;i <= n;i++){
        if(opt[i] == 0){l = r = d = false;continue;}
        if(opt[i] % 3 == 1)l = false;
        if(opt[i] <= 3) u = false;
        if(opt[i] >= 7 && opt[i] != 8) d = false;
        if(opt[i] % 3 == 0)r = false;
    }
    puts((l | r | u | d) ? "NO" : "YES");
    return 0;
}