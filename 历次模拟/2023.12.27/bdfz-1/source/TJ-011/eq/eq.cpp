#include<bits/stdc++.h>

using i64 = int64_t;

namespace shaber{
    constexpr int mod = 998244353;
    int mul(int x, int y){
        return (i64)x * y % mod;
    }
    int qpow(int a, int b, int r = 1){
        for(; b; b >>= 1, a = mul(a, a)){
            (b & 1) ? r = mul(r, a) : r;
        }
        return r;
    }
    void fraud(){
        std::ifstream fin("eq.in");
        std::ofstream fout("eq.out");
        int n, q;
        fin >> n >> q;
        int a, b;
        fin >> a >> b;
        auto get = [&](){
            if(a == 0){
                fout << (b == 0 ? "Many\n" : "No\n");
            }
            else{
                fout << qpow(a, mod - 2, b) << '\n';
            }
        };
        get();
        for(int i = 0, z; i < q; ++i){
            fin >> z >> a >> b;
            get();
        }
    }
}

int main(){
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    shaber::fraud();
    return 0;
}
/*
4 6 1
0 1
0 2
0 3
1 2
1 3
2 3

5 6 4
0 1
0 2
1 2
2 3
3 4
4 2

5 4 6
0 1
0 2
0 3
3 4

如果任何一个点的度数大于等于3 则 s 不存在

否则若存在环 那么 s = 1 极限为 所有环长之和

否则 s = 0 极限为 所有链的 n（n-1）/2 之和

特殊情况

三叶草会在一回合之后衰变成三元环
*/