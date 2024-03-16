#include <bits/stdc++.h>

using namespace std;

const int N=231231,lb=30,inf=0x3f3f3f3f;

int a[N],v;

namespace ST{
	int s[N][18];
	void build(int n){
		for(int i=1;i<=n;++i) s[i][0]=a[i];
		for(int l=1;(1<<l)<=n;++l) for(int i=1;i+(1<<l)-1<=n;++i)
			s[i][l]=max(s[i][l-1],s[i+(1<<l-1)][l-1]);
	}
	int mx(int l,int r){
		int g=__lg(r-l+1);
		return max(s[l][g],s[r-(1<<g)+1][g]);
	}
}

namespace sgt{
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	struct node{
		int l[lb],r[lb],res;
		#define l(x) x.l
		#define r(x) x.r
		#define res(x) x.res
	}t[N<<2],S;
	node mrg(node L,node R,int m){
		res(S)=min(res(L),res(R));
		int cr=0;for(int i=lb-1,nw;~i;--i){
			int r=l(R)[i]<inf?ST::mx(m+1,l(R)[i]):inf,
				l=r(L)[i]?ST::mx(r(L)[i],m):inf;
			nw=max(min(l,r),cr);
			if(v&(1<<i)){
				cr=nw;if((1<<i)==(v&-v)) res(S)=min(res(S),nw);
			}else res(S)=min(res(S),nw);
		}
		for(int i=0;i<lb;++i)
			l(S)[i]=min(l(L)[i],l(R)[i]),r(S)[i]=max(r(L)[i],r(R)[i]);
		return S;
	}
	void set(int u,int p,int x){
		for(int i=0;i<lb;++i) x&(1<<i)?l(t[u])[i]=r(t[u])[i]=p:
			(l(t[u])[i]=inf,r(t[u])[i]=0);
		res(t[u])=x>=v?ST::mx(p,p):inf;
	}
	void build(int now,int ln,int rn){
		if(ln==rn) return set(now,ln,a[ln]);
		int mid=ln+rn>>1;
		build(ls(now),ln,mid);
		build(rs(now),mid+1,rn);
		t[now]=mrg(t[ls(now)],t[rs(now)],mid);
	}
	void upd(int now,int ln,int rn,int p,int x){
		if(ln==rn) return set(now,p,x);
		int mid=ln+rn>>1;
		if(p<=mid) upd(ls(now),ln,mid,p,x);
		else upd(rs(now),mid+1,rn,p,x);
		t[now]=mrg(t[ls(now)],t[rs(now)],mid);
	}
	node qry(int now,int ln,int rn,int l,int r){
		if(l<=ln&&rn<=r) return t[now];
		int mid=ln+rn>>1;bool flg=0;node res;
		if(l<=mid) res=qry(ls(now),ln,mid,l,r),flg=1;
		if(r>mid) S=qry(rs(now),mid+1,rn,l,r),flg?res=mrg(res,S,mid):res=S;
		return res;
	}
}

int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	auto stclock = clock();
	int T;scanf("%d",&T);while(T--){
		int n;scanf("%d%d",&n,&v);
		for(int i=1;i<=n;++i) scanf("%d",a+i);
		ST::build(n);
		for(int i=1;i<=n;++i) scanf("%d",a+i);
		sgt::build(1,1,n);
		int q,f,x,y;scanf("%d",&q);while(q--){scanf("%d%d%d",&f,&x,&y);switch(f){
			case 1:sgt::upd(1,1,n,x,y);break;
			case 2:int r=sgt::qry(1,1,n,x,y).res;printf("%d ",r<inf?r:-1);
		}}puts("");
	}
    auto edclock = clock();
	cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
}
