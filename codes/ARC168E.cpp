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
const int maxn = 3e5 + 10;
int n, k, s;
int sum[maxn], pre[maxn];
pair<int,int> f[maxn];
bool check(int lim){
    int l = 1,r = n, mid = 0, res = 0;
    auto work = [](int x){
        for(int i = 1;i <= n;i++){
            f[i] = f[i - 1];if(pre[i]){f[i] = min(f[i],make_pair(f[pre[i] - 1].first + (i - pre[i]) - x,f[pre[i] - 1].second + 1));}
        }
    };
    while(l <= r){
        mid = l + r >> 1; work(mid);
        if(f[n].second <= lim){l = mid + 1;res = mid;}
        else r = mid - 1;
    }
    work(res);
    return f[n].first + res * lim <= n - k;
}
void main(){
    n = read(); k = read(); s = read();
    for(int i = 1,l = 0;i <= n;i++){
        sum[i] = read() + sum[i - 1];
        while(sum[i] - sum[l] >= s)l++;
        pre[i] = l;
    }
    int l = 1, r = k, ans = 0;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid)){l = mid + 1,ans = mid;}
        else r = mid - 1;
    }
    printf("%lld\n",ans);
    return;
}
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