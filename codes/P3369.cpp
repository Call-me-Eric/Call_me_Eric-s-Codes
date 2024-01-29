#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
struct balanced_tree{
    typedef long long ll;
    __gnu_pbds::tree<ll,__gnu_pbds::null_type,std::less<ll>,__gnu_pbds::rb_tree_tag
    ,__gnu_pbds::tree_order_statistics_node_update>d;
    ll opts;const ll shift = 20;
    void insert(int y){ll x = y;d.insert((x << shift) + opts);opts++;}
    void erase(int y){ll x = y;d.erase(d.lower_bound(x << shift));}
    int rank(int y){ll x = y;int ans = d.order_of_key(x << shift) + 1;return ans;}
    int pos(int y){ll x = y;int ans = (*d.find_by_order(x - 1)) >> shift;return ans;}
    int pre(int y){ll x = y;int ans = (*--d.lower_bound(x << shift)) >> shift;return ans;}
    int suf(int y){ll x = y;int ans = (*d.lower_bound((x + 1) << shift)) >> shift;return ans;}
}tree;
int n, m;
signed main(){
    n = read();m = read();
    for(int i = 1;i <= n;i++)tree.insert(read());
    int lastans = 0, ans = 0, opt, u;
    for(int i = 1;i <= m;i++){
        opt = read(); u = read() ^ lastans;
        if(opt == 1){tree.insert(u);}
        if(opt == 2){tree.erase(u);}
        if(opt == 3){lastans = tree.rank(u);}
        if(opt == 4){lastans = tree.pos(u);}
        if(opt == 5){lastans = tree.pre(u);}
        if(opt == 6){lastans = tree.suf(u);}
        if(opt != 1 && opt != 2)ans ^= lastans;
    }
    printf("%d\n",ans);
    return 0;
}