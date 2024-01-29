#include<bits/stdc++.h>
using namespace std;
int m, a[1000],t[1000];
int dp[200][1000];
void init(int x){
    scanf("%d%d",&a[x],&t[x]);
    a[x] *= 2;//he had to cross for twice
    if(t[x] == 0){
        init(x << 1);//=x * 2
        init(x << 1 | 1);//=x*2+1
    }
    return;
}
int dfs(int x,int tot){
    if(dp[x][tot] > 0 || tot == 0)return dp[x][tot];
    if(t[x])return dp[x][tot] = min(t[x],(tot - a[x]) / 5);
    for(int i = 0;i < tot - a[x];i++){
        dp[x][tot] = max(dp[x][tot],dfs(x << 1,i)+dfs(x << 1 | 1,tot - a[x] - i));
    }
    return dp[x][tot];
}
int main(){
    scanf("%d",&m);
    m--;//because the thief had to escape just before the police came
    init(1);
    printf("%d\n",dfs(1,m));
    return 0;
}