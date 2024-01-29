#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 10;
int n, m;
int p[maxn][maxn];
bool book[maxn][maxn];
struct node{
    int x,y;
};
int nextt[4][2] = {1,0,-1,0,0,1,0,-1};
bool bfs(int maxx){
    queue<node> que;
    que.push(node{1,1});
    book[1][1] = 1;
    while(!que.empty()){
        int xx = que.front().x;
        int yy = que.front().y;
        que.pop();
        for(int i = 0;i < 4;i++){
            int x = xx + nextt[i][0];
            int y = yy + nextt[i][1];
            if(x < 1 || y < 1 || x > n || y > m || book[x][y] || p[x][y] > maxx)continue;
            book[x][y] = 1;
            que.push(node{x,y});
            if(x == n)return 1;
        }
    }
    return 0;
}
int main(){
    int l = 99999, r = -9;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            scanf("%d",&p[i][j]);
            l = min(l,p[i][j]);
            r = max(r,p[i][j]);
        }
    }
    int ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        memset(book,0,sizeof(book));
        if(bfs(mid))r = mid - 1,ans = mid;
        else l = mid + 1;
    }
    printf("%d",ans);
    return 0;
}