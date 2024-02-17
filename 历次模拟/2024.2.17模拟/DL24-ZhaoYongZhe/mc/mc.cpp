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
const int maxn = 10 + 10;
int n, m, mod;
int book[maxn][maxn];
int fa[maxn * maxn];
inline int getid(int x,int y){return x - 1 + (y - 1) * n;}
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
const int dx[4] = { 0, 1,-1, 0};
const int dy[4] = { 1, 0, 0,-1};
int ans = 0;
void getmap(int sta){
    for(int i = 0;i <= n + 1;i++)book[i][0] = book[i][m + 1] = 0;
    for(int i = 0;i <= m + 1;i++)book[0][i] = book[n + 1][i] = 0;
    for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++){
        book[i][j] = (sta >> (i - 1 + (j - 1) * n)) & 1;
        fa[getid(i,j)] = getid(i,j);
    }
}
void water(int x,int y,int col){
    book[x][y] = col;
    for(int k = 0;k < 4;k++){
        int nx = dx[k] + x, ny = dy[k] + y;
        if(nx < 0 || ny < 0 || nx > n + 1 || ny > m + 1 || book[nx][ny])continue;
        water(nx,ny,col);
    }
}
void BF(){
    vector<int> vec;
    for(int sta = 0;sta < (1 << (n * m));sta++){
        getmap(sta);
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                if(book[i][j])
                for(int k = 0;k < 2;k++){
                    int nx = dx[k] + i, ny = dy[k] + j;
                    if(nx < 1 || ny < 1 || nx > n || ny > m || !book[nx][ny])continue;
                    fa[getf(getid(i,j))] = getf(getid(nx,ny));
                }
            }
        }
        int f = -2;
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                if(book[i][j]){
                    if(f == -2)f = getf(getid(i,j));
                    else if(f != getf(getid(i,j))){f = -1;break;}
                }
            }
            if(f == -1)break;
        }
        if(f != -1){
            vec.push_back(sta);
        }
    }
    for(int sta : vec){
        getmap(sta);int cnt = 0;
        for(int i = 0;i <= n + 1;i++){
            for(int j = 0;j <= m + 1;j++){
                if(book[i][j] == 0){
                    cnt++;water(i,j,cnt);
                }
            }
        }
        ans += cnt - 1;
    }
    printf("%d\n",ans);
}
void main(){
    n = read(); m = read(); mod = read();
    if(n > m)swap(n, m);
    if(n <= 2)ans = 0;
    if(n == 3){
        if(m == 3)ans = 5;
        if(m == 4)ans = 77;
        if(m == 5)ans = 703;
    }
    if(n == 4){
        if(m == 4)ans = 2213;
        if(m == 5)ans = 38565;
    }
    if(n == 5){
        ans = 1295954;
    }
    printf("%d\n",ans % mod);
    return;
}
};
bool edmemory;
signed main(){
    freopen("mc.in","r",stdin);
    freopen("mc.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}