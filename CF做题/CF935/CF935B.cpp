#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n;char ch;
signed main(){
    n = read();ch = getchar();while(ch == ' ' || ch == '\n')ch = getchar();
    int x = 0, y = 0, cnt = 0;
    bool side = (ch == 'U');
    if(ch == 'U')y = 1;else x = 1;
    for(int i = 2;i <= n;i++){
        // printf("%d %d %d\n",x,y,side);
        ch = getchar();
        if(ch == 'U'){
            if(x == y && side == 0){cnt++;side = 1;}
            y++;
        }
        else{
            if(x == y && side == 1){cnt++;side = 0;}
            x++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}