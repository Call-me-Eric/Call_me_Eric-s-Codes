#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10, mod = 1000003;
int a[maxn],n, k, ans, x[maxn];
void dfs(int u,int cnt){
    if(u < k){
        // if(u >= 43000){printf("cnt=%lld ; x = %lld\n",cnt,u);getchar();}

        if(cnt + k - u >= a[1]){x[u] = 0;dfs(u + 1,cnt);}
        if(cnt + 1 <= a[1]){x[u] = 1;dfs(u + 1,cnt + 1);}
    }
    else{
        int flag = 1;
        for(int i = u;i <= n;i++){
            if(cnt - x[i - k] == a[i - k + 1]){
                x[i] = 0;cnt -= x[i - k];
            }
            else if(cnt - x[i - k] + 1 == a[i - k + 1]){
                x[i] = 1;cnt = 1 - x[i - k] + cnt;
            }
            else {flag = 0;break;}
        }
        ans += flag;
        return;
    }
}
signed main(){
    freopen("bit.in","r",stdin);
    freopen("bit.out","w",stdout);
    n = read(); k = read();
    for(int i = 1;i <= n - k + 1;i++)a[i] = read();
    for(int i = 1;i <= n - k + 1;i++){
        if(a[i] > k || (i != 1 && abs(a[i] - a[i - 1]) > 1)){
            puts("0");return 0;
        }
    }
    // puts("111111");
    dfs(1,0);
    printf("%lld\n",ans);
    return 0;
}