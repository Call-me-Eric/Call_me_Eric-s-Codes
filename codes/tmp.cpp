#include<bits/stdc++.h>
using namespace std;
signed main(){
    freopen("tmp.in","w",stdout);
    int T = 50000;printf("%d\n",T);srand(time(0));
    while(T--){
        int a = 1, b = 5e4, c = 1,d = 5e4;
        int k = rand() % d + 1;
        printf("%d %d %d %d %d\n",a,b,c,d,k);
    }
    return 0;
}