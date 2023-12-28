#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
    ll x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int m, mod;
int s[maxn], atk[maxn];
signed main(){
    freopen("dark.in","r",stdin);
    freopen("dark.out","w",stdout);
    mod = read(); m = read();
    s[1] = 134775813 % mod;int pos = 1, l, r;
    for(int test = 1;test <= m;test++){
        l = read();r = read();
        while(pos <= r){
            pos++;
            s[pos] = ((ll)1103515245 % mod * s[pos - 1] % mod + 1013904223 % mod) % mod;
            atk[pos] = (s[pos] & 1) ? 4 : ((s[pos] % 4 == 0) ? 1 : 3);
        }
        unsigned int cnt = 0;int lst = 0;
        vector<int> vec;vec.clear();vec.push_back(0);
        for(int i = l;i <= r;i++){vec.push_back(vec.back() + atk[i]);}
        for(int i = 1;i <= r - l + 1;i++)
            for(int j = i;j <= r - l + 1;j++)
                if(vec[j] - vec[i - 1] > 3 * (j - i + 1))cnt++;
        printf("%u\n",cnt);
    }
    return 0;
}