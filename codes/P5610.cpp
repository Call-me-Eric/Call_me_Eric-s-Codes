#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x =0  , f =1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;

int n, m;
int a[maxn];
struct BIT{
    int c[maxn << 2];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] += add;}
    int query(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
}tree;

vector<int> st[maxn];
typedef vector<int>::iterator vit;
vector<vit> t;

signed main(){
    n = read(); m = read();int opt, l, r, w;
    for(int i = 1;i <= n;i++){
        a[i] = read(); tree.upd(i,a[i]);
        for(int j = 1, len = sqrt(a[i]);j <= len;j++){
            if(a[i] % j == 0){
                st[j].push_back(i);
                if(j * j != a[i]) st[a[i] / j].push_back(i);
            }
        }
    }
    int lstans = 0;
    for(int i = 1;i <= m;i++){
    // cerr << "i = " << i << endl;
        opt = read(); l = read() ^ lstans; r = read() ^ lstans;
        if(opt == 2){printf("%lld\n",lstans = (tree.query(r) - tree.query(l - 1)));}
        else {
            
            w = read() ^ lstans;t.clear();
            if(w == 1 || st[w].empty())continue;
            vit lit = lower_bound(st[w].begin(),st[w].end(),l),
                rit = upper_bound(st[w].begin(),st[w].end(),r);
            if(lit == st[w].end())continue;
            for(vit it = lit;it != rit;it++){
                if(a[*it] % w)continue;
                tree.upd(*it,-a[*it] + a[*it] / w);
                a[*it] /= w;
                if(a[*it] % w)t.push_back(it);
            }
            if(!t.empty()) for(int j = t.size() - 1;j + 1;j--)st[w].erase(t[j]);
        }
        // for(int j = 1;j <= n;j++)printf("%d ",tree.query(j) - tree.query(j - 1));
        // puts("");
    }
    return 0;
}