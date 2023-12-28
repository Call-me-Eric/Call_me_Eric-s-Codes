#include<bits/stdc++.h>
#define exist(x,y) (0 <= (x) && (x) <= n + 1 && 0 <= (y) && (y) <= n + 1)
using namespace std;
int n, q, P;
const int maxn = 1100;
int a[maxn][maxn];
char ch[maxn][maxn];
int f[maxn][maxn];
bool mapp[maxn][maxn];
const int dx[8] = { 1, 1, 1, 0, 0,-1,-1,-1};
const int dy[8] = { 1, 0,-1, 1,-1, 1, 0,-1};
struct node{int x, y;node(int x = 0,int y = 0){this->x = x;this->y = y;}};
queue<node> que;
queue<node> H;
void bfs(int x,int y){
    f[x][y] = 2;
    H.push(node(x,y));
    while(!H.empty()){
        node u = H.front();H.pop();
        for(int k = 0;k < 8;k++){
            int nx = u.x + dx[k];
            int ny = u.y + dy[k];
            if(!exist(nx,ny))continue;
            if(mapp[nx][ny] == mapp[u.x][u.y]){
                if(f[nx][ny] == 2)continue;
                f[nx][ny] = 2; a[nx][ny] = a[u.x][u.y];
                H.push(node(nx,ny));
            }
            else{
                if(f[nx][ny])continue;
                f[nx][ny] = 1;
                que.push(node(nx,ny));
            }
        }
    }
}
signed main(){
    scanf("%d%d",&n,&q);
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= n;j++)
            mapp[i][j] = ch[i][j] == '1';
    }
    que.push(node(0,0));
    int last = 0;
    node u;
    while(!que.empty()){
        u = que.front();que.pop();
        if(f[u.x][u.y] == 2)continue;
        if(mapp[u.x][u.y] != last && mapp[u.x][u.y])P++;
        last = mapp[u.x][u.y];
        a[u.x][u.y] = P;
        bfs(u.x,u.y);
    }
    for(int i = 1;i <= q;i++){
        int x, y;
        scanf("%d%d",&x,&y);
        if(i ^ 1)putchar(' ');
        printf("%d",a[x][y]);
    }
    puts("");
    return 0;
}