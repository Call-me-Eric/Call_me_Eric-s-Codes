#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
vector<pair<int,int> > edg[maxn];
double up[maxn], down[maxn];
namespace Subtask1{
    int son[maxn];
    void dfs1(int u,int f){
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(v != f){
                son[u]++;dfs1(v, u);
                down[u] += down[v] + w;
            }
        }
        if(son[u])down[u] /= son[u];
    }
    void dfs2(int u,int f){
        double tmp = up[u] + down[u] * (double)son[u];
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(v != f){
                if(u == 1){
                    if(son[u] == 1){up[v] = w;}
                    else up[v] = w + (tmp - down[v] - w) / (son[u] - 1);
                }
                else up[v] = w + (tmp - down[v] - w) / (son[u]);
                dfs2(v, u);
            }
        }
    }
    void main(){
        dfs1(1, 0);dfs2(1, 0);
        double ans = down[1];
        for(int i = 2;i <= n;i++)
            ans += (down[i] * son[i] + up[i]) / (son[i] + 1);
        ans /= n; printf("%.8lf\n",ans);
    }
};
namespace Subtask2{
    bool oncircle[maxn];
    int pre[maxn], son[maxn];
    int dfn[maxn], idx;
    void find(int u){
        dfn[u] = ++idx;
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(v != pre[u]){
                if(!dfn[v]){pre[v] = u;find(v);}
                else if(dfn[v] < dfn[u]){
                    for(int x = u;x != v;x = pre[x])oncircle[x] = 1;
                    oncircle[v] = 1;return;
                }
            }
        }
    }
    void getdown(int u,int f){
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(v != f && !oncircle[v]){
                ++son[u];getdown(v, u);
                down[u] += down[v] + w;
            }
        }
        if(son[u])down[u] /= son[u];
    }
    double getcirup(int u,int f,int st){
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(oncircle[v] && v != f){
                if(v == st){return down[u];}
                return (getcirup(v, u, st) + w + down[u] * son[u]) / (son[u] + 1);
            }
        }
        return 0;
    }
    void solve(int u){
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(oncircle[v]){up[u] += getcirup(v,u,u) + w;}
        }
        up[u] /= 2;
    }
    void getup(int u,int f){
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(v != f && !oncircle[v]){
                if(oncircle[u]) up[v] = w + (up[u] * 2 + down[u] * son[u] - down[v] - w) / (son[u] + 1);
                else up[v] = w + (up[u] + down[u] * son[u] - down[v] - w) / (son[u]);
                getup(v, u);
            }
        }
    }
    void main(){
        find(1);
        for(int i = 1;i <= n;i++)if(oncircle[i]){getdown(i,0);}
        for(int i = 1;i <= n;i++)if(oncircle[i]){solve(i);}
        for(int i = 1;i <= n;i++)if(oncircle[i]){getup(i, 0);}
        double ans = 0;
        for(int i = 1;i <= n;i++){
            if(oncircle[i]){ans += (down[i] * son[i] + up[i] * 2) / (son[i] + 2);}
            else {ans += (down[i] * son[i] + up[i]) / (son[i] + 1);}
        }
        ans /= n;printf("%.8lf\n",ans);
    }
};
signed main(){
    freopen("genshin.in","r",stdin);
    freopen("genshin.out","w",stdout);
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        int u = read(), v = read(), w = read();
        edg[u].push_back(make_pair(v,w));edg[v].push_back(make_pair(u,w));
    }
    if(n == m + 1){Subtask1::main();}
    else Subtask2::main();
    return 0;
}