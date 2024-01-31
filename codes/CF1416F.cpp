#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10,INF = 0x7f3f3f3f;
const int dx[4] = { 0,-1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};

int a[maxn], typ[maxn];
int ans[maxn], opt[maxn];//0 => L;1 =>U;2 =>R 3=> D
pair<int,int> pos[maxn];
int n, m;
// inline int getid(int x,int y){return (y) * (n + 2) + x;}
#define getid(x, y) ((y) * (n + 2) + (x))

struct edge1{
    int from, to, L, R;
    edge1(int fr = 0,int to = 0,int L = 0,int R = 0):from(fr),to(to),L(L),R(R){}
}e1[maxn << 3];int totedg;
int in[maxn], out[maxn];

struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int cap = 0,int flow = 0):to(to),nexte(ne),cap(cap),flow(flow){}
}e[maxn << 4];
int tot = 1, head[maxn << 1];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u, v, cap);add(v, u, 0);}

int cur[maxn], dis[maxn];
bool book[maxn]; queue<int> que;
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow; int res = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(e[i].cap > e[i].flow && dis[v] == dis[u] + 1){
            int tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(!tmp){dis[v] = INF;continue;}
            e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            flow -= tmp;res += tmp;
            if(!flow)return res;
        }
    }
    return res;
}
bool bfs(int S,int T){
    while(!que.empty())que.pop();
    for(int i = 1;i <= getid(n,m) + 4;i++){cur[i] = book[i] = 0;dis[i] = INF;}
    que.push(S);dis[S] = 0;cur[S] = head[S];book[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = 0;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] == INF && e[i].cap > e[i].flow){
                dis[v] = dis[u] + 1;cur[v] = head[v];
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return dis[T] != INF;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF,T);
    return mxflow;
}

void solve(){
    totedg = 0;tot = 1;
    
    n = read(); m = read();
    for(int i = 1;i <= getid(n + 1,m + 1) + 4;i++)head[i] = in[i] = out[i] = opt[i] = ans[i] = 0;
    for(int i = 0;i <= n + 1;i++)
        for(int j = 0;j <= m + 1;j++)
            pos[getid(i, j)] = make_pair(i, j);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            a[getid(i,j)] = read();
// puts("Step -5");
    for(int i = 0;i <= n + 1;i++)a[getid(i,0)] = a[getid(i,m + 1)] = INF;
    for(int i = 0;i <= m + 1;i++)a[getid(0,i)] = a[getid(n + 1,i)] = INF;
// puts("Step -4");
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if((i + j) & 1)typ[getid(i, j)] = 2;
            else typ[getid(i,j)] = 1;
            int flag = 1;
            for(int k = 0;k < 4 && flag;k++)
                flag &= (a[getid(dx[k] + i,dy[k] + j)] > a[getid(i,j)]);
            if(flag){puts("NO");return;}
            flag = 1;
            for(int k = 0;k < 4 && flag;k++)
                flag &= (a[getid(dx[k] + i,dy[k] + j)] >= a[getid(i,j)]);
            typ[getid(i,j)] += flag * 2;
        }
    }
// puts("Step -3");
    int S = getid(n, m) + 1, T = getid(n, m) + 2, ss = getid(n, m) + 3, tt = getid(n, m) + 4;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(typ[getid(i,j)] & 1){//奇数点
                if(typ[getid(i,j)] >= 3)//必须点
                    e1[++totedg] = edge1(S,getid(i,j),1,1);
                else//非必须点
                    e1[++totedg] = edge1(S,getid(i,j),0,1);
                for(int k = 0;k < 4;k++)//只从奇数点就可以把所有需要连接的边全部连接
                    if(a[getid(i,j)] == a[getid(i + dx[k],j + dy[k])])
                        e1[++totedg] = edge1(getid(i, j),getid(i + dx[k],j + dy[k]),0,1);
            }
            else{//偶数点
                if(typ[getid(i,j)] >= 3)//必须点
                    e1[++totedg] = edge1(getid(i,j),T,1,1);
                else//非必须点
                    e1[++totedg] = edge1(getid(i,j),T,0,1);
            }
        }
    }
// puts("Step -2");
    e1[++totedg] = edge1(T,S,0,INF);
    int sum = 0, delid = 0;
    for(int i = 1;i <= totedg;i++){
        in[e1[i].to] += e1[i].L; out[e1[i].from] += e1[i].L;
        if(e1[i].R - e1[i].L) addd(e1[i].from,e1[i].to,e1[i].R - e1[i].L);
        if(i == totedg)delid = tot - 1;
    }
    for(int x = 1;x <= n;x++)
    for(int y = 1;y <= m;y++){
        int i = getid(x, y);
        if(in[i] > out[i])addd(ss,i,in[i] - out[i]),sum += in[i] - out[i];
        if(in[i] < out[i])addd(i,tt,out[i] - in[i]);
    }
    if(in[S] > out[S])addd(ss,S,in[S] - out[S]),sum += in[S] - out[S];
    if(in[S] < out[S])addd(S,tt,out[S] - in[S]);
    if(in[T] > out[T])addd(ss,T,in[T] - out[T]),sum += in[T] - out[T];
    if(in[T] < out[T])addd(T,tt,out[T] - in[T]);
    
