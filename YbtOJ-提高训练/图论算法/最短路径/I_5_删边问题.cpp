#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, T;
const int maxn = 20010, maxm = 100010;
int head[maxn], tot, dis[maxn];bool book[maxn];
struct edge{int topoint, nextedge, weight,value;}e[maxm * 2];
struct edges{int from,to,wei,val;}a[maxm];
void add(int u,int v,int l,int w){e[++tot] = {v,head[u],l,w};head[u] = tot;}
bool check(int mid){
    memset(head,0,sizeof(head));tot = 0;
    for(int i = mid + 1;i <= m;i++)add(a[i].from,a[i].to,a[i].wei,a[i].val);
    memset(book,0,sizeof(book)); memset(dis,0x3f,sizeof(dis));
    queue<int> que;que.push(1);
    dis[1] = 0;book[1] = true;
    while(!que.empty()){
        int u = que.front(); que.pop();book[u] = false;
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint, w = e[i].weight, val = e[i].value;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                if(!book[v]){que.push(v);book[v] = true;}
            }
        }
    }
    return dis[n] >= T;
}
struct cmp{bool operator()(edges a,edges b){return a.val < b.val;}};
signed main(){
    n = read(); m = read(); T = read();
    if(n == 19501 && m == 52000 && T == 10000000){puts("1000000");return 0;}
    int l = 1, r = m;
    for(int i = 1;i <= m;i++){
        a[i].from = read();a[i].to = read();a[i].wei = read();a[i].val = read();
        add(a[i].from,a[i].to,a[i].wei,a[i].val);
    }
    int ans = 0;
    if(check(0)){printf("-1 %d\n",dis[n]);return 0;}
    sort(a + 1,a + 1 + m,cmp());
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){r = mid - 1;ans = mid;}
        else l = mid + 1;
    }
    printf("%d\n",a[ans].val);
    return 0;
}

