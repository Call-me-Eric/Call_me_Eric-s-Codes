#include<bits/stdc++.h>

using i64 = int64_t;
using f64 = double;
using cpx = std::complex<f64>;

namespace shaber{
    std::string solve_avar(int n, int k){
        for(int i = k; i > 1; --i){
            int g = std::__gcd(n, i);
            if(g != 1){
                int u = n / g, v = k / g;
                std::string ans;
                for(int i = 0; i < g; ++i){
                    for(int i = 0; i < v; ++i){
                        ans += '1';
                    }
                    for(int i = v; i < u; ++i){
                        ans += '0';
                    }
                }
                return ans;
            }
        }
        return std::string(n, '0');
    }
    void fraud(){
        std::ifstream fin("ur.in");
        std::ofstream fout("ur.out");
        int n, k;
        fin >> n >> k;
        fout << solve_avar(n, k);
    }
}

int main(){
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    shaber::fraud();
    return 0;
}