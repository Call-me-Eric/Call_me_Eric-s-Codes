#include<bits/stdc++.h>
#include "dudu.h"
using namespace std;
const int maxn = 1e3 + 10;
int val[maxn][maxn];
bool book[maxn][maxn];
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = { 0,-1, 1, 0};
int va, sx, sy;
void found(int n,int L){
    auto getval = [](int x,int y)->int{
        if(val[x][y])return val[x][y];
        return val[x][y] = query(x, y);
    };
    if(n == 1){answer(1,1);}
    if(n == 2){
        if(getval(1,1) == 1)answer(1,1);
        if(getval(1,2) == 1)answer(1,2);
        if(getval(2,1) == 1)answer(2,1);
        answer(2,2);
    }
    va = n * n + 1;
    mt19937 rnd(time(0));
    for(int i = 1;i <= 200;i++){
        int stx = rnd() % n + 1, sty = rnd() % n + 1;
        if(book[stx][sty])continue; book[stx][sty] = 1;
        int v = getval(stx,sty);
        if(v < va){sx = stx;sy = sty;va = v;}
        if(v == 1)answer(stx,sty);
        // cerr << "stx = " << stx << " sty = " << sty << "\n";
    }
    // cerr << "sx = " << sx << " sy = " << sy << "\n";
    while(1){
        int x = sx, y = sy;
        // cerr << "x = " << x << " y = " << y << "val = " << va << "\n";
        for(int k = 0;k < 4;k++){
            int nx = dx[k] + x, ny = dy[k] + y;
            if(nx < 1 || ny < 1 || nx > n || ny > n)continue;
            if(book[nx][ny])continue;book[nx][ny] = 1;
            int v = getval(nx,ny);
            if(v == 1){answer(nx,ny);}
            if(v < va){sx = nx;sy = ny;va = v;}
        }
    }
}