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
int c[maxn], sa[maxn], sb[maxn], n;
int pos[maxn];
void main(){
    n = read();
    for(int i = 1;i <= n;i++)sa[i] = sa[i - 1] + read();
    for(int i = 1;i <= n;i++)sb[i] = sb[i - 1] + read();
    int la = 0, ra = 0, lb = 0, rb = 0;pos[0] = -1;
    for(int i = 1;i <= n;i++){
        c[i] = c[i - 1];
        while(sb[c[i] + 1] <= sa[i] && c[i] < n)c[i]++;
        if(pos[sa[i] - sb[c[i]]]){
            int x = pos[sa[i] - sb[c[i]]];
            if(x == -1){la = lb = 0;ra = i;rb = c[i];break;}
            la = x;lb = c[x];ra = i;rb = c[i];
            break;
        }
        pos[sa[i] - sb[c[i]]] = i;
    }
    printf("%lld\n",ra - la); for(int i = la + 1;i <= ra;i++)printf("%lld ",i);puts("");
    printf("%lld\n",rb - lb); for(int i = lb + 1;i <= rb;i++)printf("%lld ",i);puts("");
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