#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, m, s, t;
map<int,int> mp;
signed main(){
    n = read(); m = read(); s = read(); t = read();s--;//方便mod移位
    for(int i = t;i;i--){
        if(i % n == t % n){
            if(mp[s]){
                t = i % (mp[s] - i);
                break;
            }
            else mp[s] = i;
        }
        if(s < m)s = (s + i) % n;
        else s = ((s - i) % n + n) % n;
        if(i == 1){printf("%lld\n",s + 1);return 0;}
    }
    for(int i = t;i;i--){
        if(s < m){s = (s + i) % n;}
        else s = ((s - i) % n + n) % n;
    }
    printf("%lld\n",s + 1);
    return 0;
}