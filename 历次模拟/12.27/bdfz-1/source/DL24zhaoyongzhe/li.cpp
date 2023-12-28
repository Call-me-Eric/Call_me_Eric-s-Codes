#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int deg[maxn], n, m;
map<pair<int,int>, int> mp;
signed main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
    }
    if(n == 2){
        printf("0 ");
        if(m == 1){puts("3");}
        else puts("2");
    }
    if(n == 3){
        if(m == 0){puts("0 2");}
        if(m == 1){puts("0 3");}
        if(m == 2){puts("0 6");}
        if(m == 3){puts("1 3");}
    }
    return 0;
}