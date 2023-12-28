#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 110;
int n;char ch[maxn];
signed main(){
int T = read();
while(T--){
    n = read();scanf("%s",ch + 1);
    bool f = (ch[1] == '1');
    for(int i = 2;i <= n;i++){
        if(ch[i] == '1'){putchar(f ? '-' : '+');f = !f;}
        else putchar('+');
    }
    puts("");
}
    return 0;
}