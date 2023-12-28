#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, K,A,B,C;
const int maxn = 110;
int e[maxn][maxn];
int dis[maxn][maxn][11];
struct node{int x,y,k,cost;};
bool operator < (const node a,const node b){return a.cost < b.cost;}
queue<node> que;
bool book[maxn][maxn][11];
const int dx[4] = {1,0,0,-1};
const int dy[4] = {0,1,-1,0};
signed main(){
    n = read(); K = read(); A = read(); B = read(); C = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            e[i][j] = read();
        }
    }
    memset(dis,0x3f3f3f3f,sizeof(dis));
    dis[1][1][K] = 0;
    book[1][1][K] = true;
    que.push((node){1,1,K,0});
    while(!que.empty()){
        node u = que.front();que.pop();
        book[u.x][u.y][u.k] = false;
            if(e[u.x][u.y] && u.k != K){
                if(dis[u.x][u.y][K] > dis[u.x][u.y][u.k] + A){
                    dis[u.x][u.y][K] = dis[u.x][u.y][u.k] + A;
                    if(!book[u.x][u.y][K]){
                        book[u.x][u.y][K] = true;
                        que.push((node){u.x,u.y,K,dis[u.x][u.y][K]});
                    }
                }
                continue;
            }
            else{
                if(dis[u.x][u.y][K] > dis[u.x][u.y][u.k] + A + C){
                    dis[u.x][u.y][K] = dis[u.x][u.y][u.k] + A + C;
                    if(!book[u.x][u.y][K]){
                        book[u.x][u.y][K] = true;
                        que.push((node){u.x,u.y,K,dis[u.x][u.y][K]});
                    }
                }
            }
        if(u.k > 0){
            for(int i = 0;i < 4;i++){
                int nx = dx[i] + u.x, ny = dy[i] + u.y, k = u.k - 1;
                if(nx < 1 || nx > n || ny < 1 || ny > n)continue;
                int w = (nx < u.x || ny < u.y) ? B : 0;
                if(dis[nx][ny][k] > dis[u.x][u.y][k + 1] + w){
                    dis[nx][ny][k] = dis[u.x][u.y][k + 1] + w;
                    if(!book[nx][ny][k]){
                        que.push((node){nx,ny,k,dis[nx][ny][k]});
                        book[nx][ny][k] = true;
                    }
                }
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = 0;i <= K;i++){ans = min(ans,dis[n][n][i]);}
    printf("%d\n",ans);
    return 0;
}
