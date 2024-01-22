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
const int maxn = 3e5 + 10;

struct DSU{
    int fa[maxn];
    void init(int n){for(int i = 1;i <= n;i++)fa[i] = i;}
    int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
    bool merge(int x,int y){
        int fu = getf(x), fv = getf(y);
        if(fu == fv)return false;
        fa[fu] = fv;return true;
    }
}dsu;

int n;
int a[maxn], b[maxn];
int tmp1[maxn], tmp2[maxn];
vector<int> vec;

void main(){
    n = read();int suma = 0, sumb = 0;
    for(int i = 1;i <= n;i++)suma ^= (a[i] = read());a[n + 1] = suma;
    for(int i = 1;i <= n;i++)sumb ^= (b[i] = read());b[n + 1] = sumb;
    n++;for(int i = 1;i <= n;i++){tmp1[i] = a[i];tmp2[i] = b[i];}
    sort(tmp1 + 1,tmp1 + 1 + n);sort(tmp2 + 1,tmp2 + 1 + n);
    for(int i = 1;i <= n;i++){if(tmp1[i] != tmp2[i]){puts("-1");return;}}
    int ans = 0;
    for(int i = 1;i <= n;i++){
        if(a[i] != b[i] || i == n){
            vec.push_back(a[i]);vec.push_back(b[i]);
            if(i != n)ans++;
        }
    }
    if(ans == 0){puts("0");return;}
    sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
    dsu.init(vec.size());
    for(int i = 1;i <= n;i++){
        if(a[i] != b[i]){
            a[i] = lower_bound(vec.begin(),vec.end(),a[i]) - vec.begin() + 1;
            b[i] = lower_bound(vec.begin(),vec.end(),b[i]) - vec.begin() + 1;
            dsu.merge(a[i],b[i]);
        }
    }
    for(int i = 1;i <= vec.size();i++)ans += (dsu.getf(i) == i);
    printf("%d\n",ans - 1);
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