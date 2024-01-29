#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
signed main(){
    int sg = 0;
    for(int T = read();T;T--){
        int x = read(), j = 1;
        for(j = 1;;j++){
            if(x >= j)x -= j;
            else break;
        }
        j--; sg ^= j;
    }
    puts(!sg ? "YES" : "NO");
    return 0;
}