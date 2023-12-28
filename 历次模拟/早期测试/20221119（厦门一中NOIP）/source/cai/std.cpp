#include<bits/stdc++.h>
#define N 100010
#define GC getchar()
#define ll long long
using namespace std;
ll re(){
	ll s=0,b=1; char c=GC;
	while(c>'9'||c<'0'){if(c=='-')b=-b; c=GC;}
	while(c<='9'&&c>='0'){s=(s<<1)+(s<<3)+(c^48); c=GC;}
	return s*b;
}
int n,q,x,y,he[N],tt,de[N],si[N],so[N],df[N],od,tp[N],an[N],fq[N];
ll tr[N<<2];
struct A{int ne,to;}b[N<<1];
struct B{ll p,v; int w;}cc[N];
struct C{int st,la,w;  ll v;}xw[N];
bool cmB(B x,B y){return x.p<y.p;}
void ad(){
	b[++tt].to=y; b[tt].ne=he[x]; he[x]=tt;
	b[++tt].to=x; b[tt].ne=he[y]; he[y]=tt;
}
void dfs(int x,int f){
	de[x]=de[f]+1; si[x]++; fq[x]=f;
	for(int i=he[x]; i; i=b[i].ne){
		int v=b[i].to; if(v==f)continue;
		dfs(v,x); si[x]+=si[v];
		if(si[v]>si[so[x]]) so[x]=v;
	}
}
void dft(int x,int to){
	df[x]=++od; tp[x]=to;
	if(!so[x])return; dft(so[x],to);
	for(int i=he[x]; i; i=b[i].ne){
		int v=b[i].to;
		if(v==fq[x]||v==so[x])continue;
		dft(v,v);
	}
}
void xg(int X,ll z){
	while(X<=n){tr[X]+=z; X+=(X&(-X));}
}
ll csu(int L,int R){
	ll s=0;
	int X=R;
	while(X){s+=tr[X]; X-=(X&(-X));}
	X=L-1;
	while(X){s-=tr[X]; X-=(X&(-X));}
	return s;
}
ll cz(int x,int y){
	ll S=0;
	while(tp[x]!=tp[y]){
		if(de[tp[x]]<de[tp[y]])swap(x,y);
		S+=csu(df[tp[x]],df[x]); x=fq[tp[x]];
	}
	if(de[x]>de[y])swap(x,y);
	S+=csu(df[x],df[y]);
	return S; 
}
void sol(int cl,int cr,int ql,int qr){
	if(cl==cr){
		if(cl==n){
			xg(df[cc[n].w],cc[n].v);
			for(int i=ql; i<=qr; i++)
			 if(cz(xw[i].la,xw[i].st)>=xw[i].v)an[xw[i].w]=cc[n].p;
			  else an[xw[i].w]=-1;
			xg(df[cc[n].w],-cc[n].v);
		}else for(int i=ql; i<=qr; i++)an[xw[i].w]=cc[cl].p;
		return;
	} int mi=(cl+cr)>>1,fj=ql-1;
	for(int i=cl; i<=mi; i++)
	 xg(df[cc[i].w],cc[i].v);
	for(int i=ql; i<=qr; i++)
	 if(cz(xw[i].la,xw[i].st)>=xw[i].v) swap(xw[++fj],xw[i]);
	if(fj<qr)sol(mi+1,cr,fj+1,qr);
	for(int i=cl; i<=mi; i++)
	 xg(df[cc[i].w],-cc[i].v);
	if(fj>=ql)sol(cl,mi,ql,fj);
}
int main(){
	freopen("war1.in","r",stdin);
	freopen("std.out","w",stdout);
	n=re(),q=re();
	for(int i=1; i<n; i++){
		x=re(),y=re(); ad();
	} dfs(1,0); dft(1,1);
	for(int i=1; i<=n; i++){
		cc[i].p=re(),cc[i].v=re(); cc[i].w=i;
	} sort(cc+1,cc+n+1,cmB);
	for(int i=1; i<=q; i++){
		xw[i].la=re(),xw[i].st=re();
		xw[i].v=re(); xw[i].w=i;
	}
	sol(1,n,1,q);
	for(int i=1; i<=q; i++)
	 if(an[i]==-1)cout<<"Impossible"<<endl;
	  else cout<<an[i]<<endl;
} 
