#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 10,maxk = 25;
int f[1 << maxk - 2], n, K, T;
char ch[maxn];
int a[maxn];
int cost[maxk][maxk];
int t[maxk], sta[maxk];
signed main(){
    scanf("%lld%lld%lld",&n,&K,&T);
    int all = 0;
    scanf("%s",ch + 1);for(int i = 1;i <= n;i++){a[i] = ch[i] - 'A';all |= (1 << a[i]);}
    for(int i = 1;i <= K;i++){scanf("%lld",&t[i]);f[1 << (i - 1)] += t[i];}
    for(int i = 1;i <= K;i++)
        for(int j = 1;j <= K;j++)
            scanf("%lld",&cost[i - 1][j - 1]);
    memset(sta,-1,sizeof(sta));
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < K;j++)
            if(sta[j] >= 0){
                if(!((sta[j] >> a[i]) & 1) && !((sta[j] >> j) & 1)){
                    f[sta[j]] += cost[j][a[i]];
                    f[sta[j] | (1 << j)] -= cost[j][a[i]];
                    f[sta[j] | (1 << a[i])] -= cost[j][a[i]];
                    f[sta[j] | (1 << j) | (1 << a[i])] += cost[j][a[i]];
                }
                sta[j] |= (1 << a[i]);
            }
        sta[a[i]] = 0;
    }
    int ans = 0;
    for(int i = 0;i < K;i++)
        for(int j = 0;j < 1 << K;j++)
            if((j >> i) & 1)f[j] += f[j ^ (1 << i)];
    for(int i = 0;i < 1 << K;i++)
        if(f[i] <= T && i != all && (i & all) == i){ans++;}
    printf("%lld\n",ans);
    return 0;
}