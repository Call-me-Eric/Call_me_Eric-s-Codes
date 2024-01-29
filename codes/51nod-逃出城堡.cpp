#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
struct node{
    int g;
    int x, y;
};
int n;
int next_[4][2] = {0,1,0,-1,1,0,-1,0};
char c[N][N];
bool book[N][N];
int ans = 0;
queue<node> q;

int main(){//TODO main()

    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%s",c[i] + 1);
    }
    node tmp,tmp1;
    int sx = 0, sy = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(c[i][j] == 'S' || c[i][j] == '*'){
                tmp.x = i;
                tmp.y = j;
                tmp.g = (c[i][j] == 'S' ? 1 : 0);
                q.push(tmp);
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            book[i][j] = 0;
        }
    }
    book[tmp.x][tmp.y] = 1;
    q.push(tmp);
    tmp.x = -1;
    q.push(tmp);
    while(!q.empty()){
        tmp = q.front();
        q.pop();
        if(tmp.x == -1){
            ans++;
            if(q.empty()){
                break;
            }
            q.push(tmp);
            continue;
        }
        for(int i = 0;i < 4;i ++){
            tmp1.x  = tmp.x + next_[i][0];
            tmp1.y = tmp.y + next_[i][1];
            if(tmp1.x < 1 || tmp1.x > n || tmp1.y < 1 || tmp1.y > n){
                if(tmp.g){
                    printf("%d\n",ans + 1);
                    return 0;
                }
                else continue;
            }
            if(c[tmp1.x][tmp1.y] == '#')continue;
            if(c[tmp1.x][tmp1.y] == '*')continue;
            if(book[tmp1.x][tmp1.y])continue;
            tmp1.g = tmp.g;
            book[tmp1.x][tmp1.y] = 1;
            q.push(tmp1);
        }
    }
    puts("IMPOSSIBLE");
    return 0;
}