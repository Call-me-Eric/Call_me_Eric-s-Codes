#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch >  '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x <<3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10, mod = 1e9 + 7;
int n, m;
vector<vector<int> > que1, que2;
vector<int> edg[maxn * 2][11];int cnt;
void add(int u,int v,int id){
    while(id >= 10){
        edg[++cnt][id % 10].push_back(v);
        v = cnt;id /= 10;
    }
    edg[u][id].push_back(v);
}
int dis[maxn * 2];
bool book[maxn * 2];
signed main(){
    cnt = n = read(); m = read();int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        add(u, v, i); add(v, u, i);
    }
    dis[1] = 0;
    vector<int> tmp;tmp.push_back(1);
    que1.push_back(tmp);book[1] = 1;
    while(!que1.empty()){
        for(auto x : que1){
            for(int d = 0;d < 10;d++){
                tmp.clear();
                for(int i : x){
                    for(int v : edg[i][d]){
                        if(!book[v]){
                            book[v] = 1;dis[v] = (dis[i] * 10LL + d) % mod;
                            tmp.push_back(v);
                        }
                    }
                }
                if(!tmp.empty()){que2.push_back(tmp);}
            }
        }
        que1 = que2; que2.clear();
    }
    for(int i = 2;i <= n;i++){printf("%lld\n",dis[i]);}
    return 0;
}