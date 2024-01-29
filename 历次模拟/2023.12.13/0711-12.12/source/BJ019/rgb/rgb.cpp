#include<bits/stdc++.h>
#define For(i,l,r) for(register int i=(l);i<=(r);++i)
#define For_down(i,r,l) for(register int i=(r);i>=(l);--i)
using namespace std;
constexpr int n_MAX=250+5,m_MAX=100000+5;
struct Disjoint_Set
{
    int Fa[n_MAX];
    void init(const int n)
    {
        iota(Fa+1,Fa+n+1,1);
    }
    int find(const int u)
    {
        if(Fa[u]==u) return u;
        Fa[u]=find(Fa[u]);
        return Fa[u];
    }
    bool same(const int u,const int v)
    {
        return (find(u)==find(v));
    }
    bool unite(int u,int v)
    {
        u=find(u),v=find(v);
        if(u==v) return false;
        Fa[u]=v;
        return true;
    }
};
Disjoint_Set D[8],E;
int s[m_MAX],t[m_MAX],c[m_MAX],S[8],V[8];
bool check()
{
    For(i,0,7) if(V[i]<S[i]) return false;
    return true;
}
bool check(const int u,const int v,const int c)
{
    For(i,0,7)
    {
        const int new_V=(V[i]-D[i].same(u,v));
        const int new_S=(S[i]-((i>>c)&1));
        if(new_V<new_S) return false;
    }
    return true;
}
void merge(const int u,const int v,const int c)
{
    For(i,0,7) V[i]-=(!D[i].unite(u,v));
    For(i,0,7) if(i&(1<<c)) --S[i];
}
int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int r,g,b,m; cin>>r>>g>>b>>m,S[1]=r,S[2]=g,S[4]=b;
    const int n=(r+g+b+1);
    For(i,0,7) D[i].init(n);
    E.init(n);
    For(i,1,7) S[i]=(S[i&(-i)]+S[i^(i&(-i))]);
    For(i,1,m)
    {
        cin>>s[i]>>t[i];
        char cl; cin>>cl;
        if(cl=='g') c[i]=1;
        if(cl=='b') c[i]=2;
        For(j,0,7) if(j&(1<<c[i])) V[j]+=D[j].unite(s[i],t[i]);
    }
    if(!check()){cout<<"NO\n";return 0;}
    cout<<"YES\n";
    For(i,1,m)
    {
        if(E.same(s[i],t[i])) cout<<'0';
        else if(check(s[i],t[i],c[i])) merge(s[i],t[i],c[i]),E.unite(s[i],t[i]),cout<<'1';
        else cout<<'0';
    }
    cout<<'\n'; return 0;
}