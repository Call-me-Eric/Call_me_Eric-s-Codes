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
int sum[maxn], pre[maxn], suf[maxn];
int tot;
struct BIT{
    int c[maxn],opt;//opt = 0 : min,opt = 1 : max;
    inline int cmp(int x,int y){if(x > y)swap(x,y);return opt ? y : x;}
    inline int lowbit(int x){return x & (-x);}
    int qry(int x){int s = opt ? 0 : n + 2;for(;x;x -= lowbit(x))s = cmp(s,c[x]);return s;}
    void upd(int x,int upd){for(;x <= tot + 10;x += lowbit(x))c[x] = cmp(c[x],upd);}
}tr;
int X[maxn];
int nxt[maxn], pr[maxn];
void main(){
    n = read();
    for(int i = 1;i <= n;i++)sum[i] = sum[i - 1] + (a[i] = read());
    for(int i = 1;i <= n + 1;i++)X[i] = b[i] = read();
// cerr << "11111111\n";
    sort(X + 1,X + 1 + n + 1);tot = unique(X + 1,X + 1 + n + 1) - X - 1;
// cerr << "tot = " << tot << "\n";
// for(int i = 1;i <= tot + 1;i++)cerr << X[i] << " ";cerr << "\n";
    tr.opt = 1;for(int i = 1;i <= tot + 10;i++)tr.c[i] = 0;
    for(int i = 1;i <= n + 1;i++){
        int x = lower_bound(X + 1,X + 1 + tot,b[i]) - X;
        // cerr << "b = " << b[i] << "x = " << x << " n - x + 1 = " << n - x + 1 << endl;
        pr[i] = tr.qry(tot - x);
        tr.upd(tot - x + 1,i);
    }
    tr.opt = 0;for(int i = 1;i <= tot + 10;i++)tr.c[i] = n + 2;
    for(int i = n + 1;i;i--){
        int x = lower_bound(X + 1,X + 1 + tot,b[i]) - X;
        nxt[i] = tr.qry(tot - x);
        tr.upd(tot - x + 1,i);
    }
// cerr << "2222222222\n";
    for(int i = 1;i <= n + 1;i++){pre[i] = max(pre[i - 1],b[i]);}
    for(int i = n + 1;i;i--)suf[i] = max(suf[i + 1],b[i]);
// for(int i = 1;i <= n + 1;i++)cerr << "i = " << i << " pre = " << pr[i] << " suf = " << nxt[i] << endl;
    auto check = [](int mid,int s){
        int l = s, r = s;
        while(1){
            while(l >= 1 && b[l] <= sum[r] - sum[l - 1] + mid){
                l = pr[l];if(sum[r] - sum[l - 1] + mid >= pre[l] || sum[r] - sum[l - 1] + mid >= suf[r])return true;
            }
            while(r < n + 1 && b[r + 1] <= sum[r] - sum[l - 1] + mid){
                r = nxt[r + 1] - 1;if(sum[r] - sum[l - 1] + mid >= pre[l] || sum[r] - sum[l - 1] + mid >= suf[r])return true;
            }
            // printf("l = %lld, r = %lld\n",l,r);
            if(l <= 0 || r >= n + 1)return true;
            if(b[l] > sum[r] - sum[l - 1] + mid && b[r + 1] > sum[r] - sum[l - 1] + mid)return false;
        }
        return true;
    };
    for(int s = 1;s <= n;s++){
        int l = 0, r = max(0ll,suf[1] - a[s] + 10), ans = -1;
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
    freopen("room.out","w",stdout);
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