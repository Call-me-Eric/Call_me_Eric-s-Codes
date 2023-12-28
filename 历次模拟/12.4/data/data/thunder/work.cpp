#include<bits/stdc++.h> 
using namespace std; 
#define ll long long 
#define inl inline 
#define int ll 
#define endl '\n' 
#define gc cin.get 
#define pc cout.put 
const int N=2e6+5; 
const int M=1e4+5; 
const int inf=0x3f3f3f3f3f3f3f3f; 
const int mod=1e9+7; 
inl int read(){ 
    int x=0,f=1;char c=gc(); 
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();} 
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=gc();} 
    return x*f; 
} 
inl void write(int x){ 
    if(x<0){pc('-');x=-x;} 
    if(x>9)write(x/10); 
    pc(x%10+'0'); 
} 
inl void writei(int x){write(x);pc(' ');} 
inl void writel(int x){write(x);pc('\n');} 
int n,m,s,t,mincost,dis[N],vis[N],cur[N]; 
int head[N],nxt[N],to[N],w[N],c[N],cnt=1; 
inl void add(int u,int v,int wi,int ci){ 
    nxt[++cnt]=head[u];to[cnt]=v;w[cnt]=wi;c[cnt]=ci;head[u]=cnt; 
    nxt[++cnt]=head[v];to[cnt]=u;w[cnt]=0;c[cnt]=-ci;head[v]=cnt; 
} 
queue<int>q; 
inl bool spfa(){ 
    for(int i=1;i<=t;i++) 
        dis[i]=inf,cur[i]=head[i]; 
    dis[s]=0;q.push(s); 
    while(!q.empty()){ 
        int x=q.front();q.pop();vis[x]=0; 
        for(int i=head[x];i;i=nxt[i]){ 
            int y=to[i],wi=w[i],ci=c[i]; 
            if(wi&&dis[y]>dis[x]+ci){ 
                dis[y]=dis[x]+ci; 
                if(!vis[y])q.push(y),vis[y]=1; 
            } 
        } 
    } 
    return dis[t]^inf; 
} 
inl int dfs(int x,int flow){ 
    if(x==t)return flow; 
    int used=0,rlow; 
    vis[x]=1; 
    for(int &i=cur[x];i;i=nxt[i]){ 
        int y=to[i],wi=w[i],ci=c[i]; 
        if(!vis[y]&&wi&&dis[y]==dis[x]+ci){ 
            if(rlow=dfs(y,min(wi,flow-used))){ 
                w[i]-=rlow,w[i^1]+=rlow; 
                used+=rlow;mincost+=rlow*ci; 
                if(used==flow)continue; 
            } 
        } 
    } 
    vis[x]=0; 
    return used; 
} 
inl void dinic(){while(spfa())dfs(s,inf);} 
signed main(){ 
    // freopen("thunder.in","r",stdin); 
    // freopen("thunder.out","w",stdout); 
    ios::sync_with_stdio(0); 
    cin.tie(0),cout.tie(0); 
    n=read();s=n+1,t=n+2; 
    for(int i=1;i<=n-1;i++){ 
        int u=read(),v=read(),c=read(); 
        add(u,v,inf,c);add(v,u,inf,c); 
    } 
    for(int i=1;i<=n;i++){ 
        int x=read(),y=read(); 
        if(x<y)add(s,i,y-x,0); 
        if(x>y)add(i,t,x-y,0); 
    } 
    dinic(); 
    cout<<mincost<<endl; 
    return 0; 
} 