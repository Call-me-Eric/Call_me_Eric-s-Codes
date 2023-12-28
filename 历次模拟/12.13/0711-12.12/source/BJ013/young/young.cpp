#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mod=998244353;

int n,m,q,k;
vector<int> a,b;
map<vector<int>,ll> mp[25];

inline int dfs(int p,vector<int> u)
{
    if(mp[p][u])
        return mp[p][u]-1;

    if(p==k)
        return 0;

    vector<int> v=u;
    for(int i=0;i<v.size();i++)
    {
        if(i==0||v[i-1]>v[i])
        {
            v[i]++;
            mp[p][u]=(mp[p][u]+dfs(p+1,v))%mod;
            v[i]--;
        }
    }

    v.push_back(1);
    mp[p][u]=(mp[p][u]+dfs(p+1,v))%mod;
    v.pop_back();

    for(int i=0;i+1<v.size();i++)
    {
        if(v[i]>v[i+1])
        {
            v[i]--;
            mp[p][u]=(mp[p][u]+dfs(p+1,v))%mod;
            v[i]++;
        }
    }

    if(v.size())
    {
        if(v[v.size()-1]>1)
        {
            v[v.size()-1]--;
            mp[p][u]=(mp[p][u]+dfs(p+1,v))%mod;
            v[v.size()-1]++;
        }
        else
        {
            v.pop_back();
            mp[p][u]=(mp[p][u]+dfs(p+1,v))%mod;
            v.push_back(1);
        }
    }

    mp[p][u]++;
    return mp[p][u]-1;
}

int main()
{
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>k;
        a.push_back(k);
    }

    cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>k;
        b.push_back(k);
    }

    cin>>q;

    while(q--)
    {
        for(int i=0;i<=20;i++)
            mp[i].clear();
        cin>>k;

        mp[k][b]=2;
        cout<<dfs(0,a)<<'\n';
    }

    return 0;
}
