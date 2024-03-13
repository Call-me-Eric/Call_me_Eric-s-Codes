#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 4e5 + 10;
int n = 5e3 , m = n - 1;
vector<pair<int,int> > edg;
void main(){
    srand(time(0));mt19937 rnd(rand());
    printf("%d %d\n",n,m);
    for(int i = 2;i <= n;i++){
        // int u = i, v = rnd() % (i - 1) + 1;
        int u = i - 1, v = i;
        edg.push_back(make_pair(u, v));
    }
    for(int i = n;i <= m;i++){
        int u = rnd() % (n) + 1, v = rnd() % (n) + 1;
        v = (v + (u == v)) % n + 1;
        edg.push_back(make_pair(u, v));
    }
    random_shuffle(edg.begin(),edg.end());
    for(auto i : edg){
        printf("%d %d\n",i.first,i.second);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("alphadog.in","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}