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
const int maxn = 1e6 + 10;
int n;
int a[maxn], b[maxn];
int sum[maxn], pre[maxn], nxt[maxn];
void main(){
    n = read();
    for(int i = 1;i <= n;i++)sum[i] = sum[i - 1] + (a[i] = read());
    for(int i = 1;i <= n + 1;i++)b[i] = read();
    
    auto check = [](int mid,int s){
        int l = s, r = s, sum = mid + a[s];
        while(1){
            while(l >= 1 && b[l] <= sum){l--;sum += a[l];}
            while(r < n + 1 && b[r + 1] <= sum){r++;sum += a[r];}
            if(l == 0 || r == n + 1)return true;
            if(b[l] > sum)return false;
        }
        return true;
    };
    for(int s = 1;s <= n;s++){
        int l = 0, r = 1e9, ans = -1;
        while(l <= r){
            int mid = l + r >> 1;
            if(check(mid,s)){r = mid - 1;ans = mid;}
            else l = mid + 1;
        }
        printf("%lld ",ans);
    }
    puts("");
    return;
}
};
bool edmemory;
signed main(){
    freopen("room.in","r",stdin);
    freopen("tmp.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
3
1 2 3
4 5 6 7
*/