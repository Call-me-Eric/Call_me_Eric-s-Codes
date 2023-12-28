#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=  0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e4 + 10;
int n, m;
char ch[110][110];
inline int getid(int x,int y){return x * m + y - m;}
vector<int> edg[maxn];
const int dx[4] = { 1, 0, 0,-1};
const int dy[4] = { 0, 1,-1, 0};

int match[maxn];
bool vis[maxn];
bool dfs(int u){
    if(vis[u])return false;vis[u] = 1;
    for(int v : edg[u]){
        if(!match[v] || dfs(match[v])){
            match[v] = u;match[u] = v;
            return true;
        }
    }
    return false;
}
bool dfs1(int u){
    if(vis[u])return false;
    vis[u] = 1;bool res = 0;
    for(int v : edg[u]){
        if(res)return true;
        if(!match[v])return true;
        else res |= dfs1(match[v]);
    }
    return res;
}
vector<pair<int,int> > ans;
bool g[200][200];

signed main(){
    n = read();m = read();
    for(int i = 1;i <= n;i++)
        scanf("%s",ch[i] + 1);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(((i + j) & 1) && ch[i][j] == '.')
            for(int k = 0;k < 4;k++){
                int nx = i + dx[k], ny = j + dy[k];
                if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
                if(ch[nx][ny] == '#')continue;
                edg[getid(i, j)].push_back(getid(nx,ny));
                edg[getid(nx,ny)].push_back(getid(i, j));
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(((i + j) & 1)){
                memset(vis,0,sizeof(vis));
                dfs(getid(i,j));
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(ch[i][j] == '#')continue;
            if(!match[getid(i, j)])ans.push_back(make_pair(i, j));
            else{
                memset(vis,0,sizeof(vis));
                vis[getid(i, j)] = 1;
                if(dfs1(match[getid(i, j)]))
                    ans.push_back(make_pair(i, j));
            }
        }
    }
    if(ans.size() == 0){puts("LOSE");return 0;}
    else{
        puts("WIN");
        for(auto i : ans)printf("%d %d\n",i.first,i.second);
    }
    return 0;
}
/*
10 12
.##.....##..  
....##....## 
............
###...###.#.
#..####...##
..#....####.
...##....##. 
#...##..##..
#..#........
..#..#.#..## 
*/