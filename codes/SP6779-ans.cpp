#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson rt<<1
#define rson rt<<1|1

const int N=1e5+5,M=2e5+5;
int n,q,tot,x[N],lnk[N],ter[M],nxt[M];
int idx,dfn[N],seq[N],sz[N],dep[N],hvy[N],top[N],fa[N];
struct Node {
    int sum,lmx,rmx,ret,tag;
    bool cov;
    Node() {sum=lmx=rmx=ret=0;}
}seg[N<<2];

void add(int u,int v) {
    ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot;
}
void dfs1(int u,int f) {
    dep[u]=dep[f]+1,fa[u]=f,sz[u]=1;
    for(int i=lnk[u];i;i=nxt[i]) {
        int v=ter[i];
        if(v==f) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hvy[u]]) hvy[u]=v;
    }
}
void dfs2(int u,int tp) {
    dfn[u]=++idx,seq[idx]=u,top[u]=tp;
    if(!hvy[u]) return;
    dfs2(hvy[u],tp);
    for(int i=lnk[u];i;i=nxt[i]) {
        int v=ter[i];
        if(v==fa[u]||v==hvy[u]) continue;
        dfs2(v,v);
    }
}
Node merge(Node x,Node y) {
    Node ans;
    ans.sum=x.sum+y.sum;
    ans.lmx=std::max(x.lmx,x.sum+y.lmx);
    ans.rmx=std::max(y.rmx,y.sum+x.rmx);
    ans.ret=std::max(std::max(x.ret,y.ret),x.rmx+y.lmx);
    ans.tag=ans.cov=0;
    return ans;
}
void build(int rt,int l,int r) {
    if(l==r) {
        seg[rt].sum=x[seq[l]];
        seg[rt].lmx=seg[rt].rmx=seg[rt].ret=std::max(seg[rt].sum,0);
        seg[rt].cov=0;
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    seg[rt]=merge(seg[lson],seg[rson]);
}
void update(int rt,int l,int r,int k) {
    seg[rt].sum=(r-l+1)*k;
    seg[rt].lmx=seg[rt].rmx=seg[rt].ret=std::max(seg[rt].sum,0);
    seg[rt].cov=1,seg[rt].tag=k;
}
void pushdown(int rt,int l,int r) {
    if(!seg[rt].cov) return;
    int mid=(l+r)>>1;
    update(lson,l,mid,seg[rt].tag);
    update(rson,mid+1,r,seg[rt].tag);
    seg[rt].tag=seg[rt].cov=0;
}
void modify(int x,int y,int rt,int l,int r,int k) {
    if(x<=l&&r<=y) {
        update(rt,l,r,k);
        return;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if(x<=mid) modify(x,y,lson,l,mid,k);
    if(mid<y) modify(x,y,rson,mid+1,r,k);
    seg[rt]=merge(seg[lson],seg[rson]);
}
Node query(int x,int y,int rt,int l,int r) {
    if(x<=l&&r<=y) return seg[rt];
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    Node L,R;
    if(x<=mid) L=query(x,y,lson,l,mid);
    if(mid<y) R=query(x,y,rson,mid+1,r);
    return merge(L,R);
}
void chainModify(int u,int v,int k) {
    for(int fu=top[u],fv=top[v];fu^fv;u=fa[fu],fu=top[u]) {
        if(dep[fu]<dep[fv]) std::swap(u,v),std::swap(fu,fv);
        modify(dfn[fu],dfn[u],1,1,n,k);
    }
    if(dep[u]>dep[v]) std::swap(u,v);
    modify(dfn[u],dfn[v],1,1,n,k);
}
Node chainQuery(int u,int v) {
    Node L,R;
    for(int fu=top[u],fv=top[v];fu^fv;) {
        if(dep[fu]<dep[fv]) {
            R=merge(query(dfn[fv],dfn[v],1,1,n),R);
            v=fa[fv],fv=top[v];
        } else {
            L=merge(query(dfn[fu],dfn[u],1,1,n),L);
            u=fa[fu],fu=top[u];
        }
    }
    if(dep[u]>dep[v]) {
        L=merge(query(dfn[v],dfn[u],1,1,n),L);
    } else {
        R=merge(query(dfn[u],dfn[v],1,1,n),R);
    }
    std::swap(L.lmx,L.rmx);
    return merge(L,R);
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&x[i]);
    for(int i=1;i<n;++i) {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs1(1,0),dfs2(1,1),build(1,1,n);
    scanf("%d",&q);
    while(q--) {
        int opt;
        scanf("%d",&opt);
        if(opt==1) {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",chainQuery(l,r).ret);
        } else {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            chainModify(l,r,k);
        }
    }
    return 0;
}
