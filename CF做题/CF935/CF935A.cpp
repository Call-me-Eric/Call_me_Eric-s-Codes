#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n;
signed main(){
    n = read();int cnt = 0;
    for(int i = sqrt(n);i;i--){
        if(n % i == 0){cnt += 2;}
    }
    int x = sqrt(n);if(x * x == n)cnt--;
    printf("%d\n",cnt - 1);
    return 0;
}