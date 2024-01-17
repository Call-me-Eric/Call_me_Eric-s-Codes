#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define endl '\n'
#define int ll
#define gc cin.get
#define pc cout.put
const int N=2e5+5;
const int M=5e6+5;
const int inf=0x3f3f3f3f;
const int mod=1e8+7;
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
int t,n,m,dep[N],rt;
int head[N],nxt[N],to[N],w[N],cnt;
inl void add(int u,int v,int c){
    nxt[++cnt]=head[u];
    to[cnt]=v;w[cnt]=c;
    head[u]=cnt;
}
inl void dfs(int x,int fa,int d){
    if(d>dep[rt])rt=x;
    dep[x]=d;
    for(int i=head[x];i;i=nxt[i]){
        int y=to[i],c=w[i];
        if(y==fa)continue;
        dfs(y,x,d+c);
    }
}
signed main(){
    freopen("crack.in","r",stdin);
    freopen("crack.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    t=read();
    if(t==5){
        n=read();
        for(int i=1;i<=n-1;i++){
            int u=read(),v=read(),c=read();
            add(u,v,c);add(v,u,c);
        }
        dfs(1,0,0);
        memset(dep,0,sizeof dep);
        dfs(rt,0,0);
        cout<<dep[rt]<<endl;
    }
    return 0;
}