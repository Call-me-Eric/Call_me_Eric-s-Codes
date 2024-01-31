#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f= 1;char  ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int s, v1, v2, t1,t2;
signed main(){
    s = read(); v1 = read(); v2 = read(); t1 = read(); t2 = read();
    if(2 * t1 + s * v1 < 2 * t2 + s * v2){puts("First");}
    if(2 * t1 + s * v1 == 2 * t2 + s * v2){puts("Friendship");}
    if(2 * t1 + s * v1 > 2 * t2 + s * v2){puts("Second");}
    return 0;
}