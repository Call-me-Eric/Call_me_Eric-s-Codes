#include<bits/stdc++.h>

using i64 = int64_t;

namespace shaber{
    constexpr int maxn = 2e5 + 5;
    int deg[maxn];
    struct Edge{
        int nxt, to;
    }G[maxn << 1];
    int h[maxn], tot;
    void adde(int u, int v){
        ++deg[u], ++deg[v];
        G[++tot] = {h[u], v};
        h[u] = tot;
        G[++tot] = {h[v], u};
        h[v] = tot;
    }
    int vis[maxn];
    void fraud(){
        std::ifstream fin("li.in");
        std::ofstream fout("li.out");
        int n, m;
        fin >> n >> m;
        for(int i = 0, u, v; i < m; ++i){
            fin >> u >> v, adde(u, v);
        }
        int s = 0, cirlen = 0, lkl = 0;
        for(int i = 1; i <= n; ++i){
            if(deg[i] >= 3){
                if(deg[i] == 3){
                    vis[i] = 1, cirlen += 3;
                    for(int j = h[i]; j; j = G[j].nxt){
                        int to = G[j].to;
                        vis[to] = 1;
                        if(deg[to] != 1){
                            s = -1;
                        }
                    }
                }
                else{
                    s = -1;
                }
            }
            if(s == -1){
                fout << "-1\n";
                return ;
            }
        }
        i64 lim = 0;
        bool iscir = false;
        i64 Len = 0;
        auto dfs = [&](auto self, int u, int fa, int dep) -> void{
            //std::cout << u << ' ' << fa << ' ' << dep << '\n';
            if(vis[u]){
                iscir = true;
                return ;
            }
            vis[u] = 1;
            ++Len;
            for(int i = h[u]; i; i = G[i].nxt){
                int to = G[i].to;
                if(to == fa){
                    continue;
                }
                self(self, to, u, dep + 1);
            }
        };
        for(int i = 1; i <= n; ++i){
            if(vis[i] == 0){
                iscir = false;
                Len = 0;
                dfs(dfs, i, i, 0);
                if(iscir){
                    cirlen += Len;
                }
                else{
                    lim += (Len * (Len + 1)) / 2;
                }
            }
        }
        if(cirlen){
            fout << "1 " << cirlen << '\n';
        }
        else{
            fout << "0 " << lim << '\n';
        }
    }
}

int main(){
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    shaber::fraud();
    return 0;
}
/*
4 6 1
0 1
0 2
0 3
1 2
1 3
2 3

5 6 4
0 1
0 2
1 2
2 3
3 4
4 2

5 4 6
0 1
0 2
0 3
3 4

如果任何一个点的度数大于等于3 则 s 不存在

否则若存在环 那么 s = 1 极限为 所有环长之和

否则 s = 0 极限为 所有链的 n（n-1）/2 之和

特殊情况

三叶草会在一回合之后衰变成三元环
*/