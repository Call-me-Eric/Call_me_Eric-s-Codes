#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+2;
const int mod=998244353;
    namespace io{char buf[(1<<21)+5],*p1,*p2;
    #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
    int ot[40],tp;
    int read(){
        int f=0,x=0;
        char ch=getchar();
        while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
        while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
    void write(int x){
        if(!x){putchar('0');return ;}
        while(x)ot[++tp]=x%10,x/=10;
        while(tp)putchar(ot[tp--]+'0');
        return ;
    }
}
int n;
int cnt;
int hed[maxn],sz[maxn];
int inv[maxn],f[maxn][maxn],g[maxn];
int ans;
struct node_edge{
    int nxt,to;
}G[maxn*2];
void add(int u,int v){
    G[++cnt]=(node_edge){hed[u],v};
    hed[u]=cnt;
    return ;
}
void upd(int &x,int v){((x+=v)>=mod)?(x-=mod):x;}
void calc_inv(){
    inv[1]=1;for(int i=2;i<=n;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    return ;
}
void dfs(int x,int fa){
    f[x][sz[x]=1]=1;
    for(int i=hed[x],v,sum;i;i=G[i].nxt){
        v=G[i].to;
        if(!(v^fa))continue;
        dfs(v,x);
        sum=0;
        for(int j=1;j<=sz[v];j++)upd(sum,1ll*f[v][j]*inv[j]%mod);//sum is no edge
        for(int j=1;j<=sz[x];j++){
            for(int k=1;k<=sz[v];k++)upd(g[j+k],mod-1ll*f[x][j]*f[v][k]%mod*inv[k]%mod);//g is fa to son
        }
        sz[x]+=sz[v];
        for(int j=1;j<=sz[x];j++)f[x][j]=(1ll*f[x][j]*sum%mod+g[j])%mod,g[j]=0;
    }
    for(int i=1;i<=sz[x];i++)f[x][i]=1ll*f[x][i]*inv[i]%mod;
    return ;
}
int main(){
    freopen("band.in","r",stdin);
    freopen("band.out","w",stdout);
    n=io::read();
    calc_inv();
    for(int i=1,u,v;i<n;i++){
        u=io::read(),v=io::read();
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=sz[1];i++)upd(ans,f[1][i]);
    io::write(ans);
    return 0;
}