#include<bits/stdc++.h>
using namespace std;
int range = 1e6;
signed main(){
    freopen("tmp.in","w",stdout);
    srand(time(0));mt19937 rnd(rand());
    int n = 1e5, q = 2e5;
    printf("%d %d\n",n, q);
    for(int i = 1;i <= n;i++)printf("%d ",rnd() % n + 1);puts("");
    for(int i = 2;i <= n;i++){printf("%d ",rnd() % (i - 1) + 1);}puts("");
    for(int i = 1;i <= q;i++){
        int u = rnd() % n + 1, v = rnd() % n + 1;
        if(u == v){v = (v + 1) % n + 1;}
        printf("%d %d\n",u,v);
    }
    return 0;
}