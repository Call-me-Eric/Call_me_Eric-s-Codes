#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
using vi=vector<int>;
using pii=pair<int,int>;

template<typename T>
T read(){
    T x=0,f=0;char c=getchar();
    while(!isdigit(c)) f|=(c=='-'),c=getchar();
    while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
    return f?-x:x;
}

#define rdi read<int>
#define rdi64 read<i64>
#define fi first
#define se second
#define pb push_back

const int N=2e5+10;

int n,m;

struct Graph{
    int v;
    vector<pii> e;
    void trans(){
        static vi id[N];
        for(int i=0;i<v;i++) id[i].clear();
        int sz=e.size();
        for(int i=0;i<sz;i++)
            id[e[i].fi].pb(i),id[e[i].se].pb(i);
        vector<pii> e1;
        for(int i=0;i<sz;i++){
            for(auto j:id[e[i].fi])
                if(i<j) e1.pb({i,j});
            for(auto j:id[e[i].se])
                if(i<j) e1.pb({i,j});
        }
        v=e.size(),e=e1;
    }
}g;

int main(){
    n=rdi(),m=rdi();
    g.v=n;
    for(int i=1;i<=m;i++){
        int x=rdi(),y=rdi();
        g.e.pb({x,y});
    }
    for(int i=0;i<=8;i++){
        cout<<g.v<<' '<<g.e.size()<<'\n';
        g.trans();
    }
    return 0;
}
