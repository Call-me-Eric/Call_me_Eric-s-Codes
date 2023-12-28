#include<bits/stdc++.h>
#define ri register signed
#define p(i) ++i
using namespace std;
namespace IO{
    char buf[1<<21],*p1=buf,*p2=buf;
    #define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++
    inline int read() {
        ri x=0,f=1;char ch=gc();
        while(ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=gc();}
        while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=gc();}
        return x*f;
    }
}
using IO::read;
namespace nanfeng{
    #define int long long//懒人必备
    #define cmax(x,y) ((x)>(y)?(x):(y))
    #define cmin(x,y) ((x)>(y)?(y):(x))
    #define FI FILE *IN
    #define FO FILE *OUT
    #undef bool
    static const int N=45;
    int ch[N][N],id[N][N],n,m,T,tot=1,B,b,W,w,mx;
    namespace NetworkFlows{
        #define jud(i,j) ((i)&&(j)&&(i)<=n&&(j)<=m)
        static const int INF=1e18+7;
        int first[N*N],dep[N*N],cur[N*N],que[N*N],t=2,sw,s=1,et;
        signed dx[5]={0,1,0,-1,0},dy[5]={0,0,1,0,-1};
        struct edge{int v,nxt,w;}e[N*N*5];
        inline void add(int u,int v,int w) {
            e[t].v=v,e[t].w=w;
            e[t].nxt=first[u];
            first[u]=t++;
        }
        inline void init() {et=n*m+2,t=2,sw=0;memset(first,0,sizeof(first));}
        inline void build(int w) {
            for (ri i(1);i<=n;p(i)) {
                for (ri j(1);j<=m;p(j)) {
                    if (!((i+j)%2)) {
                        sw+=w-ch[i][j];
                        add(s,id[i][j],w-ch[i][j]);
                        add(id[i][j],s,0);
                        for (ri d(1);d<=4;p(d)) {
                            if (jud(i+dx[d],j+dy[d])) add(id[i][j],id[i+dx[d]][j+dy[d]],INF),add(id[i+dx[d]][j+dy[d]],id[i][j],0);
                        }
                    } else add(id[i][j],et,w-ch[i][j]),add(et,id[i][j],0);
                }
            }
        }
        inline bool bfs(int s,int t) {
            memset(dep,0,sizeof(dep));
            ri hd=1,tl=0;
            dep[que[p(tl)]=s]=1;
            cur[s]=first[s];
            while(hd<=tl) {
                s=que[hd++];
                for (ri i(first[s]),v;i;i=e[i].nxt) {
                    if (e[i].w&&!dep[v=e[i].v]) {
                        dep[v]=dep[s]+1;
                        cur[que[p(tl)]=v]=first[v];
                        if (v==t) return 1;
                    }
                }
            }
            return 0;
        }
        int dfs(int x,int flow) {
            if (x==et||!flow) return flow;
            int rst=flow;
            for (ri i(cur[x]),v;i&&rst;i=e[i].nxt) {
                if (e[i].w&&dep[v=e[i].v]==dep[x]+1) {
                    register int k;
                    if (!(k=dfs(v,cmin(e[i].w,rst)))) dep[v]=0;
                    e[i].w-=k,e[i^1].w+=k,rst-=k;
                }
                cur[x]=i;
            }
            return flow-rst;
        }
        inline int dinic() {
            int res=0;
            while(bfs(s,et)) res+=dfs(s,INF);
            return res;
        }
    }
    inline bool check(int w) {
        NetworkFlows::init();
        NetworkFlows::build(w);
        return NetworkFlows::dinic()==NetworkFlows::sw;
    }
    inline void init() {mx=B=b=W=w=0,tot=1;}
    inline int main() {
        // FI=freopen("nanfeng.in","r",stdin);
        // FO=freopen("nanfeng.out","w",stdout);
        T=read();
        for (ri z(1);z<=T;p(z)) {
            init();
            n=read(),m=read();
            for (ri i(1);i<=n;p(i)) {
                for (ri j(1);j<=m;p(j)) {
                    ch[i][j]=read(),id[i][j]=p(tot);
                    mx=cmax(mx,ch[i][j]);
                    if (!((i+j)%2)) p(B),b+=ch[i][j];
                    else p(W),w+=ch[i][j];
                }
            }
            if (B!=W) {
                int num=(b-w)/(B-W);
                if (num>=mx&&check(num)) printf("%lld\n",B*num-b);
                else puts("-1"); 
            } else {
                if (b!=w) {puts("-1");continue;}
                int l=mx,r=1e11,res=-1;
                while(l<=r) {
                    int mid((l+r)>>1);
                    if (check(mid)) r=mid-1,res=mid;
                    else l=mid+1;
                }
                printf("%lld\n",res==-1?-1:B*res-b);
            }
        }
        return 0;
    }
    #undef int
}
int main() {return nanfeng::main();}
