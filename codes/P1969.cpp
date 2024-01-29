#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int now = 0,t = 0;
int n;
int ans = 0;
int main(){
    scanf("%d",&n);
    scanf("%d",&now);
    ans = now;
    for(int i = 2;i <= n;i++){
        scanf("%d",&t);
        if(t > now){
            ans += t - now;
        }
        now = t;
    }
    printf("%d",ans);
    return 0;
}