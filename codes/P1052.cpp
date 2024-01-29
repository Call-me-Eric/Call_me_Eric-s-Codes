#include<bits/stdc++.h>
using namespace std;
int m, s, t;
int L;
const int maxn = 300;
int stone[maxn];
int a[maxn * maxn];
bool book[maxn * maxn];
int dist;
int dp[maxn * maxn];
int main(){//TODO main()
    scanf("%d",&L);
    scanf("%d%d%d",&s,&t,&m);
    dist = s * t;
    for(int i = 1;i <= m;i++){
        scanf("%d",&stone[i]);
    }
    sort(stone + 1,stone + 1 + m);
    if(s == t){
        int ans;
        for(int i = 1;i <= m;i++){
            if(stone[i] % s == 0){
                ans ++;
            }
        }
        printf("%d\n",ans);
        return 0;
    }
    int d;
    for(int i = 1;i <= m;i++){
        d = stone[i] - stone[i - 1];
        if(d > dist)d = dist;
        a[i] = a[i - 1] + d;
        book[a[i]] = 1;
    }
    L = a[m] + dist;
    memset(dp,0x7f,sizeof(dp));
    dp[0] = 0;
    for(int i = 1;i <= L;i++){
        for(int j = s;j <= t;j++){
            if(i - j >= 0){
                if(book[i])dp[i] = min(dp[i],dp[i - j] + 1);
                else dp[i] = min(dp[i],dp[i - j]);
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = a[m];i <= L;i++){
        ans = min(ans, dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}