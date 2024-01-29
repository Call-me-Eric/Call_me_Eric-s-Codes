#include<bits/stdc++.h>
#define N 201001
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
ll r,g,b,n,m,fr[N],ed[N],fat[N],fid[N],fa[N];
vector<pair<ll,ll> >v[N];
char col[N];
bool in[N],vis[N];
ll cntr,cntg,cntb;
inline ll find(ll deep)
{
    return fa[deep]==deep?deep:fa[deep]=find(fa[deep]);
}
inline void pdfs(ll ver,ll fa)
{
    vis[ver]=true;
    for(int i=0;i<v[ver].size();i++)
    {
        ll to=v[ver][i].first,id=v[ver][i].second;
        if(vis[to])
            continue;
        in[id]=true;
        cntr+=col[id]=='r';
        cntg+=col[id]=='g';
        cntb+=col[id]=='b';
        pdfs(to,ver);
    }
    return;
}
ll dep[N];
inline void dfs(ll ver,ll fa)
{
    dep[ver]=dep[fa]+1;
    for(int i=0;i<v[ver].size();i++)
    {
        ll to=v[ver][i].first,id=v[ver][i].second;
        if(to==fa||!in[id])
            continue;
        fat[to]=ver,fid[to]=id;
        dfs(to,ver);
    }
    return;
}
signed main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    read(r);
    read(g);
    read(b);
    read(m);
    n=r+g+b+1;
    ll numr=0,numg=0,numb=0;
    for(int i=1;i<=m;i++)
    {
        ll x,y;
        char z[5];
        read(x);
        read(y);
        fr[i]=x,ed[i]=y;
        scanf("%s",z+1);
        col[i]=z[1];
        v[x].push_back(make_pair(y,i));
        v[y].push_back(make_pair(x,i));
        numr+=col[i]=='r',numg+=col[i]=='g',numb+=col[i]=='b';
    }
    if(numr<r||numg<g||numb<b)
    {
        puts("NO");
        exit(0);
    }
    pdfs(1,0);
    mt19937 rnd(time(NULL));
    while(clock()*1.0/CLOCKS_PER_SEC<1.9)
    {
        if(cntr==r&&cntg==g&&cntb==b)
            break;
        dfs(1,0);
        if(cntr<r)
        {
            vector<ll>h;
            for(int i=1;i<=m;i++)
            {
                if(col[i]=='r'&&!in[i])
                    h.push_back(i);
            }
            ll id=h[rnd()%h.size()];
            vector<ll>nowr,nowg,nowb;
            ll x=fr[id],y=ed[id];
            while(dep[x]^dep[y])
            {
                if(dep[x]<dep[y])
                    swap(x,y);
                if(col[fid[x]]=='r')
                    nowr.push_back(fid[x]);
                else if(col[fid[x]]=='g')
                    nowg.push_back(fid[x]);
                else
                    nowb.push_back(fid[x]);
                x=fat[x];
            }
            while(x^y)
            {
                if(col[fid[x]]=='r')
                    nowr.push_back(fid[x]);
                else if(col[fid[x]]=='g')
                    nowg.push_back(fid[x]);
                else
                    nowb.push_back(fid[x]);
                x=fat[x];
                if(col[fid[y]]=='r')
                    nowr.push_back(fid[y]);
                else if(col[fid[y]]=='g')
                    nowg.push_back(fid[y]);
                else
                    nowb.push_back(fid[y]);
                y=fat[y];
            }
            if(nowg.size()&&cntg>g)
            {
                ll did=nowg[rnd()%nowg.size()];
                in[did]=false;
                in[id]=true;
                cntr++;
                cntg--;
            }
            else if(nowb.size()&&cntb>b)
            {
                ll did=nowb[rnd()%nowb.size()];
                in[did]=false;
                in[id]=true;
                cntr++;
                cntb--;
            }
            else
            {
                if(nowr.size())
                {
                    ll did=nowr[rnd()%nowr.size()];
                    in[did]=false;
                    in[id]=true;
                }
                else if(nowg.size())
                {
                    ll did=nowg[rnd()%nowg.size()];
                    in[did]=false;
                    in[id]=true;
                    cntr++,cntg--;
                }
                else
                {
                    ll did=nowb[rnd()%nowb.size()];
                    in[did]=false;
                    in[id]=true;
                    cntr++,cntb--;
                }
            }
        }
        else if(cntg<g)
        {
            vector<ll>h;
            for(int i=1;i<=m;i++)
            {
                if(col[i]=='g'&&!in[i])
                    h.push_back(i);
            }
            ll id=h[rnd()%h.size()];
            vector<ll>nowr,nowg,nowb;
            ll x=fr[id],y=ed[id];
            while(dep[x]^dep[y])
            {
                if(dep[x]<dep[y])
                    swap(x,y);
                if(col[fid[x]]=='r')
                    nowr.push_back(fid[x]);
                else if(col[fid[x]]=='g')
                    nowg.push_back(fid[x]);
                else
                    nowb.push_back(fid[x]);
                x=fat[x];
            }
            while(x^y)
            {
                if(col[fid[x]]=='r')
                    nowr.push_back(fid[x]);
                else if(col[fid[x]]=='g')
                    nowg.push_back(fid[x]);
                else
                    nowb.push_back(fid[x]);
                x=fat[x];
                if(col[fid[y]]=='r')
                    nowr.push_back(fid[y]);
                else if(col[fid[y]]=='g')
                    nowg.push_back(fid[y]);
                else
                    nowb.push_back(fid[y]);
                y=fat[y];
            }
            if(nowr.size()&&cntr>r)
            {
                ll did=nowr[rnd()%nowr.size()];
                in[did]=false;
                in[id]=true;
                cntg++;
                cntr--;
            }
            else if(nowb.size()&&cntb>b)
            {
                ll did=nowb[rnd()%nowb.size()];
                in[did]=false;
                in[id]=true;
                cntg++;
                cntb--;
            }
            else
            {
                if(nowg.size())
                {
                    ll did=nowg[rnd()%nowg.size()];
                    in[did]=false;
                    in[id]=true;
                }
                else if(nowr.size())
                {
                    ll did=nowr[rnd()%nowr.size()];
                    in[did]=false;
                    in[id]=true;
                    cntg++,cntr--;
                }
                else
                {
                    ll did=nowb[rnd()%nowb.size()];
                    in[did]=false;
                    in[id]=true;
                    cntg++,cntb--;
                }
            }
        }
        else
        {
            vector<ll>h;
            for(int i=1;i<=m;i++)
            {
                if(col[i]=='b'&&!in[i])
                    h.push_back(i);
            }
            ll id=h[rnd()%h.size()];
            vector<ll>nowr,nowg,nowb;
            ll x=fr[id],y=ed[id];
            while(dep[x]^dep[y])
            {
                if(dep[x]<dep[y])
                    swap(x,y);
                if(col[fid[x]]=='r')
                    nowr.push_back(fid[x]);
                else if(col[fid[x]]=='g')
                    nowg.push_back(fid[x]);
                else
                    nowb.push_back(fid[x]);
                x=fat[x];
            }
            while(x^y)
            {
                if(col[fid[x]]=='r')
                    nowr.push_back(fid[x]);
                else if(col[fid[x]]=='g')
                    nowg.push_back(fid[x]);
                else
                    nowb.push_back(fid[x]);
                x=fat[x];
                if(col[fid[y]]=='r')
                    nowr.push_back(fid[y]);
                else if(col[fid[y]]=='g')
                    nowg.push_back(fid[y]);
                else
                    nowb.push_back(fid[y]);
                y=fat[y];
            }
            if(nowr.size()&&cntr>r)
            {
                ll did=nowr[rnd()%nowr.size()];
                in[did]=false;
                in[id]=true;
                cntb++;
                cntr--;
            }
            else if(nowg.size()&&cntg>g)
            {
                ll did=nowg[rnd()%nowg.size()];
                in[did]=false;
                in[id]=true;
                cntb++;
                cntg--;
            }
            else
            {
                if(nowb.size())
                {
                    ll did=nowb[rnd()%nowb.size()];
                    in[did]=false;
                    in[id]=true;
                }
                else if(nowr.size())
                {
                    ll did=nowr[rnd()%nowr.size()];
                    in[did]=false;
                    in[id]=true;
                    cntb++,cntr--;
                }
                else
                {
                    ll did=nowg[rnd()%nowg.size()];
                    in[did]=false;
                    in[id]=true;
                    cntb++,cntg--;
                }
            }
        }
    }
    if(cntr==r&&cntg==g&&cntb==b)
    {
        puts("YES");
        for(int i=1;i<=m;i++)
            putchar(in[i]?'1':'0');
    }
    else
        puts("NO");
   /* for(int i=1;i<=n;i++)
        fa[i]=i;
    ll tr=0,tg=0,tb=0;
    for(int i=1;i<=m;i++)
    {
        if(in[i])
        {
            tr+=col[i]=='r',tg+=col[i]=='g',tb+=col[i]=='b';
            assert(find(fr[i])^find(ed[i]));
            fa[find(fr[i])]=find(ed[i]);
        }
    }*/ //spj
   // assert(cntr==tr&&cntg==tg&&cntb==tb);
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<endl;
    exit(0);
}