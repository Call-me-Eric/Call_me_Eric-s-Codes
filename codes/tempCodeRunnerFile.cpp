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
const int maxn = 2e3 + 10;
const int dx[8] = {-2,-1, 1, 2, 2, 1,-1,-2};
const int dy[8] = { 1, 2, 2, 1,-1,-2,-2,-1};
int n, m;
struct moves{
    int u, v;
    int edx, edy;
    int pre[maxn][maxn], dis[maxn][maxn];
    void getread(){
        if(u == edx && v == edy)exit(0);
        int x = 0, y = 0;
        // x = read(); y = read();
        if(x == -1 || y == -1)exit(0);
        for(int k = 0;k < 8;k++){
            if(u + dx[k] == x && v + dy[k] == y){
                printf("%d %d\n",u += dx[k], v += dy[k]);fflush(stdout);
                exit(0);
            }
        }
    }
    struct node{
        int x, y, step;
        node(int x = 0,int y = 0,int step = 0
        ):x(x),y(y),step(step){}
    };
    queue<node> que;
    void bfs(int sx,int sy){
        memset(dis,0x3f,sizeof(dis));while(!que.empty())que.pop();
        que.push(node(sx,sy,0));dis[sx][sy] = 0;
        while(!que.empty()){
            int x = que.front().x, y = que.front().y, w = que.front().step;que.pop();
            for(int k = 0;k < 8;k++){
                int nx = x + dx[k], ny = y + dy[k];
                if(nx < 1 || ny < 1 || nx > n || ny > m || dis[nx][ny] != 0x3f3f3f3f)continue;
                dis[nx][ny] = w + 1;pre[nx][ny] = k;
                que.push(node(nx,ny,w + 1));
            }
        }
        // for(int i = 1;i <= n;i++){
        //     for(int j = 1;j <= m;j++){
        //         printf("%d:(%d,%d) ",dis[i][j],i - dx[pre[i][j]],j - dy[pre[i][j]]);
        //     }
        //     puts("");
        // }
        // puts("");
    }
    void move(int opt){printf("%d %d\n",u += dx[opt], v += dy[opt]);fflush(stdout);getread();}
    void move(int x,int y){
        stack<int> stk;
        while(x != u || y != v){
            // printf("(%d,%d)\n",x,y);
            int opt = pre[x][y];
            stk.push(opt);x -= dx[opt];y -= dy[opt];
        }
        while(!stk.empty()){move(stk.top());stk.pop();}
    }
}Black, White;
void main(){
    n = read(); m = read();
    int xW = read(), yW = read();
    int xB = read(), yB = read();
    White.u = xW;White.v = yW;White.bfs(xW,yW);
    White.edx = n / 2,White.edy = m / 2;
    Black.u = xB;Black.v = yB;Black.bfs(xB,yB);
    Black.edx = n / 2 + 1,Black.edy = m / 2;
    bool check = (((xW + yW) & 1) != ((xB + yB) & 1));
    // printf("%d %d %d %d %d\n",White.dis[n / 2][m / 2],White.dis[n / 2 + 1][m / 2],Black.dis[n / 2][m / 2],Black.dis[n / 2 + 1][m / 2],check);
    if((White.dis[n / 2][m / 2] <= Black.dis[n / 2 + 1][m / 2]) && (check || (White.dis[n / 2][m / 2] < Black.dis[n / 2][m / 2]))){
        puts("WHITE");fflush(stdout);
        White.move(n / 2,m / 2);
    }
    if((Black.dis[n / 2 + 1][m / 2] <= White.dis[n / 2][m / 2] - 1) && (!check || (Black.dis[n / 2 + 1][m / 2] < White.dis[n / 2 + 1][m / 2] - 1))){
        puts("BLACK");fflush(stdout);
        Black.getread();Black.move(n / 2 + 1,m / 2);
    }
    if(check){
        puts("WHITE");fflush(stdout);
        White.move(n / 2 + 1,m / 2);
        White.move(1);White.move(4);White.move(7);
    }
    else{
        puts("BLACK");fflush(stdout);
        Black.getread();Black.move(n / 2,m / 2);
        Black.move(7);Black.move(1);Black.move(6);
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