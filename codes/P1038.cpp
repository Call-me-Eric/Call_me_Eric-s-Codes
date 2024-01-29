#include<bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 101;
int C[maxn];
bool book[maxn];
int U[maxn];
int ind[maxn], outd[maxn];
struct edge{
    int to, w,nexte,from;
}e[maxn * maxn];
int front[maxn];
int tot = 1;
void add(int x,int y,int w){
    e[tot].from = x;
    e[tot].nexte = front[x];
    e[tot].to = y;
    e[tot].w = w;
    front[x] = tot++;
}
queue<int> que;
vector<int> points;
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        scanf("%d%d",&C[i],&U[i]);
        if(C[i] > 0){
            que.push(i);
            book[i] = 1;
        }
        else C[i] -= U[i];
    }
    int x, y, w;
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&x,&y,&w);
        outd[x]++;
        add(x,y,w);
    }
    while(!que.empty()){
        int head = que.front();
        que.pop();
        
        if(C[head] <= 0)continue;
        for(int i = front[head];i != 0;i = e[i].nexte){
            int to = e[i].to;
            int w = e[i].w;
            C[to] += (e[i].w * C[head]);
            if(!book[to]){
                que.push(to);
                book[to] = true;
            }
        }
    }
    bool flag = 0;
    for(int i = 1;i <= n;i++){
        if(!outd[i] && C[i] > 0){
            printf("%d %d\n",i,C[i]);
            flag = 1;
        }
    }
    if(!flag){
        puts("NULL");
    }
    return 0;
}