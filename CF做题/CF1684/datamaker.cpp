#include<bits/stdc++.h>
#define int long long
using namespace std;
const int range = 1e9;
int T = 1, n = 1e5,k = 2e5;
int randint(int x = 1){x++;return (rand() * (rand() + x) % range + (rand() % x) / (range / x + 1) % range) % range;}
signed main(){
    srand(time(0));
    printf("%lld\n",T);
for(;T > 0;T--){
    k = randint(n + k) % n + 1;
    printf("%lld %lld\n",n,k);
    for(int i = 1;i <= n;i++){printf("%lld ",randint(randint(i) + randint(T)) % 10 + 1);}
    puts("");int u = randint(T), v = randint(randint(T) + rand());
    for(int i = 1;i <= k;i++){
        u = randint(u + rand()) % n + 1;v = randint(v + rand() + u) % n + 1;
        if(u > v)swap(u ,v);
        printf("%lld %lld\n",u, v);
    }
}
    return 0;
}