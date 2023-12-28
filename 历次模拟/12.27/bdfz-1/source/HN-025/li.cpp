#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
using ll=long long;
int n,m,g[N],f[N],h[N],sz[N];
vector<int>lk[N];
int gf(int x){
    return x==f[x]?x:f[x]=gf(f[x]);
}
void mg(int x,int y){
    if(x!=y)f[y]=x,sz[x]+=sz[y],h[x]|=h[y];
}
ll d1,d2;
bitset<N>vs;
void RET(){puts("-1"),exit(0);}
int main(){
    ios::sync_with_stdio(false);
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    int i,j,k,l,r,x,y;
    cin>>n>>m;
    for(i=1;i<=m;++i){
        cin>>x>>y;
        lk[x].push_back(y);
        lk[y].push_back(x);
        ++g[x],++g[y];
    }
    for(x=1;x<=n;++x){
        if(g[x]>3)RET();
        if(g[x]==3){
            for(int p:lk[x])
                if(g[p]>1)RET();
                else vs[p]=1;
            d2+=3,vs[x]=1;
        }if(!g[x])vs[x]=1,++d1;
    }
    for(x=1;x<=n;++x){
        f[x]=x,h[x]=(g[x]==1),sz[x]=1;
        for(int y:lk[x])if(y<x)mg(gf(x),gf(y));
    }
    for(l=1;l<=n;++l)
        if(!vs[x=gf(l)]){
            vs[x]=1;
            if(h[x])d1+=ll(sz[x]+1)*sz[x]/2;
            else d2+=sz[x];
        }
    if(d2)printf("1 %lld\n",d2);
    else printf("0 %lld\n",d1);
    return 0;
}