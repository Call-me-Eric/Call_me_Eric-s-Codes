#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int n = 10;puts("10");srand(time(0));
    for(int i = 1;i <= n;i++)printf("%d ",(rand() % 10));
    int opt = 0, l = 0, r = 0, m = 100;puts("100");
    for(int i = 1;i <= m;i++){
        opt = (opt + rand()) % 2 + 1;l = l * rand() % n + 1;r = (r + rand() * rand()) % n + 1;
        if(l > r)swap(l, r);printf("%lld %lld %lld\n",opt,l,r);
    }
    return 0;
}