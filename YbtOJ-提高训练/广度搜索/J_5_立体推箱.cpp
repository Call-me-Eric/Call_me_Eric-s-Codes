#include<bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 510;
char ch[maxn][maxn];
int d[maxn][maxn][3];
bool book[maxn][maxn][3];
struct node{int x, y, t;//t = 0:竖立在(x,y)位置;t = 1:横向躺着且右边在(x,y)位置;t = 2:纵向躺着且下边在(x,y)位置
node(int x = 0, int y = 0,int t = 0){this->t = t;this->x = x;this->y = y;}}st,ed;
bool operator == (node a,node b){return a.t == b.t && a.x == b.x && a.y == b.y;}
const int dx[3][4] = {
    {-1,0,2,0},
    {-1,0,1,0},
    {-2,0,1,0}
};
const int dy[3][4] = {
    {0,2,0,-1},
    {0,1,0,-2},
    {0,1,0,-1}
};
const int dt[3][4] = {
    {2,1,2,1},
    {1,0,1,0},
    {0,2,0,2}
};
bool exist(node state){
    int x = state.x, y = state.y, t = state.t;
    if(x < 1 || x > n || y < 1 || y > m || ch[x][y] == '#')return 0;
    if(t == 0)return ch[x][y] != 'E';
    if(t == 1)return 1 < y && ch[x][y - 1] != '#';
    if(t == 2)return 1 < x && ch[x - 1][y] != '#';
}
void bfs(){
    memset(d,0,sizeof(d));
    memset(book,0,sizeof(book));
    queue<node> que;
    que.push(st);
    book[st.x][st.y][st.t] = 1;
    d[st.x][st.y][st.t] = 0;
    while(!que.empty()){
        node u = que.front();que.pop();
        if(u.x == ed.x && u.y == ed.y && u.t == ed.t){printf("%d\n",d[u.x][u.y][u.t]);return;}
        for(int i = 0;i < 4;i++){
            node v = (node){u.x + dx[u.t][i],u.y + dy[u.t][i],dt[u.t][i]};
            if(exist(v) && !book[v.x][v.y][v.t]){
                d[v.x][v.y][v.t] = d[u.x][u.y][u.t] + 1;
                book[v.x][v.y][v.t] = 1;
                que.push(v);
            }
        }
    }
    puts("Impossible");
}
signed main(){
    while(scanf("%d%d",&n,&m) && (n || m)){
    for(int i = 1;i <= n;i++){
        scanf("%s", ch[i] + 1);
    }
    bool flag1 = true, flag2 = true;
    for(int i = n;i && (flag1 || flag2);i--){
        for(int j = m;j && (flag1 || flag2);j--){
            if(flag1 && ch[i][j] == 'X'){
                st.x = i; st.y = j; st.t = 0;
                if(ch[i][j - 1] == 'X')st.t = 1;
                if(ch[i - 1][j] == 'X')st.t = 2;
                flag1 = false;
            }
            if(flag2 && ch[i][j] == 'O'){
                ed.x = i; ed.y = j; ed.t = 0;
                flag2 = false;
            }
        }
    }
    bfs();
    }
    return 0;
}