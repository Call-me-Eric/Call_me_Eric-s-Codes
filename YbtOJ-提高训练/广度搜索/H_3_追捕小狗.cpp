#include<bits/stdc++.h>
#define exist(x,y) (1 <= x && x <= n && 1 <= y && y <= n)
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1 ;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n;
const int maxn = 110;
char ch[maxn][maxn];
bool mapp[maxn][maxn];
bool book[maxn][maxn];
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = { 0, 1, 0,-1};
signed main(){
    scanf("%d",&n);
    int sx,sy,tx,ty;
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= n;j++){
            switch(ch[i][j]){
                case 'J':{tx = i; ty = j; break;}
                case 'F':{sx = i; sy = j; break;}
                case '*':{mapp[i][j] = true; break;}
                case '.':{mapp[i][j] = false;break;}
                default: break;
            }
        }
    }
    queue<pair<int,int> > que;
    pair<int,int> u;
    int dir = 0;
    que.push(make_pair(sx,sy));
    for(int t = 0;!que.empty();t++){
        for(int k = que.size();k;k--){
            u = que.front();que.pop();
            int x = u.first, y = u.second;
            for(int i = 0;i < 4;i++){
                int nx = x + dx[i], ny = y + dy[i];
                if(exist(nx,ny) && (!mapp[nx][ny]) && (!book[nx][ny])){
                    que.push(make_pair(nx,ny));
                    book[nx][ny] = 1;
                }
            }
        }
        if(book[tx][ty]){printf("%d\n",t);return 0;}
        int cnt = 0;
        while(1){
            int x = tx + dx[dir], y = ty + dy[dir];
            if(exist(x,y) && !mapp[x][y]){tx = x;ty = y;break;}
            dir++; cnt++;
            if(cnt == 4)break;
            dir %= 4;
        }
    }
    puts("No solution.");
    return 0;
}