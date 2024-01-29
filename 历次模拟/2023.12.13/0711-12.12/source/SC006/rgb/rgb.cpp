#include <cstdio>
#include <cassert>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <cstdlib>
#define let const auto
#define rep(name,beg,end) for(decltype(beg + end) name = beg,name##_end = end;name <= name##_end;name++)
#define per(name,beg,end) for(decltype(beg + end) name = beg,name##_end = end;name >= name##_end;name--)
#define repn(lim) for(decltype(lim + 0) REPN_NOW = 1,REPN_LIM = lim;REPN_NOW <= REPN_LIM;REPN_NOW++)
#define debug(...) std::fprintf(stderr,__VA_ARGS__)
using ci = const int;
constexpr int maxn = 922;

[[noreturn]] void nosol(){
    std::puts("NO");
    std::exit(0);
}

int lim[3],n,m;
namespace dsu{
    int f[maxn];
    int find(ci x){return x == f[x] ? x : f[x] = find(f[x]);}
    void merge(int x,int y){
        x = find(x);
        y = find(y);
        f[x] = y;
    }
    bool same(ci x,ci y){
        return find(x) == find(y);
    }
    void init(){
        rep(i,1,n)f[i] = i;
    }
}
using namespace dsu;

struct Edge{int u,v,w,id;};
std::vector<Edge> edges;
int eval(){
    int now[3]{};
    init();
    for(let &e : edges){
        if(same(e.u,e.v))continue;
        if(now[e.w] == lim[e.w])continue;
        merge(e.u,e.v);
        now[e.w]++;
    } 
    return n - 1 - now[0] - now[1] - now[2];
}

void print(){
    int now[3]{};
    std::vector<int> ans(m);
    init();
    for(let &e : edges){
        if(same(e.u,e.v))continue;
        if(now[e.w] == lim[e.w])continue;
        merge(e.u,e.v);
        ans[e.id] = 1;
    } 
    std::puts("YES");
    for(let x : ans)std::printf("%d",x);
    std::puts("");
}

using Clock = std::chrono::steady_clock;
std::mt19937 rng(229);
int main(){
    std::freopen("rgb.in","r",stdin);
    std::freopen("rgb.out","w",stdout);
    
    let st = Clock::now();

    std::scanf("%d %d %d %d",lim + 0,lim + 1,lim + 2,&m);
    n = lim[0] + lim[1] + lim[2] + 1;
    
    rep(id,0,m - 1){
        int u,v,w = -1;
        char s[4];
        std::scanf("%d %d %s",&u,&v,s);
        if(s[0] == 'r')w = 0;
        if(s[0] == 'g')w = 1;
        if(s[0] == 'b')w = 2;
        edges.push_back({u,v,w,id});
    }

    std::uniform_int_distribution<int> gen(0,m - 1);

    int now = eval();
    while(now){
        if(std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - st).count() >= 1900)nosol();
        let u = gen(rng);
        let v = gen(rng);

        std::swap(edges[u],edges[v]);

        let nxt = eval();
        if(nxt < now)now = nxt;
        else if(now == nxt && rng() % 2 == 0)now = nxt;
        else{
            std::swap(edges[u],edges[v]);
        }
    }
    print();
    return 0;
}