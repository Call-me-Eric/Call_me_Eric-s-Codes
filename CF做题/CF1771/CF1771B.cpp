#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
vector<int> vec[maxn];
signed main(){
int T = read();
while(T--){
    n = read();m = read();int u, v;
    for(int i = 1;i <= n;i++)vec[i].clear();
    for(int i = 1;i <= m;i++){u = read(); v = read();vec[min(u,v)].push_back(max(u,v));}
    int lst = n + 1,ans = 0;
    for(int i = n;i;i--){
        if(!vec[i].empty()){for(int j : vec[i])lst = min(lst,j);}
        ans += lst - i;
    }
    printf("%lld\n",ans);
}
    return 0;
}