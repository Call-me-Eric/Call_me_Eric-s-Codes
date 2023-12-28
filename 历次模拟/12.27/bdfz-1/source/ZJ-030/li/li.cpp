#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(j);i<=(k);i++)
#define per(i,j,k) for (int i=(j);i>=(k);i--)
#define pb push_back
#define ll long long
int n,m,s,sum;
const int N=2e5+5;
int d[N];
vector<int>t[N];
bool vis[N];
ll ans;
void dfs(int x)
{
    vis[x]=1,sum++,ans+=sum;
    for (int i:t[x])
    {
        if (vis[i]) continue;
        dfs(i);
    }
}

int main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    rep(i,1,m)
    {
        int x,y;
        cin >> x >> y;
        t[x].pb(y),t[y].pb(x);
        d[x]++,d[y]++;
    }
    rep(i,1,n)
    {
        if (d[i]>3)
        {
            cout << -1;
            return 0;
        }
        if (d[i]==3)
        {
            vis[i]=1;
            for (int j:t[i])
            {
                vis[j]=1;
                if (d[j]>1)
                {
                    cout << -1;
                    return 0;
                }
            }
            s+=3;
        }
    }
    rep(i,1,n)
    {
        if (vis[i]) continue;
        if (d[i]==1) 
        {
            sum=0;
            dfs(i);
        }
        else if (d[i]==0)
        {
            ans++;
            vis[i]=1;
            continue;
        }
    }
    rep(i,1,n)
    {
        if (vis[i]) continue;
        s++;
    }
    if (s>0)
    {
        cout << "1 " << s;
        return 0;
    }
    else
    {
        cout << "0 " << ans;
    }
    return 0;
}