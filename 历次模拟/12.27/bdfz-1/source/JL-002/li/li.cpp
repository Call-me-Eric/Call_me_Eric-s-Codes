#include<bits/stdc++.h>
#define N 1500101
#define MAX 2001
using namespace std;
typedef long long ll;
typedef double db;
inline void read(ll &ret)
{
    ret=0;char c=getchar();bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,m,x,y,fr[N],ed[N],cfr[N],ced[N];
vector<pair<ll,ll>>v[N],g[N];
signed main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    read(n);
    read(m);
    for(int i=1;i<=m;i++)
    {
        read(x);
        read(y);
        fr[i]=x,ed[i]=y;
        v[x].push_back(make_pair(y,i));
        v[y].push_back(make_pair(x,i));
    }
    ll cnt=0;
    ll sum=n;
    bool flag=false;
    while(clock()*1.0/CLOCKS_PER_SEC<0.9)
    {
        cnt++;
     //   cerr<<n<<" "<<m<<endl;
        n=m;
        sum+=n;
        if(!n)
            break;
        for(int j=1;j<=n;j++)
            g[j].clear();
        m=0;
        for(int i=1;i<=n;i++)
        {
            for(auto x:v[fr[i]])
            {
                if(x.second>i)
                    g[i].push_back(make_pair(x.second,++m)),g[x.second].push_back(make_pair(i,m)),cfr[m]=i,ced[m]=x.second/*,cout<<m<<" "<<fr[i]<<" "<<i<<" "<<x.second<<endl*/;
            }
            for(auto x:v[ed[i]])
            {
                if(x.second>i)
                    g[i].push_back(make_pair(x.second,++m)),g[x.second].push_back(make_pair(i,m)),cfr[m]=i,ced[m]=x.second/*,cout<<m<<" "<<ed[i]<<" "<<i<<" "<<x.second<<endl*/;
            }
            if(m>1000000)
            {
                if(n==m)
                    printf("1 %lld\n",(ll)(sum*1.0/cnt+0.5));
                else
                {
                    if(m>n*(n-1)/2/2)
                        puts("-1");
                    else
                        printf("2 %lld\n",(ll)(sum*1.0/cnt/cnt+0.5));
                }
                exit(0);
            }
        }
        for(int j=1;j<=n;j++)
            v[j]=g[j];
        for(int j=1;j<=m;j++)
            fr[j]=cfr[j],ed[j]=ced[j];
    }
    if(!n)
        printf("0 %lld\n",sum);
    else if(n==m)
        printf("1 %lld\n",(ll)(sum*1.0/cnt+0.5));
    else
    {
        if(m>n*(n-1)/2/2)
            puts("-1");
        else
            printf("2 %lld\n",(ll)(sum*1.0/cnt/cnt+0.5));
    }
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<endl;
    exit(0);
}