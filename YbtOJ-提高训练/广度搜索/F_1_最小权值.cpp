#include<bits/stdc++.h>
#define exist(x,y) (1 <= (x) && (x) <= n && 1 <= (y) && (y) <= m)
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 1010;
int a[maxn][maxn];
bool book[maxn][maxn], visit[maxn][maxn];
const int dx[4] = {0,-1,1,0};
const int dy[4] = {1,0,0,-1};
void flood_fill(int sx,int sy,int mid){
    if(a[sx][sy] > mid)return;
    queue<pair<int,int> > que;
    book[sx][sy] = true;
    pair<int,int> tmp;
    que.push(make_pair(sx,sy));
    while(!que.empty()){
        tmp = que.front();que.pop();
        for(int i = 0;i < 4;i++){
            int nx = dx[i] + tmp.first;
            int ny = dy[i] + tmp.second;
            if(exist(nx,ny) && a[nx][ny] <= mid && !book[nx][ny]){
                book[nx][ny] = true;
                que.push(make_pair(nx,ny));
            }
        }
    }
}
bool check(int mid){
    memset(book,0,sizeof(book));
    memset(visit,0,sizeof(visit));
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            if(!book[i][j])flood_fill(i,j,mid);
    queue<pair<int,int> > que;
    for(int i = 1;i <= m;i++)
        if(book[1][i])que.push(make_pair(1,i));
    while(!que.empty()){
        pair<int,int> tmp = que.front();que.pop();
        for(int i = 0;i < 4;i++){
            int nx = dx[i] + tmp.first;
            int ny = dy[i] + tmp.second;
            if(exist(nx,ny) && book[nx][ny] && !visit[nx][ny]){
                que.push(make_pair(nx,ny));
                visit[nx][ny] = true;
            }
        }
    }
    for(int i = 1;i <= m;i++)if(visit[n][i])return true;
    return false;
}
signed main(){
    int maxx = -1;
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            a[i][j] = read();
            maxx = max(maxx,a[i][j]);
        }
    }
    int l = 0, r = maxx + 1,ans = 0;
    while(l < r){
        int mid = (l + r) >> 1;
        if(check(mid)){r = mid;}
        else l = mid + 1;
    }
    printf("%d\n",r);
    return 0;
}
