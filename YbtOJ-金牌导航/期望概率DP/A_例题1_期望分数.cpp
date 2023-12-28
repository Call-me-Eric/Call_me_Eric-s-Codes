#include<bits/stdc++.h>
using namespace std;
int n;double p, pow3, pow1, pow2;
signed main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%lf",&p);
        pow3 += (3.0 * pow2 + 3.0 * pow1 + 1.0) * p;
        pow2 = (pow2 + 2.0 * pow1 + 1.0) * p;
        pow1 = (pow1 + 1.0) * p;
    }
    printf("%.1lf\n",pow3);
    return 0;
}