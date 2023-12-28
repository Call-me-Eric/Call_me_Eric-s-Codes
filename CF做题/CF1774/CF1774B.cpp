#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int a, n, m, k;
signed main(){
int T = read();
while(T--){
    n = read();m = read(); k = read();
    bool flag = true;
    int res = n % k;
    for(int i = 1;i <= m;i++){
        a = read();
        if(a - 1 == n / k){res--;}
        else if(a > n / k){flag = false;}
        // printf("flag = %d;",flag);
    }
    if(!flag || res < 0){
        // printf("%d %d,",flag,res);
        puts("NO");
    }
    else puts("YES");
}
    return 0;
}