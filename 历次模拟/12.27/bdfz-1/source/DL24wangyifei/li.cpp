#include<bits/stdc++.h>
#define il inline
using namespace std;
il int read()
{
    int xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9')
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
const int N=2e5+5;
int n,m,a[N],b[N];
struct edge{int v,id;};
vector<edge> e[N];
typedef pair<int,int> pir;
vector<pir> t;
il int trans()
{
    for(int u=1;u<=n;u++)
    {
        for(auto [v1,id1]:e[u])
            for(auto [v2,id2]:e[u]) t.push_back(pir(id1,id2));
    }
    for(auto &[u,v]:t) if(u>v) swap(u,v);
    sort(t.begin(),t.end()),t.erase(unique(t.begin(),t.end()),t.end());
    int cnt=0;
    for(int i=1;i<=n;i++) e[i].clear();
    for(auto [u,v]:t) if(u!=v)
    {
        cnt++;
        e[u].push_back(edge{v,cnt}),e[v].push_back(edge{u,cnt});
    }
    n=m,m=cnt;
    return n;
}
int main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    n=read(),m=read();
    for(int i=1;i<=m;i++) 
    {
        int u=read(),v=read();
        e[u].push_back(edge{v,i}),e[v].push_back(edge{u,i});
    }
    a[0]=n; int mx=100;
    for(int i=1;i<=mx;i++) 
    {
        a[i]=trans();
        if(a[i]>5000) {mx=i;break;} 
        // cout<<i<<" "<<a[i]<<endl;
    }
    for(int i=1;i<=mx;i++) a[i]+=a[i-1];
    for(int s=0;s<=mx;s++)
    {
        int len=0;
        for(int i=1;i<=mx;i++)
        {
            b[i]=round(1.0*a[i]/pow(i,s));
            if(b[i]==b[i-1]) len++;
            else len=0;
            if(len>5) {printf("%d %d\n",s,b[i]);return 0;}
        }
    } 
    printf("-1\n");
    return 0;
}