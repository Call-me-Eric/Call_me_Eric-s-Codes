#include<bits/stdc++.h>
#define LL long long
using namespace std;
int k, n;
const LL mod = 1e9 + 7;
const int maxn = 5e5 + 100;
LL c[maxn],d[maxn],e[maxn];//e[i]为当前的偏移量
LL l[20], r[20];//l,r是这一轮第i维的最左端不符合(负数)的和最右端不符合的点(正数)
LL w[20];
LL ans = 1;
int main(){
    scanf("%d%d",&n,&k);
    for(int i = 1;i <= k;i++){
        scanf("%lld",&w[i]);
        ans = ans * w[i] % mod;
    }
    //此时ans = 所有点(每一个点在走出界时也算一步)
    for(int i = 1;i <= n;i++){
        scanf("%lld%lld",&c[i],&d[i]);
    }
    while(1){//枚举每一轮
        for(int i = 1;i <= n;i++){
            //记录偏移量
            e[c[i]] += d[i];
            //更新边界
            l[c[i]] = min(l[c[i]],e[c[i]]);
            r[c[i]] = max(r[c[i]],e[c[i]]);
            LL s = 1;
            for(int j = 1;j <= k;j++){
                if(r[j] - l[j] >= w[j]){
                    printf("%lld",ans);
                    return 0;//所有点已经全部出界
                }
                s = s * (w[j] - r[j] + l[j]) % mod;//加上合格的点
            }
            ans = (ans + s) % mod;
            //更新答案
        }
        bool book = 1;
        for(int i = 1;i <= k;i++){
            if(e[i] != 0){//如果走不出去
                book = 0;
                break;
            }
        }
        if(book){
            puts("-1");
            return 0;
        }
    }
    return 0;
}