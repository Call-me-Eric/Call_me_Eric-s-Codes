#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n;
char ch[maxn];
int f[maxn][3];
signed main(){
    n = read();scanf("%s",ch + 1);
    int ans = 1;
    f[1][0] = f[1][1] = f[1][2] = 1;
    for(int i = 2;i <= n;i++){
        f[i][0] = f[i - 1][0] + (ch[i] != ch[i - 1]);
        f[i][1] = max(f[i - 1][1 + (ch[i] == ch[i - 1])] + 1,f[i - 1][1 + (ch[i] != ch[i - 1])]);
        f[i][2] = max(f[i - 1][2] + (ch[i] != ch[i - 1]),f[i - 1][0] + (ch[i] == ch[i - 1]));
        ans = max(max(ans,f[i][0]),max(f[i][1],f[i][2]));
    }
    printf("%d\n",ans);
    return 0;
}