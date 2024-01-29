#include<bits/stdc++.h>
using namespace std;
inline void read(int &x)
{
    x=0; char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
}
const int maxn = 500 + 10;
int a[maxn][maxn];
int n, m;
struct node{
    int x,y;
    bool book = false;
};
bool book2[maxn];
struct cmp{
    bool operator ()(node x1,node x2){
        return x1.x < x2.x;
    }
};
int l[maxn][maxn];
int r[maxn][maxn];
int from[maxn][maxn];
node section[maxn];
int nextt[4][2] = {1,0,-1,0,0,-1,0,1};
bool book[maxn][maxn];
void dfs(int x,int y){//TODO dfs(int,int)
    book[x][y] = 1;
    for(int i = 0;i < 4;i++){
        int nx = nextt[i][0] + x;
        int ny = nextt[i][1] + y;
        if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
        if(a[nx][ny] >= a[x][y])continue;
        if(!book[nx][ny])dfs(nx,ny);
        if(l[nx][ny] < l[x][y]){
            l[x][y] = l[nx][ny];
        }
        if(r[nx][ny] > r[x][y]){
            r[x][y] = r[nx][ny];
        }
    }
}
int main(){//TODO main()
    read(n);
    read(m);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            read(a[i][j]);
        }
    }
    memset(l,0x3f,sizeof(l));
    memset(r,0,sizeof(r));
    memset(book,0,sizeof(book));
    for(int i = 1;i <= m;i++){
        l[n][i] = r[n][i] = i;
    }
    for(int j = 1;j <= m;j++){
        if(book[1][j])continue;
        book[1][j] = 1;
        dfs(1,j);
    }
    int total = 0;
    bool flag = 0;
    for(int i = 1;i <= m;i++){
        if(book[n][i] == 0)flag = 1,total++;
    }
    if(flag){
        printf("0\n%d\n",total);
        return 0;
    }
    total = 0;
    int last = 1;
    while(last <= m){
        int t = 0;
        for(int i = 1;i <= m;i++){
            if(l[1][i] <= last)t = max(r[1][i],t);
        }
        last = t + 1;total++;
    }
    printf("1\n%d",total);
    return 0;
}