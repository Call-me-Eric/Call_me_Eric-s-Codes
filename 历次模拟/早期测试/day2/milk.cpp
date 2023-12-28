#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
const int maxm = 5010;
long long n;
int m;
struct node{
    long long price,a;
}a[maxm];
struct cmp{
    bool operator ()(node x,node y){
        return x.price < y.price;
    }
};
int main(){
    scanf("%lld%d",&n,&m);
    for(int i = 1;i <= m;i++){
        scanf("%lld%lld",&a[i].price,&a[i].a);
    }
    sort(a + 1,a + 1 + m,cmp());
    long long ans = 0;
    for(int i = 1;i <= m;i++){
        if(n <= 0)break;
        if(n - a[i].a >= 0){
            n -= a[i].a;
            ans += a[i].price * a[i].a;
        }
        else{
            ans += a[i].price * n;
            n = 0;
        }
    }
    printf("%lld\n",ans);
    return 0;
}