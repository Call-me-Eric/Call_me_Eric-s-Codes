#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, p;
const int maxn = 1e6 + 10;
int fa[maxn], tot[maxn];
int getf(int x){
    if(fa[x] == x)return x;
    int tmp = fa[x];
    fa[x] = getf(fa[x]);
    tot[x] += tot[tmp];
    return fa[x];
}
signed main(){
    int l, r, k;
    n = read(); m = read(); p = read();
    for(int i = 0;i <= n;i++){fa[i] = i;}
    for(int i = 1;i <= m;i++){
        l = read(); r = read(); k = read();
        int fl = getf(l - 1), fr = getf(r);
        if(fl == fr){
            if((tot[r] - tot[l - 1] + p) % p != k){
                printf("%d\n",i - 1);
                return 0;
            }
        }
        else {
            fa[fl] = fr;
            tot[fl] = k - tot[r] - tot[l - 1];
        }
    }
    printf("%d\n",m);
    return 0;
}
