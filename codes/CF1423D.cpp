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
const int maxn = 2e2 + 10, maxm = 1e6 + 10;
int n, m;
int K, T, W;
int mp[maxn][maxn];//1 = water, 0 = land, 2 = start, 3 = end
int wind[maxm];
bitset<4510> supply[maxn][maxn];
int sx, sy, tx, ty;

const int dx[5] = {-1, 1, 0, 0, 0};
const int dy[5] = { 0, 0,-1, 1, 0};
int f[2][maxn][maxn];
queue<pair<int,int> > que[2];
bool book[2][maxn][maxn];
void dfs(int x,int y){
    book[1][x][y] = 1;
    for(int i = 0;i < 4;i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 1 || ny < 1 || nx > n || ny > m || book[1][nx][ny] || !mp[nx][ny])continue;
        dfs(nx,ny);
    }
}
void main(){
    n = read(); m = read();
    K = read(); T = read(); W = read();
    auto calc = [](char ch){
        if(ch == 'L')return 0;if(ch == 'S')return 1;
        if(ch == 'M')return 2;if(ch == 'P')return 3;
        if(ch == 'N')return 0;if(ch == 'E')return 3;
        if(ch == 'W')return 2;if(ch == 'C')return 4;
    };
    auto check = [](int x,int y){return x >= 1 && x <= n && y >= 1 && y <= m;};
    char ch;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            ch = getchar();
            while(!isupper(ch))ch = getchar();
            // printf("(%d,%d),ch = %c\n",i,j,ch);
            mp[i][j] = calc(ch);
            if(mp[i][j] == 2){sx = i;sy = j;mp[i][j] = 1;}
            if(mp[i][j] == 3){tx = i;ty = j;mp[i][j] = 1;}
            // printf("%d ",mp[i][j]);
        }
        // puts("");
    }
    for(int i = 1;i <= W;i++){ch = getchar();while(!isupper(ch))ch = getchar();wind[i] = calc(ch);}
    // for(int i = 1;i <= W;i++)printf("%d ",wind[i]);puts("");
    for(int i = 1;i <= T;i++){int x = read() + 1, y = read() + 1, k = read();if(k <= 4500)supply[x][y][k] = 1;}

    dfs(sx,sy);if(!book[1][tx][ty]){puts("-1");return;}
    for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)mp[i][j] &= book[1][i][j];

    if(sx == tx && sy == ty){puts("0");return;}
    memset(f,-0x3f,sizeof(f));
    int day = 0;que[0].push(make_pair(sx,sy));f[0][sx][sy] = K;book[0][sx][sy] = 1;
    memset(book[1],0,sizeof(book[1]));
    while(1){
        day++;int opt = day & 1;
        if(que[opt ^ 1].empty()){puts("-1");break;}
        while(!que[opt ^ 1].empty()){
            int x = que[opt ^ 1].front().first, y = que[opt ^ 1].front().second;que[opt ^ 1].pop();
            book[opt ^ 1][x][y] = 0;if(f[opt ^ 1][x][y] <= 0)continue;
            int wx = dx[wind[day]], wy = dy[wind[day]];
            for(int i = 0;i < 5;i++){
                int nx = x + wx + dx[i],ny = y + wy + dy[i];
                if(!check(nx,ny) || !mp[nx][ny])continue;
                if(!mp[x + wx][y + wy] && !mp[x + dx[i]][y + dy[i]])continue;
                int tmp = supply[nx][ny][day] ? K : (f[opt ^ 1][x][y] - 1);
                if(!book[opt][nx][ny]){que[opt].push(make_pair(nx,ny));book[opt][nx][ny] = 1;f[opt][nx][ny] = tmp;}
                else f[opt][nx][ny] = max(f[opt][nx][ny],tmp);
            }
        }
        // printf("day = %d\n",day);
        // for(int i = 1;i <= n;i++){
        //     for(int j = 1;j <= m;j++){
        //         printf("%d ",f[opt][i][j]);
        //     }
        //     puts("");
        // }
        if(book[opt][tx][ty]){printf("%d\n",day);break;}
        if(day >= 5000)assert(0);
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