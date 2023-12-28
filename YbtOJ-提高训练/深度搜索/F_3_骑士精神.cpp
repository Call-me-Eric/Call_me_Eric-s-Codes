#include<bits/stdc++.h>
using namespace std;
int T;
const int maxn = 7;
char mapp[maxn][maxn];
const int dx[8] = {-2,-2,-1,-1, 1, 1, 2, 2};
const int dy[8] = { 1,-1, 2,-2, 2,-2, 1,-1};
const int goal[6][6] = {
    {0,0,0,0,0,0},
    {0,1,1,1,1,1},
    {0,0,1,1,1,1},
    {0,0,0,2,1,1},
    {0,0,0,0,0,1},
    {0,0,0,0,0,0}
};
int now[maxn][maxn];
bool success = 0;
int h(){int cnt = 0;for(int i = 1;i <= 5;i++)for(int j = 1;j <= 5;j++)if(now[i][j] != goal[i][j])cnt++;return cnt;}
void dfs(int step,int x,int y,int maxstep){
    if(step == maxstep){
        if(!h())success = true;
        return;
    }
    for(int i = 0;i < 8;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx > 5 || nx < 1 || ny > 5 || ny < 1)continue;
        swap(now[x][y],now[nx][ny]);
        if(step + h() <= maxstep) dfs(step + 1,nx,ny,maxstep);
        swap(now[x][y],now[nx][ny]);
    }
}
signed main(){
    scanf("%d",&T);
    while(T--){
        success = false;
        int stx = 0,sty = 0;
        for(int i = 1;i <= 5;i++){
            scanf("%s",mapp[i] + 1);
            for(int j = 1;j <= 5;j++){
                if(mapp[i][j] == '*'){stx = i;sty = j;now[i][j] = 2;}
                else now[i][j] = mapp[i][j] - '0';
            }
        }
        if(!h()){puts("0");continue;}
        for(int maxstep = 1;maxstep <= 15;maxstep++){
            dfs(0,stx,sty,maxstep);
            if(success){printf("%d\n",maxstep);break;}
        }
        if(!success)puts("-1");
    }
    return 0;
}