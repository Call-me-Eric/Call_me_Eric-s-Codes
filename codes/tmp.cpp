#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
const int N=2007,xx[8]={1,2,2,1,-1,-2,-2,-1},yy[8]={2,1,-1,-2,-2,-1,1,2},INF=1e9;
int n,m,xa,ya,xb,yb;
int d1[N][N],d2[N][N];
struct poi {
    int x,y;
    poi (int _x=0,int _y=0) { x=_x,y=_y; }
};
queue <poi> Q;
void BFS(int sx,int sy,auto &mp)
{
    Q.push(poi(sx,sy)); mp[sx][sy]=0;
    while(!Q.empty())
    {
        poi u=Q.front(); Q.pop();
        for(int k=0;k<8;k++)
        {
            int tx=u.x+xx[k],ty=u.y+yy[k];
            if(tx<1||tx>n||ty<1||ty>m||mp[tx][ty]<INF) continue;
            mp[tx][ty]=mp[u.x][u.y]+1; Q.push(poi(tx,ty));
        }
    }
}
void dfs(int sx,int sy,auto &mp)
{
    for(int k=0;k<8;k++)
    {
        int tx=sx+xx[k],ty=sy+yy[k];
        if(tx<1||tx>n||ty<1||ty>m||mp[tx][ty]>=mp[sx][sy]) continue;
        cout<<tx<<" "<<ty<<endl; dfs(tx,ty,mp); break;
    }
}
int main()
{
    freopen("ans.out","w",stdout);
    memset(d1,0x3f,sizeof(d1)); memset(d2,0x3f,sizeof(d2));
    cin>>n>>m; cin>>xa>>ya>>xb>>yb;
    BFS(n/2,m/2,d1); BFS(n/2+1,m/2,d2);
    int wht=d1[xa][ya],blk=d2[xb][yb];
    int w_b=d2[xa][ya],b_w=d1[xb][yb];
    printf("%d %d %d %d\n",wht,blk,w_b,b_w);getchar();
    if( ((xa+ya)&1) == ((xb+yb)&1) )
    {
        if(blk<wht) { printf("BLACK\n"); dfs(xb,yb,d2); return 0; }
        if( b_w-1<wht )
        {
            printf("BLACK\n");
            dfs(xb,yb,d1); dfs(n/2,m/2,d2);
            return 0;
        }
        printf("WHITE\n"); dfs(xa,ya,d1);
        return 0;
    }
    if(wht<=blk) { printf("WHITE\n"); dfs(xa,ya,d1); return 0; }
    if(w_b-1<=blk)
    {
        printf("WHITE\n");
        dfs(xa,ya,d2); dfs(n/2+1,m/2,d1);
        return 0;
    }
    printf("BLACK\n"); dfs(xb,yb,d2);
    return 0;
}