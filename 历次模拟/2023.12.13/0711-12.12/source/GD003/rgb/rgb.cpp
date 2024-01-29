#include<bits/stdc++.h>
using namespace std;

const int inf=2139062143;
mt19937 mt(114514);

int cC[3],pC[3];
struct Edge
{
    int end,col;
};
vector<Edge> G[260];
map<pair<int,int>,bool> vis;
map<pair<int,int>,int> enu;
map<pair<int,int>,int> eco;
int fth[260],dep[260];
bool pvs[260];

struct FlowEdge
{
    int end,cap,rev;
};
vector<FlowEdge> Gf[70010];
int S,T,C[3],tot;
int lab[70010],cur[70010];
queue<int> q;

bool ans[70010];

inline
int trans(char c)
{
    if(c=='r') return 0;
    if(c=='g') return 1;
    if(c=='b') return 2;
    return -1;
}
inline
void preworkDfs(int u,int fa)
{
    pvs[u]=1;
    fth[u]=fa,dep[u]=dep[fa]+1;
    shuffle(G[u].begin(),G[u].end(),mt);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i].end,c=G[u][i].col;
        if(pvs[v]==1) continue;
        pC[c]++;
        vis[pair<int,int>(u,v)]=1;
        vis[pair<int,int>(v,u)]=1;
        preworkDfs(v,u);
    }
}

inline
void linkEdge(int u,int v,int c)
{
    Gf[u].push_back((FlowEdge){v,c,Gf[v].size()});
    Gf[v].push_back((FlowEdge){u,0,Gf[u].size()-1});
}
inline
bool getLabel()
{
    while(!q.empty()) q.pop();
    fill(lab+1,lab+tot+1,-1);
    lab[S]=0,q.push(S);

    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<Gf[u].size();i++)
        {
            int v=Gf[u][i].end;
            if(lab[v]!=-1||Gf[u][i].cap==0) continue;
            lab[v]=lab[u]+1,q.push(v);
        }
    }

    return lab[T]!=-1;
}
inline
int getFlow(int u,int rmn_flw)
{
    if(u==T||rmn_flw==0)
    {
        return rmn_flw;
    }

    int res_flw=0;
    for(int &i=cur[u];i<Gf[u].size();i++)
    {
        int v=Gf[u][i].end,r=Gf[u][i].rev;
        if(lab[v]!=lab[u]+1||Gf[u][i].cap==0) continue;
        int dlt_flw=getFlow(v,min(Gf[u][i].cap,rmn_flw));
        rmn_flw-=dlt_flw,res_flw+=dlt_flw;
        Gf[u][i].cap-=dlt_flw,Gf[v][r].cap+=dlt_flw;
        if(rmn_flw==0) break;
    }
    return res_flw;
}
inline
int Dinic()
{
    int res_flw=0,dlt_flw=0;
    while(getLabel())
    {
        fill(cur+1,cur+tot+1,0);
        while(dlt_flw=getFlow(S,inf))
        {
            res_flw+=dlt_flw;
        }
    }
    return res_flw;
}

