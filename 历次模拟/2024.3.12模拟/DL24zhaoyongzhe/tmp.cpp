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
const int maxn = 1e6 + 10, mod = 1e9 + 7;
int n, M;
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}

typedef pair<int,int> pii;

vector<pii> edg[maxn];
vector<pair<pii ,int> > e;
int pw[maxn];

pii operator + (pii a,pii b){
    return make_pair((a.first * pw[b.second] % mod + b.first) % mod,a.second + b.second);
}

bool book[maxn];

void main(){
    n = read(); M = read(); int u, v, tmp = n;
    pw[0] = 1;for(int i = 1;i <= n;i++){pw[i] = (pw[i - 1] * 10ll) % mod;fa[i] = i;}
    for(int i = 1;i <= M;i++){
        u = read(); v = read();
        if(getf(u) != getf(v)){
            int fu = getf(u), fv = getf(v);
            edg[u].push_back(make_pair(v, i));
            edg[v].push_back(make_pair(u, i));
            fa[fu] = fv;
        }
    }
    for(int s = 1;s <= n;s++){
        for(int i = 1;i <= n;i++)book[i] = 0;
        priority_queue<pii ,vector<pii >,greater<pii > > que;
        book[s] = 1;
        int cnt = n - 1, now = s;pii ans = make_pair(0,0);
        for(auto i : edg[s]){
            if(!book[i.first]){
                que.push(make_pair(i.second,i.first));
            }
        }
        while(cnt--){
            auto x = que.top();que.pop();
            if(book[x.second])continue;
            for(auto i : edg[x.second]){
                if(!book[i.first]){
                    que.push(make_pair(i.second,i.first));
                }
            }
            ans = ans + make_pair(x.first,1);
            book[x.second] = 1;
        }
        printf("%lld\n",ans.first);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("alphadog.in","r",stdin);
    freopen("alphadog.ans","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}