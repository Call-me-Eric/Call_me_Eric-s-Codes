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
const int maxn = 4e5 + 10, INF = 0x3f3f3f3f;
int n, V;
int x[maxn];
pair<int,int> seg[maxn];
int cntseg, dep;
int L[21][maxn], R[21][maxn];//在v = V>>i时，u能够到达的最左最右点是[L[i][u],R[i][u]]
int l[maxn * 5], r[maxn * 5];//在状态是sta时，从n出发能够跳到最左点l[sta],从1出发能够跳到最右点r[sta]
bool ans[maxn];
void main(){
    n = read(); V = read();x[0] = -INF;x[n + 1] = INF;
    for(int i = 1;i <= n;i++)x[i] = read();
    for(int v = V;v >= 0;v >>= 1,dep++){
        R[dep][n + 1] = n + 1;
        for(int i = 1;i <= n;i++)L[dep][i] = (x[i] - x[i - 1] <= v) ? L[dep][i - 1] : i;
        for(int i = n;i >= 1;i--)R[dep][i] = (x[i + 1] - x[i] <= v) ? R[dep][i + 1] : i;
        if(v == 0){dep++;break;}
    }
    for(int i = 1;i <= n;i++){seg[i] = make_pair(L[0][i],R[0][i]);}
    sort(seg + 1,seg + 1 + n);
    cntseg = unique(seg + 1,seg + 1 + n) - seg - 1;
    if(cntseg > dep){//保证最多只有log n条线段，再多就一定无法覆盖
        for(int i = 1;i <= n;i++)puts("Impossible");
        return;
    }
    for(int i = 0;i < (1 << dep);i++)l[i] = n + 1;
    for(int sta = 0;sta < (1 << dep);sta += 2){//sta += 2是因为不能用v=V
        for(int i = 0;i < dep;i++){
            if(sta & (1 << i)){
                l[sta] = min(l[sta],L[i][l[sta ^ (1 << i)] - 1]);
                r[sta] = max(r[sta],R[i][r[sta ^ (1 << i)] + 1]);
            }
        }
    }
    for(int i = 1;i <= cntseg;i++){
        // printf("[%d,%d]\n",seg[i].first,seg[i].second);
        for(int sta = 0;sta < (1 << dep);sta += 2){//仍然不让用v=V
            if(seg[i].first - 1 <= r[sta] && l[(1 << dep) - 1 - sta - 1] <= seg[i].second + 1){
                // printf("sta = %d,l[] = %d,r[] = %d\n",sta,l[(1 << dep) - 1 - sta - 1],r[sta]);
                for(int j = seg[i].first;j <= seg[i].second;j++){ans[j] = true;}
                break;
            }
        }
    }
    for(int i = 1;i <= n;i++)puts(ans[i] ? "Possible" : "Impossible");
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