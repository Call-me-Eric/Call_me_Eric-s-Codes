#include<bits/stdc++.h>
using namespace std;
signed main(){
    srand(time(0));
    printf("10\n");
for(int t = 1;t <= 10;t++){
    int n = (n - rand() + (int)1e5) % (int(1e5));if(n / 1000)n /= 100;
    int m = 1e5 / n;
    printf("%d %d\n",n, m);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++)
            printf("%d ",j);
        puts("");
    }
}
    return 0;
}