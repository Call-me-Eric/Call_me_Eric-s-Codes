#include<bits/stdc++.h>
using namespace std;
const int N=255,M=N*N<<1;
int n,m;
int head[N],to[M],nxt[M],val[M],tot=1;
int cnt[4];
int need[4];
int dep[N],fa[N],fid[N];
inline void _add(int f,int t,int v)
{
    to[++tot]=t,nxt[tot]=head[f],head[f]=tot,val[tot]=v;
}
inline void add(int a,int b,int v)
{
    _add(a,b,v),_add(b,a,v);
}
bool chose[M];
void build(int p,int f,int fi)
{
    static bool vis[N];
    vis[p]=1;
    dep[p]=dep[f]+1,fa[p]=f,fid[p]=fi;
    for(int i=head[p];i;i=nxt[i])
    {
        if(to[i]==f||vis[to[i]])continue;
        need[val[i]]--,chose[i]=chose[i^1]=1;
        build(to[i],p,i^1);
    }
}
list<int>wt[4];
void rebuild(int p,int f,int fi)
{
    dep[p]=dep[f]+1,fa[p]=f,fid[p]=fi;
    for(int i=head[p];i;i=nxt[i])
    {
        if(to[i]==f||!chose[i])continue;
        build(to[i],p,i^1);
    }
}
inline int findEdge(int id,int del)
{
    int a=to[id],b=to[id^1];
    if(dep[a]<dep[b])swap(a,b);
    while(dep[a]>dep[b])
    {
        if(val[fid[a]]==del)
            return fid[a];
        a=fa[a];
    }
    while(a!=b)
    {
        if(val[fid[a]]==del)
            return fid[a];
        if(val[fid[b]]==del)
            return fid[b];
        a=fa[a],b=fa[b];
    }
    return 0;
}
inline bool change(int add,int del,list<int>::iterator id)
{
    int e=findEdge(*id,del);
    if(e==0)return 0;
    need[val[*id]]--,need[del]++;
    wt[add].erase(id),wt[del].push_back(e);
    chose[*id]=chose[*id^1]=1,chose[e]=chose[e^1]=0;
    rebuild(1,0,0);
    return 1;
}
inline bool work(int add,int del)
{
    for(auto it=wt[add].begin();it!=wt[add].end();++it)
    {
        if(change(add,del,it))
            return 1;
    }
    return 0;
}
inline bool work(int add)
{
    for(int i=1;i<=3;++i)
    {
        if(i==add)continue;
        if(need[i]<0)
            if(work(add,i))
                return 1;
    }
    for(int i=1;i<=3;++i)
    {
        if(i==add)continue;
        if(work(add,i))
            return 1;
    }
    return 0;
}
inline void work()
{
    while(need[1]|need[2]|need[3])
    {
        for(int i=1;i<=3;++i)
        {
            if(clock()*1.0/CLOCKS_PER_SEC>1800)
                    return puts("No"),void();    
            while(need[i]>0)
                if(!work(i))
                    return puts("No"),void();
        }
    }
    puts("Yes");
    for(int i=2;i<=tot;i+=2)
        putchar('0'+chose[i]);
}
int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);

    scanf("%d %d %d %d",need+1,need+2,need+3,&m);
    n=need[1]+need[2]+need[3]+1;
    for(int i=1,a,b;i<=m;++i)
    {
        char v;
        scanf("%d %d %c",&a,&b,&v);
        v=v=='r'?1:2+(v=='b');
        add(a,b,v);
        ++cnt[v];
    }
    if(cnt[1]<need[1]||cnt[2]<need[2]||cnt[3]<need[3])
        return puts("No");
    
    build(1,0,0);
    for(int i=2;i<=tot;i+=2)
    {
        if(!chose[i])
            wt[val[i]].push_back(i);
    }
    work();
    return 0;
}