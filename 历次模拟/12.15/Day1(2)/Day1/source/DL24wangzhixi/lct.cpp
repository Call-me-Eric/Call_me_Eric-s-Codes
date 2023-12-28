#include <bits/stdc++.h>
using namespace std;

const int maxn=5e5+10;

int n,Q,ans[maxn];
vector<int>e[maxn];
vector<pair<int,int> >qbuc[maxn];

int c[maxn];
inline int lowbit(int x){return x&(-x);}
inline void add(int x,int y){for(;x<maxn;x+=lowbit(x))c[x]+=y;}
inline int query(int x){int res=0;for(;x;x-=lowbit(x))res+=c[x];return res;}
inline int qsum(int l,int r){return query(r)-query(l-1);}

inline void solve()
{
    cin>>n>>Q;
    for(int i=1,x,y;i<n;i++)
        cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
    for(int i=1,l,r;i<=Q;i++)
        cin>>l>>r,qbuc[r].emplace_back(l,i);
    for(int i=1;i<=n;i++)
    {
        for(auto y:e[i]) if(y<i) add(y,1);
        for(auto [l,id]:qbuc[i])
            ans[id]=i-l+1-qsum(l,i);
    }
    for(int i=1;i<=Q;i++)
        cout<<ans[i]<<'\n';
}
signed main()
{
    freopen("lct.in","r",stdin);
    freopen("lct.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();
}
