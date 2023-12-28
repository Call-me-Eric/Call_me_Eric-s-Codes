#include<bits/stdc++.h>
using namespace std;
int n,m,p;
int f[400000];
int s[400000];
int c[400000];
long long ans;
vector<int>e[400000];
int check(int x)
{
    if(x==f[x])
    {
        return x;
    }
    return f[x]=check(f[x]);
}
int main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
    {
        if(e[i].size()>3)
        {
            printf("-1\n");
            return 0;
        }
        if(e[i].size()==3)
        {
            for(int j:e[i])
            {
                if(e[j].size()>1)
                {
                    printf("-1\n");
                    return 0;
                }
                e[j].clear();
            }
            e[i].clear();
            p=1;
            ans+=3;
        }
    }
    iota(f+1,f+n+1,1);
    fill(s+1,s+n+1,1);
    for(int i=1;i<=n;i++)
    {
        for(int j:e[i])
        {
            if(j>i)
            {
                if(check(i)==check(j))
                {
                    c[f[i]]=p=1;
                }
                else
                {
                    s[f[i]]+=s[f[j]];
                    f[f[j]]=f[i];
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(p&&c[i])
        {
            ans+=s[i];
        }
        if(!p&&f[i]==i)
        {
            ans+=(s[i]+1ll)*s[i]/2;
        }
    }
    printf("%d %lld\n",p,ans);
    return 0;
}