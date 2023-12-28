#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=1e5+10,mod=998244353,rg=1e11;
inline void Add(int &x,int y){ x=(x+y)%mod; }

int Q,opt;
struct ques{int op,l,r,x,v;}q[maxn];

namespace subtask_1
{
    #define ls (t[p].lc)
    #define rs (t[p].rc)
    #define mid ((l+r)>>1)
    struct node{int val,tag,lc,rc;}t[maxn<<1];
    int idx,rt;
    inline void pushup(int p){ t[p].val=(t[ls].val+t[rs].val)%mod; }
    inline void updata(int &p,int l,int r,int k)
    {
        if(!p) p=++idx;
        Add(t[p].val,(r-l+1)*k%mod);
        Add(t[p].tag,k);
    }
    inline void pushdown(int p,int l,int r)
    {
        if(!t[p].tag) return;
        updata(ls,l,mid,t[p].tag);
        updata(rs,mid+1,r,t[p].tag);
        t[p].tag=0;
    }
    inline void modify(int &p,int l,int r,int L,int R,int x)
    {
        if(!p) p=++idx;
        if(L<=l && r<=R) return updata(p,l,r,x);
        pushdown(p,l,r);
        if(L<=mid) modify(ls,l,mid,L,R,x);
        if(R>mid) modify(rs,mid+1,r,L,R,x);
        pushup(p); 
    }
    inline int query(int p,int l,int r,int L,int R)
    {
        if(L<=l && r<=R) return t[p].val;
        pushdown(p,l,r);
        int res=0;
        if(L<=mid) Add(res,query(ls,l,mid,L,R));
        if(R>mid) Add(res,query(rs,mid+1,r,L,R));
        return res; 
    }
    inline void solve()
    {
        int lst=0;
        for(int i=1;i<=Q;i++)
        {
            auto [op,l,r,x,v]=q[i];
            if(opt) l^=lst,r^=lst,x^=lst,v^=lst;
            if(op==1) modify(rt,1,rg,l,r,v);
            if(op==3) cout<<(lst=query(rt,1,rg,l,r))<<'\n';
        }
    }
}

namespace subtask_2
{
    const int MAXN=2010,topx=1000,topy=1000;
    int val[MAXN*MAXN],X[MAXN*MAXN],Y[MAXN*MAXN];
    int id[MAXN][MAXN],idx;
    const int dx[4]={0,-1,0,1};
    const int dy[4]={1,0,-1,0};
    inline void fill(int x,int y,int len,int d)
    {
        if(len>1000) return;
        for(int i=1;i<=len;i++)
        {
            id[x][y]=++idx;
            X[idx]=x,Y[idx]=y;
            x+=dx[d],y+=dy[d];
        }
        d=(d+1)%4;
        for(int i=1;i<=len;i++)
        {
            id[x][y]=++idx;
            X[idx]=x,Y[idx]=y;
            x+=dx[d],y+=dy[d];
        }
        fill(x,y,len+1,d=(d+1)%4);
    }
    inline void build()
    {
        int x=topx,y=topy;
        fill(x,y,1,0);
    }
    inline void solve()
    {
        build();
        int lst=0;
        for(int i=1;i<=Q;i++)
        {
            auto [op,l,r,x,v]=q[i];
            if(opt) l^=lst,r^=lst,x^=lst,v^=lst;
            if(op==1){ for(int i=l;i<=r;i++) Add(val[i],v); }
            if(op==2)
            {
                int px=X[x],py=Y[x];
                for(int i=min(px,topx);i<=max(px,topx);i++)
                    for(int j=min(py,topy);j<=max(py,topy);j++)
                        Add(val[id[i][j]],v);
            }
            if(op==3)
            {
                int res=0;
                for(int i=l;i<=r;i++) Add(res,val[i]);
                cout<<(lst=res)<<'\n';
            }
        }
    }
}


inline void solve()
{
    cin>>Q>>opt;
    bool flag=true;
    for(int i=1;i<=Q;i++)
    {
        auto &[op,l,r,x,v]=q[i];
        cin>>op;
        if(op==1) cin>>l>>r>>v;
        if(op==2) flag=false,cin>>x>>v;
        if(op==3) cin>>l>>r;
    }
    if(flag) subtask_1::solve();
    else subtask_2::solve();
}
signed main()
{
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();
}
