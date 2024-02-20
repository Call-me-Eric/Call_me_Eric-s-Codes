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
    auto stclock = clock();
    n = read();
    for(int i = 1;i <= n;i++)sum[i] = sum[i - 1] + (a[i] = read());
    for(int i = 1;i <= n + 1;i++)b[i] = read();
    stack<int> stk;
    for(int i = 1;i <= n + 1;i++){
        while(!stk.empty() && b[stk.top()] < b[i]){stk.pop();}
        if(stk.empty())pr[i] = 0;
        else pr[i] = stk.top();
        stk.push(i);
    }
    while(!stk.empty())stk.pop();
    for(int i = n + 1;i;i--){
        while(!stk.empty() && b[stk.top()] < b[i]){stk.pop();}
        if(stk.empty())nxt[i] = n + 2;
        else nxt[i] = stk.top();
        stk.push(i);
    }
    // cerr << (clock() - stclock)* 1.0 / CLOCKS_PER_SEC << " SEC COST.\n";
// cerr << "2222222222\n";
    for(int i = 1;i <= n + 1;i++){pre[i] = max(pre[i - 1],b[i]);}
    for(int i = n + 1;i;i--)suf[i] = max(suf[i + 1],b[i]);
// for(int i = 1;i <= n + 1;i++)cerr << "i = " << i << " pre = " << pr[i] << " suf = " << nxt[i] << endl;
    auto check = [](int s){
        int l = s, r = s, mid = 0;
        while(1){
            while(l >= 1 && b[l] <= sum[r] - sum[l - 1] + mid){
                l = pr[l];if(sum[r] - sum[l - 1] + mid >= pre[l] || sum[r] - sum[l - 1] + mid >= suf[r])return mid;
            }
            while(r < n + 1 && b[r + 1] <= sum[r] - sum[l - 1] + mid){
                r = nxt[r + 1] - 1;if(sum[r] - sum[l - 1] + mid >= pre[l] || sum[r] - sum[l - 1] + mid >= suf[r])return mid;
            }
            // printf("l = %lld, r = %lld, mid = %lld, s = %lld\n",l,r,mid,s);
            if(l <= 0 || r >= n + 1)return mid;
            int su = sum[r] - sum[l - 1] + mid;
            if(b[l] <= su)continue;
            int x = b[l] - su, y = b[r + 1] - su;
            if(x < y){mid += x;l = pr[l];}
            else{mid += y;r = nxt[r + 1] - 1;}
        }
        return mid;
    };
    for(int s = 1;s <= n;s++){
        printf("%lld ",check(s));
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

10
10 1 3 9 2 10 9 5 10 1
13 13 4 4 7 7 3 7 13 6 13

3 3 1 0 5 0 0 2 2 5
*/