int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int m;
    cin>>cC[0]>>cC[1]>>cC[2]>>m;
    int n=cC[0]+cC[1]+cC[2]+1;
    for(int i=1;i<=m;i++)
    {
        int u,v,x;
        char c;
        cin>>u>>v>>c,x=trans(c);
        G[u].push_back((Edge){v,x});
        G[v].push_back((Edge){u,x});
        enu[pair<int,int>(u,v)]=i;
        enu[pair<int,int>(v,u)]=i;
        eco[pair<int,int>(u,v)]=x;
        eco[pair<int,int>(v,u)]=x;
    }
    // cout<<"Input done"<<endl;

    preworkDfs(1,1);
    // cout<<"Prework done"<<endl;
    // cout<<"Fth : ";
    // for(int i=1;i<=n;i++) cout<<fth[i]<<" ";
    // cout<<endl;
    // cout<<"Dep : ";
    // for(int i=1;i<=n;i++) cout<<dep[i]<<" ";
    // cout<<endl;

    int exf=0;
    tot=m+5;
    S=m+1,T=m+2,C[0]=m+3,C[1]=m+4,C[2]=m+5;
    if(cC[0]<pC[0]) linkEdge(S,C[0],pC[0]-cC[0]);
    else linkEdge(C[0],T,cC[0]-pC[0]),exf+=cC[0]-pC[0];
    if(cC[1]<pC[1]) linkEdge(S,C[1],pC[1]-cC[1]);
    else linkEdge(C[1],T,cC[1]-pC[1]),exf+=cC[1]-pC[1];
    if(cC[2]<pC[2]) linkEdge(S,C[2],pC[2]-cC[2]);
    else linkEdge(C[2],T,cC[2]-pC[2]),exf+=cC[2]-pC[2];
    // cout<<"S,T,C built"<<endl;
    // cout<<"S = "<<S<<" , T = "<<T<<" , C = "<<C[0]<<" , "<<C[1]<<" , "<<C[2]<<endl;
    for(int pu=1;pu<=n;pu++)
    {
        for(int i=0;i<G[pu].size();i++)
        {
            int u=pu,v=G[pu][i].end,c=G[pu][i].col;
            if(u>v) continue;
            // cout<<"Checking edge "<<u<<" <--"<<c<<"--> "<<v<<endl;
            
            if(vis[pair<int,int>(u,v)]==1)
            {
                // cout<<"It is used"<<endl;
                if(cC[c]>=pC[c])
                {
                    // cout<<"It must be used"<<endl;
                    ans[enu[pair<int,int>(u,v)]]=1;
                    continue;
                }
                // cout<<"Link "<<C[c]<<" ---> "<<enu[pair<int,int>(u,v)]<<endl;
                linkEdge(C[c],enu[pair<int,int>(u,v)],1);
            }
            else
            {
                if(abs(dep[u]-dep[v])>=20) continue;
                // cout<<"It is not used"<<endl;
                if(cC[c]<=pC[c]) continue;
                // cout<<"It may be used"<<endl;
                // cout<<"Link "<<enu[pair<int,int>(u,v)]<<" ---> "<<C[c]<<endl;
                linkEdge(enu[pair<int,int>(u,v)],C[c],1);

                int pn=enu[pair<int,int>(u,v)];
                if(dep[u]<dep[v]) swap(u,v);
                // cout<<"All of the edges on route "<<u<<" to "<<v<<" can be changed"<<endl;
                while(u!=v)
                {
                    if(eco[pair<int,int>(u,fth[u])]!=c)
                    {
                        // cout<<"Link "<<enu[pair<int,int>(u,fth[u])]<<" ---> "<<pn<<endl;
                        linkEdge(enu[pair<int,int>(u,fth[u])],pn,1);
                    }
                    u=fth[u];
                }
            }
        }
    }
    // cout<<"Build graph done"<<endl;
    for(int u=1;u<=tot;u++)
    {
        for(int i=0;i<Gf[u].size();i++)
        {
            int v=Gf[u][i].end,c=Gf[u][i].cap;
            if(c==0) continue;
            // cout<<u<<" --"<<c<<"-> "<<v<<endl;
        }
    }

    int flw=Dinic();
    if(flw!=exf)
    {
        cout<<"NO"<<'\n'<<flush;
        return 0;
    }
    cout<<"YES"<<'\n';
    for(int c=0;c<3;c++)
    {
        for(int i=0;i<Gf[C[c]].size();i++)
        {
            if(Gf[C[c]][i].cap==1) ans[Gf[C[c]][i].end]=1;
        }
    }
    
    for(int i=1;i<=m;i++)
    {
        cout<<ans[i];
    }
    cout<<'\n'<<flush;
}
/*
2 2 3 10
1 2 r
1 3 r
1 4 g
2 5 b
3 6 r
3 7 r
6 8 g
1 5 b
1 6 b
1 7 b
*/