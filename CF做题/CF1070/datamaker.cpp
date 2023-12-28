#include<bits/stdc++.h>
using namespace std;
signed main(){
    srand(time(0));mt19937 rnd(rand());
    int n = 2000;printf("%d\n",n);
    long long lst = -1;
    for(int i = 1;i <= n;i++){
        long long sd = rnd() % (1ll << 32);
        long long x1 = sd >> 24ll;sd -= (x1 << 24ll);
        long long x2 = sd >> 16ll;sd -= (x2 << 16ll);
        long long x3 = sd >> 8ll;sd -= (x3 << 8ll);
        long long x4 = sd;
        printf("%c%lld.%lld.%lld.%lld/%d\n",((rnd() & 1) ? '-' : '+'),x1,x2,x3,x4,32 - (rnd() % 4));
    }
    return 0;
}