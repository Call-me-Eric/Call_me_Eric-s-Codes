#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#define let const auto
#define rep(name,beg,end) for(decltype(beg + end) name = beg,name##_end = end;name <= name##_end;name++)
#define per(name,beg,end) for(decltype(beg + end) name = beg,name##_end = end;name >= name##_end;name--)
#define repn(lim) for(decltype(lim + 0) REPN_NOW = 1,REPN_LIM = lim;REPN_NOW <= REPN_LIM;REPN_NOW++)
#define debug(...) std::fprintf(stderr,__VA_ARGS__)
using ci = const int;
constexpr int V = 1e7 + 100;

bool vis[V + 1];
std::vector<int> pri;
void sieve(){
    vis[0] = 1;
    vis[1] = 1;
    rep(i,2,V){
        if(!vis[i])pri.push_back(i);
        for(let p : pri){
            if(i * p > V)break;
            vis[i * p] = 1;
            if(i % p == 0)break;
        }
    }
}

bool nprime(ci x){
    if(x <= V)return vis[x];
    for(let p : pri){
        if(p * p > x)break;
        if(x % p == 0)return true;
    }
    return false;
}

std::vector<int> vec[11];
std::vector<int> stk;
bool chk(){
    if(stk.empty())return true; 
    ci len = stk.size();
    for(let s : vec[len - 1]){
        int now = 0;
        for(int i = 0;i < len;i++)
            if((s >> i) & 1)
                now = now * 10 + stk[i];
        now = now * 10 + stk.back();
        if(!nprime(now))return false;
    }
    return true;
}

std::vector<int> ans;
void dfs(ci step,const int s = 0){
    if(!chk())return;
    ans.push_back(s);
    for(let v : {0,1,4,6,8,9}){
        if(!step && !v)continue;
        if(10ll * s + v > 1000000000)continue;

        stk.push_back(v);
        dfs(step + 1,s * 10 + v);
        stk.pop_back();
    }
}

int main(){
    std::freopen("prime.in","r",stdin);
    std::freopen("prime.out","w",stdout);
    sieve();
    rep(len,1,10){
        rep(s,1,(1 << len) - 1)
            vec[len].push_back(s);
        std::sort(vec[len].begin(),vec[len].end(),[](ci x,ci y){
            return __builtin_popcount(x) < __builtin_popcount(y);
        });
    }

    dfs(0);

    std::sort(ans.begin(),ans.end());

    int t = 0; std::scanf("%d",&t);
    repn(t){
        int L,R; std::scanf("%d %d",&L,&R);
        ci x = std::upper_bound(ans.begin(),ans.end(),R) - std::lower_bound(ans.begin(),ans.end(),L);
        std::printf("%d\n",x);
    }
    return 0;
}