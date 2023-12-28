#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,m;
int mx,mn,cnt,cur;
ll ans;
bool vis[200005];
vector<int> adj[200005];

inline void dfs(int u)
{
    vis[u]=1;
    cur++;
    if(mn<adj[u].size())
        mn=adj[u].size(),cnt=0;
    if(mn==adj[u].size())
        cnt++;

    for(int v:adj[u])
    {
        if(!vis[v])
            dfs(v);
    }
}

int main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;

    while(m--)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            mn=cnt=cur=0;
            dfs(i);
            if(mn>3||(mn==3&&cur!=4))
            {
                cout<<"-1\n";
                return 0;
            }
            if(mn==3)
            {
                if(mx<1)
                    mx=1,ans=0;
                ans+=3;
            }
            else if(mn==2&&cnt==cur)
            {
                if(mx<1)
                    mx=1,ans=0;
                ans+=cur;
            }
            else
            {
                if(mx<1)
                    ans+=1LL*cur*(cur+1)/2;
            }
        }
    }

    cout<<mx<<' '<<ans<<'\n';

    return 0;
}
