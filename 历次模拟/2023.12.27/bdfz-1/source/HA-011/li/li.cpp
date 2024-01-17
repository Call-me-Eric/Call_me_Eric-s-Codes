#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+7;
int deg[N];
int n,m;
struct edge
{
    int y,next;
}e[2*N];
int link[N],t=0,fa[N];
int getf(int x)
{
    if(x==fa[x])return x;
    return fa[x]=getf(fa[x]);
}
void add(int x,int y)
{
    fa[getf(x)]=getf(y);
    e[++t].y=y;
    deg[x]++;
    e[t].next=link[x];
    link[x]=t;
}
int ecnt[N],pcnt[N],u[N],v[N];
typedef long long LL;
LL calc(int len)
{
    return 1ll*len*(len+1)/2ll;
}
int d3cnt[N];
int main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        u[i]=x;v[i]=y;
        add(x,y);
        add(y,x);
    }
    int mx=0;
    for(int i=1;i<=n;i++)mx=max(mx,deg[i]);
    if(mx>3)
    {
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=n;i++)pcnt[getf(i)]++;
    for(int i=1;i<=m;i++)ecnt[getf(u[i])]++;
    for(int i=1;i<=n;i++)if(deg[i]==3)d3cnt[getf(i)]++;
    LL S=0,E=0;
    for(int i=1;i<=n;i++)if(getf(i)==i)
    {
        if(d3cnt[i]>1)
        {
            cout<<-1;
            return 0;
        }
        if(d3cnt[i]==1)
        {
            if(ecnt[i]!=3)
            {
                cout<<-1;
                return 0;
            }
            S+=3;
            continue;
        }
        if(ecnt[i]==pcnt[i])S+=pcnt[i];
        else  E+=calc(pcnt[i]);
    }
    if(S)
    {
        cout<<1<<' '<<S;
        return 0;
    }
    cout<<0<<' '<<E;
    return 0;
}
