#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
ull n, ans, tmp;
const ull prime[20] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
void dfs(ull step,ull pow,ull most,ull took,ull m){
    ull res = m * (took + 1);
    if(res > tmp || (res == tmp && pow < ans)){tmp = res;ans = pow;}
    if(took + 1 <= most && pow * prime[step] <= n){dfs(step,pow * prime[step],most,took + 1,m);}
    if(pow * prime[step + 1] <= n){
        dfs(step + 1,pow * prime[step + 1],most,1,m * (took + 1));
    }
}
signed main(){
    cin >> n;
    dfs(0,1,53,0,1);
    cout << ans;
    return 0;
}
