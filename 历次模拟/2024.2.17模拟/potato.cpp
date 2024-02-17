#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
#define ll long long
inline ll read(){
    ll x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10;
int T, n, m, t; ll seed;
int a[maxn][maxn];
vector<int> upd[maxn], add[maxn];
bool Rand(ll &x){x ^= x << 16; x ^= x >> 5; x ^= x << 1;return (x & 65535) < t;}
void getdata(){for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)a[i][j] = Rand(seed);}
int down[maxn][maxn];
int fa[maxn], siz[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
int calc1(int x){return siz[x] * (siz[x] - 1) / 2 + siz[x];}
void main(){
    n = read(); m = read(); t = read(); seed = read();getdata();
    for(int i = m;i;i--){down[n][i] = down[n + 1][i] = n + 1;}
    for(int i = n;i;i--)for(int j = 1;j <= m;j++)
        down[i][j] = a[i][j] ? i : down[i + 1][j];
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            printf("%d",a[i][j]);
        }
        puts("");
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            printf("%d ",down[i][j]);
        }
        puts("");
    }
    ll ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n + 1;j++){upd[j].clear();add[j].clear();}
        for(int j = 1;j <= m;j++){
            int x = down[i][j], y = down[x + 1][j];//[i,x-1] : 0,[x,y-1] : 1
            if(x == n + 1)x++;
            upd[y - 1].push_back(j); add[x - 1].push_back(j);
            fa[j] = j;siz[j] = 0;
        }
        int sum = 0;
        for(int j = n + 1;j >= i;j--){
            for(int k : add[j]){
                printf("k = %d,add\n",k);
                int fl = getf(k - 1), fr = getf(k + 1), fk = getf(k);
                sum -= (siz[fl] + 1) * (siz[fr] + 1);
                siz[fk] = 1;
                if(siz[fl]){sum -= calc1(fl);fa[fl] = fk;siz[fk] += siz[fl];}
                if(siz[fr]){sum -= calc1(fr);fa[fr] = fk;siz[fk] += siz[fr];}
                sum += calc1(fk);
            }
            printf("sum = %d\n",sum);
            for(int k : upd[j]){
                printf("k = %d,upd\n",k);
                int fl = getf(k - 1), fr = getf(k + 1);
                sum += (siz[fl] + 1) * (siz[fr] + 1);
            }
            printf("i = %d, j = %d, sum = %d\n",i,j,sum);
            ans += sum;
        }
    }
    printf("%lld\n",1ll * (n * m - 1) * (n * m) / 2 - ans);
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