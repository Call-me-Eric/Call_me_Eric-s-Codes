#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch =  getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, sum;
signed main(){
    n = read();
    for(int i = 1;i <= n;i++)sum += read();
    int mx1 = 0, mx2 = 0;
    for(int i = 1;i <= n;i++){
        int t = read();
        if(t > mx1){mx2 = mx1;mx1 = t;}
        else if(t > mx2){mx2 = t;}
    }
    puts((mx1 + mx2 >= sum) ? "YES" : "NO");
    return 0;
}