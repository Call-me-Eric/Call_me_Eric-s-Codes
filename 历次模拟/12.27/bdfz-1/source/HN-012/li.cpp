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
vi e[N];

using Lim=pair<int,i64>;

Lim operator+ (Lim a,Lim b){
    if(a.fi==b.fi) return {a.fi,a.se+b.se};
    else return max(a,b);
}

int vis[N];
void dfs(int x,vi &vec){
    vec.pb(x),vis[x]=1;
    for(auto y:e[x])
        if(!vis[y]) dfs(y,vec);
}

Lim detect(int st){
    vi v;dfs(st,v);
    int cv=v.size(),ce=0,mx=0;
    for(auto x:v){
        int sz=e[x].size();
        ce+=sz,mx=max(mx,sz);
    }
    ce/=2;
    if(ce>cv) return {2,0};
    else if(ce==cv) return mx==2?(Lim){1,cv}:(Lim){2,0};
    else{
        assert(ce==cv-1);
        if(mx<=2) return {0,(i64)cv*(cv+1)/2};
        else if(mx==cv-1) return {1,ce};
        else return {2,0};
    }
}

int main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    n=rdi(),m=rdi();
    for(int i=1;i<=m;i++){
        int x=rdi(),y=rdi();
        e[x].pb(y),e[y].pb(x);
    }
    Lim res{0,0};
    for(int i=1;i<=n;i++)
        if(!vis[i]) res=res+detect(i);
    if(res.fi>1) puts("-1");
    else cout<<res.fi<<' '<<res.se<<'\n';
    return 0;
}
