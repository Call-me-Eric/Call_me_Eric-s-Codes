#include<bits/stdc++.h>
using namespace std;
bool stmemory;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
namespace Call_me_Eric{
const int maxn = 3e3 + 10;
vector<int> edg[maxn];
int n;
bool vis[maxn], in[maxn];
stack<int> stk;
vector<int> ring;bool flag = false;
int col[maxn][maxn];
void dfs(int u,int f){
    if(flag)return;
    vis[u] = in[u] = 1;stk.push(u);
    for(auto v : edg[u]){
        if(flag)return;
        if(v != f){
            if(in[v]){
                ring.clear();flag = true;
                while(stk.top() != v){ring.push_back(stk.top());stk.pop();}
                ring.push_back(v);stk.pop();return;
            }
            dfs(v,u);
        }
    }
    if(flag)return;
    in[u] = 0;stk.pop();
}
void main(){
    n = read();
    ring.clear();flag = false;
    memset(col,0,sizeof(col));memset(in,0,sizeof(in));
    memset(vis,0,sizeof(vis));
    while(!stk.empty())stk.pop();
    for(int i = 1;i <= n * 2;i++)edg[i].clear();
    for(int i = 1;i <= n * 2;i++){
        int u = read(), v = read() + n;col[u][v] = col[v][u] = i;
        edg[u].push_back(v); edg[v].push_back(u);
    }
    for(int i = 1;i <= n && !flag;i++)if(!vis[i])dfs(i,0);
    auto query = [](int x,int y)->int{if(x > y)swap(x, y); printf("? %d %d\n",x,y - n);fflush(stdout);return read();};
    while(ring.size() > 4){
        int mid = (ring.size() - 1) / 4,siz = ring.size() - 1;
        int u = ring[mid], v = ring[siz - mid], color = query(u, v);
        col[u][v] = col[v][u] = color;bool book = true;
        for(int i = mid;i < siz - mid;i++){if(col[ring[i]][ring[i + 1]] == color){book = false;break;}}
        vector<int> tmp;tmp.clear();
        if(book){for(int i = mid;i <= siz - mid;i++)tmp.push_back(ring[i]);}
        else {for(int i = 0;i <= mid;i++)tmp.push_back(ring[i]);for(int i = siz - mid;i <= siz;i++)tmp.push_back(ring[i]);}
        ring = tmp;
    }
    sort(ring.begin(),ring.end());
    printf("! %d %d %d %d\n",ring[0],ring[1],ring[2] - n,ring[3] - n);fflush(stdout);
    char ch[100];scanf("%s",ch + 1);
    if(ch[1] == 'E'){exit(0);}
    return;
}
void solve(){int T = read();while(T--)main();}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::solve();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}