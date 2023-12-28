#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n,ans, all;
int s[20];
int prime[11] = {0,2,3,5,7,11,13,17,19,23,27};
void dfs(int step,int sum,int mul){
    if(step > 10)return;
    if(sum > ans || sum == ans && mul < all){
        ans = sum;
        all = mul;
    }
    s[step] = 0;
    while(mul * prime[step] <= n && s[step] <= s[step - 1]){
        s[step]++;
        mul *= prime[step];
        dfs(step + 1,sum * (s[step] + 1),mul);
    }
}
signed main(){
    n = read();
    s[0] = 1000000;
    dfs(1,1,1);
    printf("%d\n",all);
    return 0;
}
