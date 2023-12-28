#include<bits/stdc++.h>
using namespace std;
int n, m, t;
signed main(){
    t = 100;
    srand(time(0));
    mt19937 rnd(rand());
    printf("%d\n",t);
    while(t--){
        n = rnd() % 41 + 1;m = rnd() % 41 + 1;
        while(n < 0)n += 40;while(m < 0)m += 40;
        printf("%d %d\n",n,m);
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                unsigned int x = rnd() % (int)10;
                printf("%u ",x);
            }
            puts("");
        }
    }
    return 0;
}