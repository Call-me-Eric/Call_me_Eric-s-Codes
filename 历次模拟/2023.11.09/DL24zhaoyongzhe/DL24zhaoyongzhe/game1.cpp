#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, a[maxn];
bool check(int l,int r){
    if(l > r)return true;
    int cnt = 0;
    for(int i = l;i <= r;i++)cnt += a[i];
    if((cnt >> 1) & 1)return false;
    while(a[l] == a[r] && l < r){l++;r--;}
    for(int i = l;i <= r;i += 2)
        if(a[i] ^ a[i + 1])return false;
    return true;
}
int solve(){
    int sum = 0;
    n = read(); for(int i = 1;i <= n;i++)sum ^= (a[i] = read());
    if(!sum)return 0; if((n & 1) == 0 || n == 1)return 1;
    for(int i = 30;i + 1;i--)
        if(sum & (1 << i)){
            for(int j = 1;j <= n;j++)a[j] = !!((a[j] >> i) & 1);
            break;
        }
    if(a[1] && check(2,n))return 1;
    if(a[n] && check(1,n - 1))return 1;
    return -1;
}
signed main(){
int T = read();
while(T--){
    int res = solve();
    puts(res == 1 ? "First" : (res == 0 ? "Draw" : "Second"));
}
    return 0;
}