#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;

namespace Call_me_Eric{

inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, maxq = 3.2e7 + 10,INF = 0x3f3f3f3f3f3f3f3f;

bitset<maxq> bookprime;
vector<int> prime;
unordered_map<int,vector<pair<int,int> > > mp;
bool ans[maxn];
int exgcd(int &x,int &y,int a,int b){
    if(b == 0){x = 1;y = 0;return a;}
    int t = exgcd(y,x,b,a % b);
    y -= x * (a / b);return t;
}
void init(){
    for(int i = 2;i < maxq;i++){
        if(!bookprime[i])prime.push_back(i);
        for(int j : prime){
            if(i * j >= maxq)break;
            bookprime[i * j] = 1;if(i % j == 0)break;
        }
    }
}

int dis[maxn];queue<int> que;bool book[maxn];
void solve(int k,vector<pair<int,int> > vec){
    // printf("%lld\n",k);
    if(k == 1)return;
    vector<int> fac;
    for(int i : prime){
        if(i > k)break;
        if(k % i == 0){
            fac.push_back(i);
            while(k % i == 0)k /= i;
        }
    }
    if(k > 1)fac.push_back(k);

    if(fac.size() == 1){
        for(auto i : vec)ans[i.second] = (i.first % fac.back() == 0);
        return;
    }
    if(fac.size() == 2){
        int x, y, g = exgcd(x,y,fac[0],fac[1]), s = fac[1] / g;
        for(auto i : vec){
            int n = i.first, id = i.second;
            if(n % g != 0)ans[id] = 0;
            int u = ((__int128_t)x * (n / g) % s + s) % s;
            ans[id] = (n >= fac[0] * u);
        }
        return;
    }

    int p = fac[0];
    fill(dis + 1,dis + 1 + p,INF);dis[0] = 0;
    for(int i : fac){
        if(i != p){
            int c = __gcd(i, p);
            for(int d = 0;d < c;d++){
                int tim = 0;
                for(int u = d,nxt = (u + i) % p;tim <= 2;u = nxt,nxt = (u + i) % p){
                    tim += (u == d);dis[nxt] = min(dis[nxt],dis[u] + i);
                }
            }
        }
    }
    for(auto i : vec){
        int n = i.first, id = i.second;
        ans[id] = n >= dis[n % p];
    }
}
void main(){
    init();int T = read();
    for(int i = 1;i <= T;i++){
        int n = read(), k = read();
        mp[k].push_back(make_pair(n, i));
    }
    for(auto u : mp){solve(u.first,u.second);}
    for(int i = 1;i <= T;i++)puts(ans[i] ? "YES" : "NO");
}
};
bool edmemory;

signed main(){
    auto begintime = clock();
    Call_me_Eric::main();
    auto endtime = clock();
    cerr << 1.0 * (endtime - begintime) / CLOCKS_PER_SEC << " sec cost.\n";
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << "Mib cost.\n";
    return 0;
}
/*
35
41 236447
7 1533
128 68191
1188 267623
1 1358
3 1533
259 68191
6 12727
31 267623
215 55981
648 267623
368 68191
178 236447
470 236447
11 1533
148 68191
2 1358
170 178303
890 267623
201 236447
2 1358
136 48887
236 48887
3 55981
1 1358
379 267623
54 68191
10 1533
414 267623
6 12727
212 68191
202 55981
601 296141
134 68191
5 1358
*/