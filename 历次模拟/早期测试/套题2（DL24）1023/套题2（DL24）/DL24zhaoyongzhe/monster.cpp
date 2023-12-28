#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, k;
const int maxn = 1e5 + 10, maxm = 1010;
int a[maxn], sum;
bool check(int maxx,int x){
    int cnt = 0, total = 0;
    for(int i = 1;i <= n;i++){
        if((a[i] + x) % m > maxx)return 0;
        if(total + ((a[i] + x) % m) > maxx){
            cnt++;
            total = (x + a[i]) % m;
            if(cnt == k)return 0;
        }
        else if(total + ((a[i] + x) % m) == maxx){
            cnt++;
            total = 0;
        }
        else total += ((x + a[i]) % m);
    }
    if(total == 0)return cnt <= k;
    else return cnt < k;
}
int work(int x){
    int l = 0, r = sum + x * n, mid = 0,ans;
    while(l < r){
        mid = (l + r) >> 1;
        if(check(mid,x))r = mid - 1,ans = mid;
        else l = mid + 1;
    }
    return ans;
}
signed main(){
    freopen("monster.in","r",stdin);
    freopen("monster.out","w",stdout);
    int ans = 0x3f3f3f3f;
    n = read(); m = read(); k = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();sum += a[i];
    }
    for(int x = 0;x < m;x++){
        ans = min(ans,work(x));
    }
    printf("%d\n",ans);
    return 0;
}