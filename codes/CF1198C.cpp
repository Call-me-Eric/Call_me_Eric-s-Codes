#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
int book[maxn * 3], ans[maxn];
signed main(){
int T = read();
while(T--){
    n = read() * 3;m = read();int cnt = 0;
    for(int i = 1;i <= n;i++)book[i] = 0;
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        if(!book[u] && !book[v] && cnt < n / 3){book[u] = book[v] = 1;ans[++cnt] = i;}
    }
    if(cnt >= n / 3){
        puts("Matching");
        for(int i = 1;i <= n / 3;i++){printf("%d ",ans[i]);}
        puts("");
    }
    else{
        puts("IndSet");cnt = 0;
        for(int i = 1;i <= n && cnt < n / 3;i++){
            if(!book[i]){cnt++;printf("%d ",i);}
        }
        puts("");
    }
}
    return 0;
}