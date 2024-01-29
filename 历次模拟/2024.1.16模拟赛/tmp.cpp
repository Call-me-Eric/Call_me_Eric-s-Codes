#include<bits/stdc++.h>
using namespace std;
namespace genshin{

const int maxn = 100 + 10;
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
map<pair<int,int> ,int> mp;
void main(){

    freopen("genshin.in","w",stdout);
    srand(time(0));mt19937 rnd(rand());
    int n = rnd() % 100 + 1;n = 100;
    printf("%d %d\n",n,n);
    for(int i = 1;i <= n;i++)fa[i] = i;
    for(int i = 1;i < n;i++){
        int u = 1, v = 1;
        while(getf(u) == getf(v) || u == v){
            u = rnd() % n + 1, v = rnd() % n + 1;
        }
        fa[getf(u)] = getf(v);
        printf("%d %d %d\n",u, v,rnd() % 100 + 1);
        mp[make_pair(u , v)] = 1;
    }
    int u = 1, v = 1;
    while(mp[make_pair(u, v)] || u == v){
        u = rnd() % n + 1, v = rnd() % n + 1;
    }
    printf("%d %d %d\n",u , v,rnd() % 100 + 1);
}
};
namespace impact{
    
};
signed main(){
    return 0;
}