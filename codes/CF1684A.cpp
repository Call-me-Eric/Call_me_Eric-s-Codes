#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n;
char ch[100];
signed main(){
int T = read();
while(T--){
    scanf("%s",ch + 1);
    n = strlen(ch + 1);
    if(n == 2){putchar(ch[2]);}
    else{
        int x = 10;
        for(int i = 1;i <= n;i++)x = min(x,ch[i] - '0');
        putchar(x + '0');
    }
    puts("");
}
    return 0;
}