// puts("Step 0");
    int res = Dinic(ss,tt);
// puts("Step 1");
    // printf("res = %d sum = %d\n",res,sum);
    if(res != sum){puts("NO");return;}
// printf("S = %d T = %d\n",S,T);
// printf("delid = %d, fr = %d, to = %d\n",delid,e[delid ^ 1].to,e[delid].to);
    e[delid].cap = e[delid ^ 1].cap = 0;
    e[delid].flow = e[delid ^ 1].flow = 0;
    Dinic(S,T);
// puts("Step 2");
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(typ[getid(i,j)] & 1){//奇数点
            //老样子，还是从奇数点找双元环，偶数点只是判定是否有解即可
                int chose = 0, nxt = 0;
                for(int ed = head[getid(i,j)];ed;ed = e[ed].nexte)
                    if(e[ed].flow == 1){nxt = e[ed].to;chose = 1;break;}
                if(typ[getid(i,j)] >= 3){//必须点
                    if(!chose){puts("NO");return;}
                    else{
                        int x = pos[nxt].first, y = pos[nxt].second;
                        if(i - x == 0){
                            if(j - y == 1){
                                opt[getid(i,j)] = 0; opt[getid(x,y)] = 2;
                                ans[getid(i,j)] = 1; ans[getid(x,y)] = a[getid(i,j)] - 1;
                            }
                            else{
                                opt[getid(i,j)] = 2; opt[getid(x,y)] = 0;
                                ans[getid(i,j)] = 1; ans[getid(x,y)] = a[getid(i,j)] - 1;
                            }
                        }
                        else{
                            if(i - x == 1){
                                opt[getid(i,j)] = 1; opt[getid(x,y)] = 3;
                                ans[getid(i,j)] = 1; ans[getid(x,y)] = a[getid(i,j)] - 1;
                            }
                            else{
                                opt[getid(i,j)] = 3; opt[getid(x,y)] = 1;
                                ans[getid(i,j)] = 1; ans[getid(x,y)] = a[getid(i,j)] - 1;
                            }
                        }
                    }
                }
                else{//非必须点
                    if(chose){
                        int x = pos[nxt].first, y = pos[nxt].second;
                        if(i - x == 0){
                            if(j - y == 1){
                                opt[getid(i,j)] = 0; opt[getid(x,y)] = 2;
                                ans[getid(i,j)] = 1; ans[getid(x,y)] = a[getid(i,j)] - 1;
                            }
                            else{
                                opt[getid(i,j)] = 2; opt[getid(x,y)] = 0;
                                ans[getid(i,j)] = 1; ans[getid(x,y)] = a[getid(i,j)] - 1;
                            }
                        }
                        else{
                            if(i - x == 1){
                                opt[getid(i,j)] = 1; opt[getid(x,y)] = 3;
                                ans[getid(i,j)] = 1; ans[getid(x,y)] = a[getid(i,j)] - 1;
                            }
                            else{
                                opt[getid(i,j)] = 3; opt[getid(x,y)] = 1;
                                ans[getid(i,j)] = 1; ans[getid(x,y)] = a[getid(i,j)] - 1;
                            }
                        }
                    }
                }
            }
            else{//偶数点
                int chose = 0;
                for(int ed = head[getid(i,j)];ed;ed = e[ed].nexte)
                    if(e[ed].flow == 1){chose = 1;break;}
                if(typ[getid(i,j)] >= 3)//必须点
                    if(!chose){puts("NO");return;}
            }
        }
    }
    for(int i = 1;i <= n;i++)//找其他没有限制的点
        for(int j = 1;j <= m;j++){
            if(ans[getid(i,j)])continue;
            for(int k = 0;k < 4;k++){
                if(a[getid(i + dx[k],j + dy[k])] < a[getid(i,j)]){
                    opt[getid(i,j)] = k;
                    ans[getid(i,j)] = a[getid(i,j)] - a[getid(i + dx[k],j + dy[k])];
                }
            }
        }
    puts("YES");
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++)
            printf("%d ",ans[getid(i,j)]);
        puts("");
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(opt[getid(i,j)] == 0)putchar('L');
            if(opt[getid(i,j)] == 1)putchar('U');
            if(opt[getid(i,j)] == 2)putchar('R');
            if(opt[getid(i,j)] == 3)putchar('D');
            putchar(' ');
        }
        puts("");
    }
}

signed main(){
    int T = read();
    while(T--)solve();
    return 0;
}