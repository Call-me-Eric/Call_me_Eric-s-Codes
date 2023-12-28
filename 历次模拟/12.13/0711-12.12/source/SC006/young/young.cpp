#include <cstdio>
#include <cassert>
#include <array>
#include <map>
#include <algorithm>
#define let const auto
#define rep(name,beg,end) for(decltype(beg + end) name = beg,name##_end = end;name <= name##_end;name++)
#define per(name,beg,end) for(decltype(beg + end) name = beg,name##_end = end;name >= name##_end;name--)
#define repn(lim) for(decltype(lim + 0) REPN_NOW = 1,REPN_LIM = lim;REPN_NOW <= REPN_LIM;REPN_NOW++)
#define debug(...) std::fprintf(stderr,__VA_ARGS__)
using ci = const int;
constexpr int L = 10,N = 42,mod = 998244353;
using Young = std::array<int,N>;

void fix(int &x){
    x += (x >> 31) & mod;
}

std::map<Young,int> v[2][L + 1];
template <int opt>
void work(const Young s){
    v[opt][0][s] = 1;
    rep(i,0,L - 1)
        for(let &it : v[opt][i]){
            auto now = it.first;
            
            rep(p,0,N - 1){
                for(let d : {-1,1})
                    if(now[p] + d >= 0){
                        now[p] += d;
                        
                        bool flg = true;
                        rep(i,0,N - 2)
                            flg = flg && now[i] >= now[i + 1];

                        if(flg)
                            fix(v[opt][i + 1][now] += it.second - mod);
    
                        now[p] -= d;
                    }
                if(!now[p])break;
            }
        }

}

int n,m;
Young A,B;
int main(){
    std::freopen("young.in","r",stdin);
    std::freopen("young.out","w",stdout);
    std::scanf("%d",&n);
    rep(i,0,n - 1)std::scanf("%d",&A[i]);
    std::scanf("%d",&m);
    rep(i,0,m - 1)std::scanf("%d",&B[i]);
    
    work<0>(A);
    work<1>(B);

    int q; std::scanf("%d",&q);
    repn(q){
        int k; std::scanf("%d",&k);
        auto &ma = v[0][k / 2];
        auto &mb = v[1][k - k / 2];

        int ans = 0;
        for(let &it : ma)
            fix(ans += it.second * mb[it.first] % mod - mod);
        std::printf("%d\n",ans);
    }
    return 0;
}