#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<string.h>
#include<math.h>
using namespace std;
int n, m;
int temp = 0;
struct node{
    int lvl;
    int c;
}tmp,t;
queue<node> que;
int c[22];
int book[110][22];
int bfs(){
    tmp.lvl = 1;
    que.push(tmp);
    while(!que.empty()){
        tmp = que.front();
        que.pop();
        for(int i = 1;i <= m;i++){
            if(c[i] == 0 || tmp.lvl + c[i] < 1 || tmp.lvl + c[i] > n)continue;
            if(book[tmp.lvl + c[i]][i] > book[tmp.lvl][tmp.c] + abs(tmp.c - i) + abs(c[i]) * 2){
                book[tmp.lvl + c[i]][i] = book[tmp.lvl][tmp.c] + abs(tmp.c - i) + abs(c[i]) * 2;
                t.c = i;
                t.lvl = tmp.lvl + c[i];
                que.push(t);
            }
        }
    }
    int res = book[n][1];
    for(int i = 2;i <= m;i++){
        res = min(res,book[n][i]);
    }
    if(res == book[1][0]){
        return -1;
    }
    return res;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i++){
        scanf("%d",&c[i]);
        if(c[i] == 0)temp = i;
    }
    memset(book,0x3f,sizeof(book));
    tmp.c = temp;
    book[1][temp] = 0;
    printf("%d\n",bfs());
    return 0;
}
/*
20 20
18 -5 12 10 17 5 -13 17 0 15 -16 14 5 12 -10 11 -17 1 -4 10 
*/