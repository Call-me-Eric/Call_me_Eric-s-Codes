#include<bits/stdc++.h>
using namespace std;
int range = 1e6;
signed main(){
    freopen("tmp.in","w",stdout);
    srand(time(0));mt19937 rnd(rand());
    int n = 1e3;printf("%d\n",n);
    for(int i = 1;i <= n;i++){
        printf("%d %d\n",rnd() % (range * 2) - range,rnd() % (range * 2) - range);
    }
    return 0;
}