#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,m,k,ans;
int adj[10],tt[10],cur;
int cnt[1000005],lt[1000005];
bool vis[10],tp[1000005];

inline void change(int res,int bg,int siz)
{
    for(int i=1;i<=cur;i++)
        tt[i]=0;

    while(bg)
    {
        tt[lt[bg]]++;
        bg-=adj[lt[bg]];
    }

    int u=1;

    for(int i=1;i<=n;i++)
        tp[i]=0;

    for(int i=1;i<=cur;i++)
    {
        if(!tt[i])
            continue;

        int v=u,sk=n/adj[i];

        for(int j=1;j<=tt[i];j++)
        {
            for(int x=0;x<adj[i];x++)
                tp[v+x*sk]=1;
            v+=n/res;
        }

        u++;
    }

    while(siz--)
    {
        for(int i=0;i<res;i++)
            tp[u+n/res*i]=1;
        u++;
    }
}

inline void sol()
{
    m=0;
    int res=1;
    for(int i=1;i<=cur;i++)
    {
        if(vis[i])
            res*=adj[i],m++;
    }

    int sum=n/res-m;

    if(res==1||sum<0)
        return;

    for(int i=1;i<=n;i++)
        cnt[i]=-1;

    for(int i=1;i<=cur;i++)
    {
        if(!vis[i])
            continue;

        int f=res/adj[i]-1;
        if(!f)
            continue;

        for(int j=adj[i];j<=n;j++)
        {
            if(cnt[j-adj[i]]!=-1)
            {
                if(cnt[j]==-1||cnt[j]>cnt[j-adj[i]]+1)
                {
                    cnt[j]=cnt[j-adj[i]]+1;
                    lt[j]=i;
                }
            }
        }

        for(int j=adj[i];j<=n;j++)
        {
            if(cnt[j]!=-1)
            {
                if(cnt[j]>f)
                    cnt[j]=-1;
                else
                    cnt[j]=0;
            }
        }
    }

    int mx=0,pos=0;

    for(int i=0;i<=k;i++)
    {
        if(cnt[i]!=-1)
        {
            int tmp=i+min(sum,(k-i)/res)*res;
            if(mx<tmp)
                mx=tmp,pos=i;
        }
    }

    if(ans<mx)
    {
        ans=mx;
        change(res,pos,min(sum,(k-pos)/res));
    }
}

inline void dfs(int u)
{
    if(u==cur+1)
    {
        sol();
        return;
    }

    vis[u]=1;
    dfs(u+1);
    vis[u]=0;
    dfs(u+1);
}

int main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>k;
    m=n;

    for(int i=2;i<=n;i++)
    {
        if(m%i==0)
        {
            adj[++cur]=i;
            while(m%i==0)
                m/=i;
        }
    }

    if(n==k)
    {
        for(int i=1;i<=n;i++)
            cout<<1;
        cout<<'\n';

        return 0;
    }

    dfs(1);

    for(int i=1;i<=n;i++)
        cout<<tp[i];
    cout<<'\n';

    return 0;
}
