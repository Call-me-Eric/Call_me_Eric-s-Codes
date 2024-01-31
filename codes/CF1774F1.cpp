#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 8e5 + 10, mod = 998244353,maxx = 1e9;
int n;
int a[maxn], b[maxn];

vector<int> vec;
int pw[maxn];

signed main(){
    n = read();int sum = 0;pw[0] = 1;
    for(int i = 1;i <= n;i++){
        pw[i] = pw[i - 1] << 1;pw[i] %= mod;
        a[i] = read();if(a[i] != 3)b[i] = read();
        if(a[i] == 2){sum += b[i];}sum = min(sum,maxx);
        if(a[i] == 3){b[i] = sum;sum <<= 1;}sum = min(sum,maxx);
    }
    int ans = 0, times = 1;sum = 0;
    for(int i = n;i;i--){
        switch(a[i]){
            case 1:{
                int x = b[i] - sum, res = 1;if(x <= 0)break;
                for(int i = 0;i < vec.size();i++){
                    if(vec[i] < x){
                        res = (res + pw[vec.size() - i - 1]) % mod;
                        x -= vec[i];
                    }
                }
                ans = (ans + res * times) % mod;
                break;
            }
            case 2:{sum += b[i];break;}
            case 3:{
                if(b[i] >= maxx)break;
                if(b[i] == 0){times <<= 1;times %= mod;break;}
                vec.push_back(b[i]);
                break;
            }
            default: break;
        }
    }
    printf("%lld\n",ans);
    return 0;
}