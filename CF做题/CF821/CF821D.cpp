#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, m, k;

struct hash_function{size_t operator ()(pair<int,int> a) const{return (a.first) * (m + 2) + (a.second);}};
map<pair<int,int>,int> mp;
int cnt, x[maxn], y[maxn];

struct node{
    int first, second;
    node(int f = 0,int s = 0):first(f),second(s){}
    friend bool operator < (node a,node b){return a.first != b.first ? a.first < b.first : a.second < b.second;}
    friend bool operator > (node a,node b){return a.first != b.first ? a.first > b.first : a.second > b.second;}
};

int dis[maxn << 1];bool book[maxn << 1];
priority_queue<node,vector<node>,greater<node> > que;
vector<int> line[maxn], row[maxn];
signed main(){
    n = read();m = read();k = read();
    for(int i = 1;i <= k;i++){
        x[i] = read();y[i] = read();
        mp[make_pair(x[i],y[i])] = ++cnt;
        line[x[i]].push_back(cnt);
        row[y[i]].push_back(cnt);
    }
    int S = mp[make_pair(1,1)], T = mp[make_pair(n, m)];
    memset(dis,0x3f,sizeof(dis));dis[S] = 0;que.push(node(0,S));
    while(!que.empty()){
        int u = que.top().second;que.pop();
        if(book[u])continue;book[u] = 1;
        vector<int> to1,to0;to1.clear();to0.clear();
        int i = u;
        int pos = mp[make_pair(x[i],y[i])];
        for(int j : line[x[i]]){to1.push_back(j);}
        for(int j : row[y[i]]){to1.push_back(j);}
        for(int j : line[x[i] + 1]){to1.push_back(j);}
        for(int j : line[x[i] - 1]){to1.push_back(j);}
        for(int j : row[y[i] + 1]){to1.push_back(j);}
        for(int j : row[y[i] - 1]){to1.push_back(j);}
        if(x[i] > 1)for(int j : line[x[i] - 2]){to1.push_back(j);}
        if(y[i] > 1) for(int j : row[y[i] - 2]){to1.push_back(j);}
        for(int j : line[x[i] + 2]){to1.push_back(j);}
        for(int j : row[y[i] + 2]){to1.push_back(j);}

        if(mp[make_pair(x[i] - 1,y[i])]){to0.push_back(mp[make_pair(x[i] - 1,y[i])]);}
        if(mp[make_pair(x[i],y[i] - 1)]){to0.push_back(mp[make_pair(x[i],y[i] - 1)]);}
        if(mp[make_pair(x[i] + 1,y[i])]){to0.push_back(mp[make_pair(x[i] + 1,y[i])]);}
        if(mp[make_pair(x[i],y[i] + 1)]){to0.push_back(mp[make_pair(x[i],y[i] + 1)]);}
        // printf("dis[u = %d] = %d->\n",u,dis[u]);
        for(int v : to0){
            if(dis[v] > dis[u]){
                dis[v] = dis[u];
                que.push(node(dis[v],v));
            }
        }
        for(int v : to1){
            if(dis[v] > dis[u] + 1){
                dis[v] = dis[u] + 1;
                que.push(node(dis[v],v));
            }
        }
    }
    if(!mp[make_pair(n ,m)]){
        T = mp[make_pair(n, m)] = ++cnt;
        int pos = cnt;
        for(int j : line[n]){dis[T] = min(dis[T],dis[j] + 1);}
        for(int j : row[m]){dis[T] = min(dis[T],dis[j] + 1);}
        for(int j : line[n - 1]){dis[T] = min(dis[T],dis[j] + 1);}
        for(int j : row[m - 1]){dis[T] = min(dis[T],dis[j] + 1);}
    }
    printf("%d\n",dis[T] == 0x3f3f3f3f ? -1 : dis[T]);
    // for(int i = -2;i <= n;i++){
    //     for(int j = -2;j <= m;j++){
    //         if(mp[make_pair(i,j)]){
    //             printf("(%d,%d)id=%d dis=%d\n",i,j,mp[make_pair(i,j)],dis[mp[make_pair(i,j)]]);
    //         }
    //     }
    // }
    return 0;
}