#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = (1 << 18) + 10;
int T;
int n, k, a[maxn];
int buc[maxn];
pair<int,int> buc1[maxn];
pair<int,int> ins(int x,int y){
    int s = (a[y] ^ a[x - 1]);
    if(buc1[s].first == -1){buc1[s] = make_pair(x, y);return make_pair(-1,-1);}
    return buc1[s];
}
void solve(){
    k = read();n = 1 << (k + 1);for(int i = 1;i <= n;i++)a[i] = a[i - 1] ^ read();
    for(int i = 0;i <= (1 << k);i++)buc[i] = -1,buc1[i] = make_pair(-1,-1);
    buc[0] = 0;
    for(int i = 1;i <= n;i++){
        if(buc[a[i] >> k] != -1){
            auto tmp = ins(buc[a[i] >> k] + 1,i);
            if(tmp.first != -1){
                int u = tmp.first, v = tmp.second;
                int l = buc[a[i] >> k] + 1, r = i;
                if(v < l){printf("%lld %lld %lld %lld\n",u,v,l,r);return;}
                if(u < l && v >= l){printf("%lld %lld %lld %lld\n",u,l - 1,v + 1,r);return;}
                if(u > l){printf("%lld %lld %lld %lld\n",l,u - 1,v + 1,r);return;}
            }
        }
        buc[a[i] >> k] = i;
    }
    puts("-1");
}
void main(){T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}