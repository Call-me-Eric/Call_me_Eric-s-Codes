#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int maxn=1e6+5;
int m,n,u,v;
int a[maxn],s[maxn];
vector<int> g[maxn];
vector<pii> e;
void work()
{
    vector<pii> now;
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1;i<=e.size();i++) g[e[i-1].fi].push_back(i),g[e[i-1].se].push_back(i);
    for(int i=1;i<=n;i++)
        for(int j=0;j<g[i].size();j++)
            for(int k=j+1;k<g[i].size();k++)
            {
                now.push_back(mp(g[i][j],g[i][k]));
                if(now.size()>=maxn) printf("-1\n"),exit(0);
            }
    n=e.size(),swap(e,now);
}
int main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    scanf("%d%d",&n,&m);
    while(m--) scanf("%d%d",&u,&v),e.push_back(mp(u,v));
    a[0]=s[0]=n;
    for(int i=1;i<=100;i++)
    {
        work(),a[i]=n,s[i]=s[i-1]+n;
        if(!n) printf("0 %d\n",s[i]),exit(0);
        if(i>=50&&a[i]==a[i-1]) printf("1 %d\n",a[i]),exit(0);
    }
    printf("-1\n");
    return 0;
}