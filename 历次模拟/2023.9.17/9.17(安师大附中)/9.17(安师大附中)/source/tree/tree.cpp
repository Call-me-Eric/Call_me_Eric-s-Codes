//2024 HOPE IN VALUABLE
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
const int inf=1000000005;
int n,m,idx,mx,siz[N],fa[N],dep[N],son[N],top[N],dfn[N],poi[N],len[N]; vector<int>e[N];
namespace sgt{
	struct Node{ int lc,rc,xmx,xmn,ymx,ymn,tag,sum; }t[N<<2]; int tot;
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	inline void pushup(int u){
		t[u].xmx=max(t[t[u].lc].xmx,t[t[u].rc].xmx);
		t[u].xmn=min(t[t[u].lc].xmn,t[t[u].rc].xmn);
		t[u].ymx=max(t[t[u].lc].ymx,t[t[u].rc].ymx);
		t[u].ymn=min(t[t[u].lc].ymn,t[t[u].rc].ymn);
		t[u].sum=t[t[u].lc].sum+t[t[u].rc].sum;
	}
	inline void lzy(int u){
		swap(t[u].xmx,t[u].ymx);
		swap(t[u].xmn,t[u].ymn);
		t[u].tag^=1;
	}
	inline void pushdown(int u){
		if(!t[u].tag) return;
		lzy(t[u].lc); lzy(t[u].rc);
		t[u].tag=0;
	}
	inline void build(int &u,int l,int r){
		u=++tot;
		if(l==r){
			t[u].xmx=t[u].xmn=l; t[u].sum=siz[poi[l]]-siz[son[poi[l]]];
			t[u].ymx=-inf; t[u].ymn=inf;
			return;
		}
		int mid=l+r>>1;
		build(t[u].lc,l,mid); build(t[u].rc,mid+1,r);
		pushup(u);
	}
	inline void flip(int u,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr) return lzy(u),void();
		int mid=l+r>>1; pushdown(u);
		if(ql<=mid) flip(t[u].lc,l,mid,ql,qr);
		if(qr>mid) flip(t[u].rc,mid+1,r,ql,qr);
		pushup(u);
	}
	inline int findl(int u,int l,int r,int x){
		if(t[u].ymn>x) return -1;
		if(l==r) return poi[l];
		int mid=l+r>>1; pushdown(u);
		if(t[t[u].rc].ymn<=x) return findl(t[u].rc,mid+1,r,x);
		return findl(t[u].lc,l,mid,x);
	}
	inline int findr(int u,int l,int r,int x){
		if(t[u].ymx<x) return -1;
		if(l==r) return poi[l];
		int mid=l+r>>1; pushdown(u);
		if(t[t[u].lc].ymx>=x) return findr(t[u].lc,l,mid,x);
		return findr(t[u].rc,mid+1,r,x);
	}
	inline int query(int u,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr) return t[u].sum;
		int mid=l+r>>1; pushdown(u);
		if(qr<=mid) return query(t[u].lc,l,mid,ql,qr);
		if(ql>mid) return query(t[u].rc,mid+1,r,ql,qr);
		return query(t[u].lc,l,mid,ql,qr)+query(t[u].rc,mid+1,r,ql,qr);
	}
	inline void add(int u,int l,int r,int x,int y){
		if(l==r){
			t[u].sum+=y;
			return;
		}
		int mid=l+r>>1; pushdown(u);
		if(x<=mid) add(t[u].lc,l,mid,x,y);
		else add(t[u].rc,mid+1,r,x,y);
		pushup(u);
	}
}	int rt[N];
inline void dfs1(int u){
	siz[u]=1;
	for(int v:e[u]){
		if(v==fa[u]) continue;
		fa[v]=u; dep[v]=dep[u]+1;
		dfs1(v); siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
inline void dfs2(int u,int tp){
	len[u]=1; top[u]=tp; dfn[u]=++idx; poi[idx]=u;
	if(!son[u]) return;
	dfs2(son[u],tp); len[u]=len[son[u]]+1;
	for(int v:e[u]) if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
}
inline int querydown(int x){
	if(!son[x]) return sgt::query(rt[top[x]],dfn[top[x]],dfn[top[x]]+len[top[x]]-1,dfn[x],dfn[x]);
	int dwn=sgt::findr(rt[top[x]],dfn[top[x]],dfn[top[x]]+len[top[x]]-1,dfn[son[x]]);
	if(dwn==-1) return sgt::query(rt[top[x]],dfn[top[x]],dfn[top[x]]+len[top[x]]-1,dfn[x],dfn[top[x]]+len[top[x]]-1);
	return sgt::query(rt[top[x]],dfn[top[x]],dfn[top[x]]+len[top[x]]-1,dfn[x],dfn[fa[dwn]]);
}
inline int queryup(int x){
	while(x){
		int up=sgt::findl(rt[top[x]],dfn[top[x]],dfn[top[x]]+len[top[x]]-1,dfn[x]);
		if(up!=-1) return querydown(up);
		x=fa[top[x]];
	}
	return querydown(1);
}
inline void update(int x){
	int tmp=querydown(top[x]);
	while(x){
		int ttmp=querydown(top[fa[top[x]]]);
		sgt::flip(rt[top[x]],dfn[top[x]],dfn[top[x]]+len[top[x]]-1,dfn[top[x]],dfn[x]);
		if(top[x]!=1){
			if(sgt::findl(rt[top[x]],dfn[top[x]],dfn[top[x]]+len[top[x]]-1,dfn[top[x]])==-1)
			 	sgt::add(rt[top[fa[top[x]]]],dfn[top[fa[top[x]]]],dfn[top[fa[top[x]]]]+len[top[fa[top[x]]]]-1,dfn[fa[top[x]]],querydown(top[x]));
			else
			 	sgt::add(rt[top[fa[top[x]]]],dfn[top[fa[top[x]]]],dfn[top[fa[top[x]]]]+len[top[fa[top[x]]]]-1,dfn[fa[top[x]]],-tmp);
		}
		x=fa[top[x]]; tmp=ttmp;
	}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	dfs1(1); dfs2(1,1);
	for(int i=1;i<=n;i++)
		if(top[i]==i)
			sgt::build(rt[i],dfn[i],dfn[i]+len[i]-1);
	while(m--){
		int op; cin>>op;
		if(op==1){
			int x,y; cin>>x>>y;
			update(x); update(y);
		}
		else{
			int x; cin>>x;
			cout<<queryup(x)<<'\n';
		}
	}
	return 0;
}