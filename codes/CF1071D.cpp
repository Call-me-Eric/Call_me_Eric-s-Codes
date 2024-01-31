#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10, maxm = 610;
int prime[maxn], d[maxn], tot;
bool book[maxn];
vector<int> vec[maxn];
map<vector<int>,vector<int> > mp;
signed main(){
    for(int i = 2;i < maxn;i++){
        if(!book[i]){prime[++tot] = i;d[i] = i;}
        for(int j = 1;j <= tot && prime[j] * i < maxn;j++){
            book[i * prime[j]] = 1;
            d[i * prime[j]] = prime[j];
            if(i % prime[j] == 0)break;
        }
    }
    for(int i = 2;i < maxn;i++){
        vec[i] = vec[i / d[i]];
        if(d[i] == d[i / d[i]])vec[i].back()++;
        else vec[i].push_back(2);
    }
    for(int i = 2;i < maxn;i++)sort(vec[i].begin(),vec[i].end(),greater<int>());
    
    auto &v = mp[vec[1]]; v.resize(maxm);v[1] = 0;
    for(int i = 2;i < maxm;i++)v[i] = v[i / d[i]] + d[i] - 1;
    
    for(int i = 2;i < maxn;i++){
        if(!mp.count(vec[i])){
            auto lst = vec[i];lst.pop_back();
            auto &v = mp[vec[i]], &u = mp[lst];
            v.resize(maxm);
            for(int x = 1;x < maxm;x++)v[x] = u[x] + vec[i].back() - 1;
            for(int x = 1;x < maxm;x++)
                for(int y = 2;x * y < maxm;y++)
                    v[x * y] = min(v[x * y],min(u[x] + abs(vec[i].back() - y),v[x] + y - 1));
        }
    }
    for(int i = read();i;i--){
        int u = read(), v = read();
        int ans = 0x3f3f3f3f;
        auto &x = mp[vec[u]], &y = mp[vec[v]];
        for(int j = 1;j < maxm;j++)
            ans = min(ans,x[j] + y[j]);
        printf("%d\n",ans);
    }
    return 0;
}