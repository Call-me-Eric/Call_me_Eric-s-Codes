#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll mod=998244353;

int n,q,id[705],bg[705];
ll x[1405][705],mat[705][705],ans[705][705];
bool vis[705],tp[3005][705];
vector<int> adj[3005];

inline ll fpow(ll a,ll b)
{
    ll res=1;

    while(b)
    {
        if(b&1)
            res=res*a%mod;

        a=a*a%mod;
        b>>=1;
    }

    return res;
}

inline int lc(int k){return k<<1;}

inline int rc(int k){return k<<1|1;}

inline void add(int k,int l,int r,int ql,int qr,int pos)
{
    if(ql<=l&&r<=qr)
    {
        adj[k].push_back(pos);
        return;
    }

    int mid=(l+r)>>1;

    if(ql<=mid)
        add(lc(k),l,mid,ql,qr,pos);
    if(mid<qr)
        add(rc(k),mid+1,r,ql,qr,pos);
}

inline void ins(int id)
{
    if(vis[n+1])
        return;

    for(int i=1;i<=n+1;i++)
        mat[n+1][i]=x[id][i];

    for(int i=1;i<=n;i++)
    {
        if(!mat[n+1][i])
            continue;

        if(!vis[i])
        {
            for(int j=i;j<=n+1;j++)
                mat[i][j]=mat[n+1][j];
            vis[i]=1;
            return;
        }

        ll a=mat[n+1][i],b=mat[i][i];
        for(int j=i;j<=n+1;j++)
            mat[n+1][j]=((mat[n+1][j]*b-mat[i][j]*a)%mod+mod)%mod;
    }

    if(mat[n+1][n+1])
        vis[n+1]=1;
    else
        vis[n+2]=1;
}

inline void sol()
{
    if(vis[n+1])
    {
        cout<<"No\n";
        return;
    }

    if(vis[n+2])
    {
        cout<<"Many\n";
        return;
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n+1;j++)
            ans[i][j]=mat[i][j];
    }

    for(int i=n;i;i--)
    {
        for(int j=i+1;j<=n;j++)
            ans[i][n+1]=((ans[i][n+1]-ans[i][j]*ans[j][n+1])%mod+mod)%mod;
        ans[i][n+1]=ans[i][n+1]*fpow(ans[i][i],mod-2)%mod;
    }

    for(int i=1;i<=n;i++)
        cout<<ans[i][n+1]<<' ';
    cout<<'\n';
}

inline void build(int k,int l,int r)
{
    for(int i=1;i<=n+2;i++)
        tp[k][i]=vis[i];

    for(int u:adj[k])
        ins(u);

    if(l==r)
    {
        sol();

        for(int i=1;i<=n+2;i++)
            vis[i]=tp[k][i];

        return;
    }

    int mid=(l+r)>>1;

    build(lc(k),l,mid);
    build(rc(k),mid+1,r);

    for(int i=1;i<=n+2;i++)
        vis[i]=tp[k][i];
}

int main()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;

    for(int i=1;i<=n;i++)
    {
        id[i]=i;
        for(int j=1;j<=n+1;j++)
            cin>>x[i][j];
    }

    for(int i=1;i<=q;i++)
    {
        int p;
        cin>>p;
        add(1,0,q,bg[p],i-1,id[p]);
        bg[p]=i,id[p]=n+i;
        for(int j=1;j<=n+1;j++)
            cin>>x[n+i][j];
    }

    for(int i=1;i<=n;i++)
        add(1,0,q,bg[i],q,id[i]);

    build(1,0,q);

    return 0;
}
