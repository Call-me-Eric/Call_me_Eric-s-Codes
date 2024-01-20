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
const int maxn = 1e3 + 10;
int val[maxn][maxn];
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = { 0,-1, 1, 0};

struct node{
    int x, y, val;
    node(int x = 0,int y = 0,int val = 0):x(x),y(y),val(val){}
    friend bool operator < (node a,node b){return a.val < b.val;}
};
priority_queue<node> que;
void main(){
    freopen("dudu.in","w",stdout);
    mt19937 rnd(time(0));
    int n = 1000, L = 3100;
    int stx = rnd() % n + 1, sty = rnd() % n + 1;
    val[stx][sty] = 1;que.push(node(stx,sty,rnd()));int cnt = 1;
    while(cnt < n * n){
        int x = que.top().x, y = que.top().y;que.pop();
        for(int k = 0;k < 4;k++){
            int nx = dx[k] + x, ny = dy[k] + y;
            if(nx < 1 || ny < 1 || nx > n || ny > n || val[nx][ny])continue;
            val[nx][ny] = ++cnt;
            que.push(node(nx,ny,rnd()));
        }
    }
    printf("%d %d\n",n,L);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            printf("%d%c",val[i][j]," \n"[j == n]);
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