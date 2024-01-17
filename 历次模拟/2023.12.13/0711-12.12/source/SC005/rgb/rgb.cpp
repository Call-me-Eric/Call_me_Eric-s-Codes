#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define rint int
#define endl '\n'
int read(){
    int x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c))x=x*10+c-48,c=getchar();
    return x*f;
}const int N=260,M=N*(N-1)/2,p=1e9;

mt19937 rd(19260817);
int n,m,rgb[3];
struct Edge{int x,y,c,id;}E[M];
bool use[M];int cnt[3];
int f[N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}

void choose()
{
    for(rint i=1;i<=n;i++) f[i]=i;
    for(rint i=1;i<=m;i++)
    {
        int x=find(E[i].x),y=find(E[i].y);
        if(x!=y) f[x]=y,use[E[i].id]=1,cnt[E[i].c]++;
    }
}

struct edge{int to,id;};
vector<edge> e[N];
int d[N][3],FA[N],laste[N][3];
int dep[N],dfn[N],idx,st[10][N];
void dfs(int x=1,int fa=0,int d0=0,int d1=0,int d2=0,int dd=1,int id0=0,int id1=0,int id2=0)
{
    dep[x]=dd,dfn[x]=++idx,st[0][idx]=fa;
    
    FA[x]=fa,laste[x][0]=id0,laste[x][1]=id1,laste[x][2]=id2;
    d[x][0]=d0,d[x][1]=d1,d[x][2]=d2;
    for(auto &it:e[x])
    if(it.to!=fa) 
    {
        if(E[it.id].c==0) dfs(it.to,x,d0+1,d1,d2,dd+1,it.id,id1,id2);
        if(E[it.id].c==1) dfs(it.to,x,d0,d1+1,d2,dd+1,id0,it.id,id2);
        if(E[it.id].c==2) dfs(it.to,x,d0,d1,d2+1,dd+1,id0,id1,it.id);
    }
}

void init()
{
    for(rint i=1;i<=n;i++) e[i].clear();
    for(rint i=1;i<=m;i++) 
    if(use[E[i].id]) 
        e[E[i].x].push_back({E[i].y,E[i].id}),
        e[E[i].y].push_back({E[i].x,E[i].id});
    idx=0;
    dfs();
    for(rint i=1,lg=__lg(n);i<=lg;i++)
    for(rint j=1;j+(1<<i)-1<=n;j++)
    if(dep[st[i-1][j]]<dep[st[i-1][j+(1<<(i-1))]]) st[i][j]=st[i-1][j];
    else st[i][j]=st[i-1][j+(1<<(i-1))];
}
inline int lca(int x,int y)
{
    x=dfn[x],y=dfn[y];
    if(x>y) swap(x,y);
    x++;
    int lg=__lg(y-x+1);
    if(dep[st[lg][x]]<dep[st[lg][y-(1<<lg)+1]]) return st[lg][x];
    return st[lg][y-(1<<lg)+1];
}

int ban=-1;
void work(int c)
{
    // puts("work");
    while(cnt[c]<rgb[c])
    {
        init();
        
        bool over=0;
        for(rint i=1;i<=m&&!over;i++)
        if(!use[E[i].id]&&E[i].c==c)
        {
            int x=E[i].x,y=E[i].y,fa=lca(x,y);bool can=0;int tar=0;
            for(rint j=0;j<3;j++)
            if(j!=c&&j!=ban&&d[x][j]+d[y][j]-2*d[fa][j]) can=1,tar=j;
            
            if(can)
            {
                int xe=laste[x][tar],ye=laste[y][tar];
                if(min(dep[E[xe].x],dep[E[xe].y])<min(dep[E[ye].x],dep[E[ye].y])) swap(xe,ye);
                use[xe]=0,use[i]=1;
                cnt[c]++,cnt[tar]--;
                over=1;
            }
        }
        if(!over)
        {
            if(~ban&&clock()<=1.9*CLOCKS_PER_SEC)
            {
                static int o[M];
                for(rint i=1;i<=m;i++) o[i]=i;
                shuffle(o+1,o+m+1,rd);
                for(rint z=1,i=o[z];z<=m;z++,i=o[z])
                if(!use[E[i].id]&&E[i].c==ban)
                {
                    int x=E[i].x,y=E[i].y,fa=lca(x,y);
                    if(d[x][ban]+d[y][ban]-2*d[fa][ban])
                    {
                        int xe=laste[x][ban],ye=laste[y][ban];
                        if(min(dep[E[xe].x],dep[E[xe].y])<min(dep[E[ye].x],dep[E[ye].y])) swap(xe,ye);
                        use[xe]=0,use[i]=1;
                        break;
                    }
                }
            }
            else puts("NO"),exit(0);
        }
    }
}

signed main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    
    rgb[0]=read(),rgb[1]=read(),rgb[2]=read(),m=read(),n=rgb[0]+rgb[1]+rgb[2]+1;
    for(rint i=1;i<=m;i++)
    {
        int x=read(),y=read();char c;cin>>c;
        E[i]={x,y,c=='r'?0:c=='g'?1:2,i};
    }
    choose();
    if(cnt[0]+cnt[1]+cnt[2]!=rgb[0]+rgb[1]+rgb[2]) return puts("NO"),0;
    
    // cout<<cnt[0]<<" "<<cnt[1]<<" "<<cnt[2]<<endl;
    // for(rint i=1;i<=m;i++) cout<<use[i];cout<<endl;
    
    for(rint i=0;i<3;i++)
    if(cnt[i]<rgb[i]) {work(i);ban=i;break;}
    
    // cout<<cnt[0]<<" "<<cnt[1]<<" "<<cnt[2]<<endl;
    // for(rint i=1;i<=m;i++) cout<<use[i];cout<<endl;
    
    for(rint i=0;i<3;i++)
    if(cnt[i]<rgb[i]) {work(i);break;}
    puts("YES");
    for(rint i=1;i<=m;i++) cout<<use[i];cout<<endl;
    return 0;
}