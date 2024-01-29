#include<bits/stdc++.h>
using namespace std;
const int maxn = 50050;
int n;
long long a[maxn];
struct node{
    int i;
    long long sum;
}sum[maxn];
bool operator < (node x,node y){return x.sum < y.sum;}
int main(){
    sum[0].i = 0;
    sum[0].sum = 0;
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%lld",&a[i]);
        sum[i].i = i;
        sum[i].sum = sum[i - 1].sum + a[i];
    }
    sort(sum,sum + 1 + n);
    long long ans = 0x7f7f7f7f;
    for(int i = 0;i <= n;i++){
        if(sum[i].i < sum[i + 1].i && sum[i + 1].sum - sum[i].sum > 0){
            ans = min(ans,sum[i + 1].sum - sum[i].sum);
        }
    }
    printf("%lld\n",ans);
    return 0;
}