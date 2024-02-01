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
const int maxn = 1e3 + 10, maxm = maxn * maxn;
struct mystk{
    struct node{
        int x, y, dep;
        node(int x = 0,int y = 0,int dep = 0):x(x),y(y),dep(dep){}
    }st[maxm];
    int op;
    void init(){op = 0;}
    void pop(){op--;}
    node top(){return st[op];}
    void push(node x){st[++op] = x;}
    bool empty(){return op == 0;}
};
typedef long long ll;set<ll> p,s;
struct DSU{
    mystk stk;
    int fa[maxm], dep[maxm];
    void init(int x = 0){for(int i = 1;i <= x;i++){fa[i] = i;dep[i] = 1;}stk.init();}
    int getf(int x){return fa[x] == x ? x : getf(fa[x]);}
    int getfa(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
    void merge(int x,int y){
        int fx = getf(x), fy = getf(y);
        s.insert(fx);
        if(fx == fy)return;
        s.insert(fy);
        if(dep[fx] > dep[fy])swap(fx,fy);
        stk.push(mystk::node(fx,fy,dep[fx] == dep[fy]));
        fa[fx] = fy;dep[fy] += (dep[fx] == dep[fy]);
    }
    void trace(int rev = -1){
        while(rev < stk.op){
            int x = stk.top().x, y = stk.top().y, dept = stk.top().dep;
            fa[x] = x;dep[y] -= dept; stk.pop();
        }
    }
}dsu;
int n, m, q;
int a[maxn][maxn];
char ch[maxn];
int id[maxn][maxn], cntnode;
const int dx[8] = {-1,-1,-1, 0, 1, 1, 1, 0};
const int dy[8] = {-1, 0, 1, 1, 1, 0,-1,-1};
inline bool check(int x,int y){return x > -1 && y > -1 && x <= n && y <= m;}

vector<pair<int,int> > vec;int l;
void main(){
    n = read(); m = read(); q = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1); for(int j = 1;j <= m;j++) a[i][j] = ch[j] == '#';
    }
    n++;m++;
    for(int i = 3;i <= n;i++)a[i][0] = 1;
    for(int j = 3;j <= m;j++)a[0][j] = 1;
    for(int i = 0;i + 2 < n;i++)a[i][m] = 1;
    for(int j = 0;j + 2 < m;j++)a[n][j] = 1;
    for(int i = 0;i <= n;i++)for(int j = 0;j <= m;j++)id[i][j] = ++cntnode;
    dsu.init(cntnode);
    for(int i = 0;i <= n;i++){
        for(int j = 0;j <= m;j++){
            if(a[i][j])
            for(int k = 0;k < 8;k++){
                int nx = i + dx[k], ny = j + dy[k]; 
                if(check(nx,ny) && a[nx][ny])dsu.fa[dsu.getfa(id[i][j])] = dsu.getfa(id[nx][ny]);
            }
        }
    }
    for(int i = 1;i <= cntnode;i++){if(i == dsu.getfa(i))dsu.dep[i] = 2;else dsu.dep[i] = 1;}
    for(int i = 0;i <= n;i++){
    for(int j = 0;j <= m;j++){
        if(a[i][j]){
            for(int u = -2;u <= 2;u++){
            for(int v = -2;v <= 2;v++){
                int x = u + i, y = v + j;
                if(!check(x,y) || !a[x][y])continue;
                int fu = dsu.getfa(id[i][j]), fv = dsu.getfa(id[x][y]);
                if(fu == fv)continue;p.insert(1ll * fu * cntnode + fv);
            }
            }
        }
    }
    }
    int top = dsu.stk.op;
    auto solve = [](){
        // if(dsu.getf(id[n][0]) == dsu.getf(id[0][m]))return false;
        s.erase(s.begin(),s.end());s.insert(dsu.getf(id[n][0]));s.insert(dsu.getf(id[0][m]));
        if(a[1][1] || a[n - 1][m - 1])return false;
        for(int i = 1;i <= l;i++){
            int u = vec[i].first, v = vec[i].second;
            for(int k = 0;k < 8;k++){
                int nx = u + dx[k],ny = v + dy[k];
                if(check(nx,ny) && a[nx][ny])dsu.merge(id[nx][ny],id[u][v]);
            }
        }
        if(dsu.getf(id[n][0]) == dsu.getf(id[0][m]))return false;
        for(ll i : s)if(dsu.getf(i) == dsu.getf(id[n][0]))
            for(ll j : s)if(dsu.getf(j) == dsu.getf(id[0][m]) && p.find(1ll * i * cntnode + j) != p.end())
                return false;
        for(int i = 1;i <= l;i++){
            int x = vec[i].first, y = vec[i].second;
            if(dsu.getf(id[x][y]) == dsu.getf(id[n][0])){
                for(int u = -2;u <= 2;u++)
                    for(int v = -2;v <= 2;v++){
                        int nx = u + x, ny = v + y;
                        if(check(nx,ny) && a[nx][ny] && dsu.getf(id[nx][ny]) == dsu.getf(id[0][m]))
                            return false;
                    }
            }
            if(dsu.getf(id[x][y]) == dsu.getf(id[0][m])){
                for(int u = -2;u <= 2;u++)
                    for(int v = -2;v <= 2;v++){
                        int nx = u + x, ny = v + y;
                        if(check(nx,ny) && a[nx][ny] && dsu.getf(id[nx][ny]) == dsu.getf(id[n][0]))
                            return false;
                    }
            }
        }
        return true;
    };
    while(q--){
        l = read();vec.clear();vec.push_back(make_pair(0,0));
        for(int i = 1;i <= l;i++){
            int u = read(), v = read(); vec.push_back(make_pair(u, v)); a[u][v] = 1;
        }
        puts(solve() ? "YES" : "NO");
        for(int i = 1;i <= l;i++){int u = vec[i].first, v = vec[i].second; a[u][v] = 0;}
        dsu.trace(top);fflush(stdout);
    }
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