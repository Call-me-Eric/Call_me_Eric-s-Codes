#include<bits/stdc++.h>
#define gh() getchar()
#define re register
typedef long long ll;
using namespace std;
const int MAXN=201;
const int MAXM=5e3+1;
const int INF=1e9;
const double eps=1e-8;
template<class T>
inline void read(T &x)
{
    x=0;
    char ch=gh(),t=0;
    while(ch<'0'||ch>'9') t|=ch=='-',ch=gh();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=gh();
    if(t) x=-x;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1)
{
    read(x),read(x1...);
}
template<class T>
inline bool checkMax(T &x,T &y)
{
    return x<y?x=y,1:0;
}
template<class T>
inline bool checkMin(T &x,T &y)
{
    return x>y?x=y,1:0;
}
int N,M,S,T;
struct G
{
    int next,to;
    double val;
    G(int n=0,int t=0,double v=0):next(n),to(t),val(v){}
}Edge[MAXM<<1];
struct Eg
{
    int u,v;
}Edges[MAXM<<1];
int Head[MAXN],Total=1;
int Deg[MAXN],ans,Cur[MAXN];
bool St[MAXN];
inline void addEdge(int u,int v,double w1,double w2)
{
    Edge[++Total]=G(Head[u],v,w1);Head[u]=Total;
    Edge[++Total]=G(Head[v],u,w2);Head[v]=Total;
}
void build(double g)
{
    memset(Head,0,sizeof(Head));
    Total=1;
    for(int i=1;i<=M;++i) addEdge(Edges[i].u,Edges[i].v,1,1);
    for(int i=1;i<=N;++i)
    {
        addEdge(S,i,M,0);
        addEdge(i,T,M+g*2-Deg[i],0);
    }
}
int Fl[MAXN];
inline bool Bfs()
{
    memset(Fl,-1,sizeof(Fl));
    Fl[S]=0,Cur[S]=Head[S];
    queue<int>Q;
    Q.push(S);
    while(!Q.empty())
    {
        int u=Q.front();Q.pop();
        for(int e=Head[u],v;e;e=Edge[e].next)
        {
            v=Edge[e].to;
            if(Fl[v]==-1&&Edge[e].val>0)
            {
                Fl[v]=Fl[u]+1;
                Cur[v]=Head[v];
                if(v==T) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}
double Dfs(int x,double inf)
{
    if(x==T) return inf;
    double flow=0;
    for(int e=Cur[x];e&&flow<inf;e=Edge[e].next)
    {
        Cur[x]=e;
        int v=Edge[e].to;
        if(Fl[v]==Fl[x]+1&&Edge[e].val>0)
        {
            double k=Dfs(v,min(Edge[e].val,inf-flow));
            if(k<=0) Fl[v]=-1;
            Edge[e].val-=k,Edge[e^1].val+=k,flow+=k;
        }
    }
    return flow;
}
double Dinic(double g)
{
    build(g);
    double r=0,flow;
    while(Bfs()) while(flow=Dfs(S,INF)) r+=flow;
    return r;
}
void Search(int x)
{
    St[x]=1;
    if(x!=S) ++ans;
    for(int e=Head[x];e;e=Edge[e].next)
    {
        int v=Edge[e].to;
        if(!St[v]&&Edge[e].val>0) Search(v);
    }
}
int main()
{
    // freopen("minCut.in","r",stdin);
    // freopen("minCut.out","w",stdout);
    while((scanf("%d%d",&N,&M))!=EOF)
    {
        S=0,T=N+1;
        memset(Deg,0,sizeof(Deg));
        memset(St,0,sizeof(St));
        ans=0;
        for(int i=1,u,v;i<=M;++i)
        {
            read(u,v);
            ++Deg[u],++Deg[v];
            Edges[i]={u,v};
        }
        double l=0,r=M;
        while(r-l>eps)
        {
            double mid=(l+r)/2;
            double k=Dinic(mid);
            if(M*N-k>0) l=mid;
            else r=mid;
        }
        Dinic(l);
        Search(S);
        if(!ans) printf("1\n1\n");
        else
        {    
            printf("%d\n",ans);
            for(int i=1;i<=N;++i)
                if(St[i]) printf("%d\n",i);
        }
    }
    return 0;
}
/*
5 6
1 5
5 4
4 2
2 5
1 2
3 1
4 0
*/
