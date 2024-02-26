#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e4 + 10;
int n, k;
int w[maxn], f[maxn], ff[maxn];
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void add(int x,int add){for(;x <= n;x += lowbit(x))c[x] += add;}
    int qry(int x){int s = 0;for(;x;x -= lowbit(x))s += c[x];return s;}
}tr;
int l, r, ans;
inline void addl(int x){ans += tr.qry(w[x]);tr.add(w[x],1);}
inline void addr(int x){ans += r - l - tr.qry(w[x]);tr.add(w[x],1);}
inline void delr(int x){tr.add(w[x],-1);ans -= r - l + 1 - tr.qry(w[x]);}
inline void dell(int x){tr.add(w[x],-1);ans -= tr.qry(w[x]);}
void move(int nl,int nr){
    while(r < nr)addr(++r);
    while(nl < l)addl(--l);
    while(r > nr)delr(r--);
    while(l < nl)dell(l++);
}
void solve(int l,int r,int L,int R){
    if(r < l)return;
    int mid = l + r >> 1, p = mid;
    for(int i = min(mid - 1,R);i >= L;i--){
        move(i + 1,mid);
        if(ff[i] + ans <= f[mid]){f[mid] = ff[i] + ans;p = i;}
    }
    solve(l,mid - 1,L,p);solve(mid + 1,r,p,R);
}
void main(){
    n = read();k = read();
    for(int i = 1;i <= n;i++){w[i] = n - read() + 1;f[i] = ff[i] = 0x3f3f3f3f;}
    l = 1;r = 0;
    for(int j = 1;j <= k;j++){
        solve(1,n,0,n - 1);
        for(int i = 1;i <= n;i++)ff[i] = f[i];
    }
    printf("%d\n",f[n]);
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