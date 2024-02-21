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
const int maxn = 30 + 10;
char ch[maxn][maxn];
int n, m;
int sx, sy, tx, ty;
const int dx[4] = { 0, 0, 1,-1};
const int dy[4] = { 1,-1, 0, 0};
const char opt[5] = {'R','L','D','U'};
int cnt;
bool vis[maxn][maxn];
void check(int x,int y){
    vis[x][y] = 1;cnt--;
    for(int i = 0;i < 4;i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 1 || ny < 1 || nx > n || ny > m)continue;
        if(vis[nx][ny] || ch[nx][ny] == 0)continue;
        check(nx,ny);
    }
}
string ans = "";
void work(int k){
    for(int i = 1;;i++){
        if(ch[tx + dx[k] * i][ty + dy[k] * i] == 0){
            ans += string(i - 1,opt[k ^ 1]) + string(i,opt[k]);
            break;
        }
        if(ch[sx - dx[k] * i][sy - dy[k] * i] == 0){
            ans += string(i,opt[k ^ 1]) + string(i,opt[k]);
            break;
        }
    }
    sx += dx[k];sy += dy[k];
}
void solve(int k){
    vis[sx][sy] = 1;
    if(k && (abs(sx - tx) + abs(sy - ty) < 2)){
        cout << ans;
        if(sx == tx + 1)putchar('U');
        if(sx == tx - 1)putchar('D');
        if(sy == ty + 1)putchar('L');
        if(sy == ty - 1)putchar('R');
        reverse(ans.begin(),ans.end());
        cout << ans << "\n";exit(0);
    }
    for(int i = 0;i < 4;i++){
        int nx = sx + dx[i], ny = sy + dy[i];
        if(nx < 1 || ny < 1 || nx > n || ny > m)continue;
        if(ch[nx][ny] == 1 && !vis[nx][ny]){work(i);solve(k);work(i ^ 1);}
    }
}
void main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        cin >> ch[i] + 1;
        for(int j = 1;j <= m;j++){ch[i][j] -= '0';cnt += ch[i][j] == 1;}
    }
    sx = read(); sy = read(); tx = read(); ty = read();
    check(sx,sy);if(cnt > 0){puts("-1");return;}
    memset(vis,0,sizeof(vis));solve(0);
    memset(vis,0,sizeof(vis));solve(1);
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
/*
2 2
11
11
1 1 2 2
*/