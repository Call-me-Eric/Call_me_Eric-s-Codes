#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+7;
int n,m;
namespace splay
{
	struct node 
	{
		int s[2];
		int fa;
		int tag;
		#define tag(x) tr[x].tag
		#define l(x) tr[x].s[0]
		#define r(x) tr[x].s[1]
		#define fa(x) tr[x].fa
	}tr[N];
	void rev(int x)
	{
		if(!x)return;
		swap(l(x),r(x));
		tag(x)^=1;
	}
	void down(int x)
	{
		if(tag(x))
		{
			rev(l(x));
			rev(r(x));
			tag(x)^=1;
		}
	}
	bool isroot(int x)
	{
		return l(fa(x))!=x&&r(fa(x))!=x; 
	}
	void rotate(int x)
	{
		int y=fa(x),z=fa(y);
		int a=(r(y)==x),b=(r(z)==y);
		if(!isroot(y))tr[z].s[b]=x;fa(x)=z;
		tr[y].s[a]=tr[x].s[a^1];fa(tr[x].s[a^1])=y;
		tr[x].s[a^1]=y;fa(y)=x;
	}
	int stk[N],top=0;
	void spread(int x)
	{
		stk[++top]=x;
		while(!isroot(x))x=fa(x),stk[++top]=x;
		while(top)down(stk[top--]);
	}
	void splay(int x)
	{
		spread(x);
		while(!isroot(x))
		{
			int y=fa(x),z=fa(y);
			if(!isroot(y))
			{
				if((r(y)==x)!=(r(z)==y))rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
	}
	int access(int x)
	{
		int y=0,r=x;
		for(;x;y=x,x=fa(x))
		{
			splay(x);
			r(x)=y;
		}
		splay(r);
		return y;
	}
	void makeroot(int x)
	{
		access(x);
		rev(x);
	}
	void link(int x,int y)
	{
		makeroot(x);
		fa(x)=y;
	}
	void cut(int x,int y)
	{
		makeroot(x);
		access(y);
		fa(x)=l(y)=0;
	}
	int lca(int x,int y)
	{
		makeroot(1);
		access(x);
		return access(y);
	}
}
typedef double db;
const db alpha = 0.8;
db w[N];
namespace treap
{
	struct node
	{
		int l,r;
		int siz;
		#define siz(x) tr[x].siz
		#define ls(x) tr[x].l
		#define rs(x) tr[x].r
	}tr[N];
	int seq[N],tot=0;
	void flatten(int x)
	{
		if(!x)return;
		flatten(ls(x));
		seq[++tot]=x;
		flatten(rs(x));
	}
	void pushup(int x)
	{
		siz(x)=siz(ls(x))+siz(rs(x))+1;
	}
	int rebuild(int l,int r,db L,db R)
	{
		if(l>r)return 0;
		int mid=(l+r)>>1;
		int x=seq[mid];
		db M=(L+R)/2.0;
		w[x]=M; 
		ls(x)=rebuild(l,mid-1,L,M);
		rs(x)=rebuild(mid+1,r,M,R);
		pushup(x);
		return x; 
	}
	void build(int &x,db L,db R)
	{
		if(max(siz(ls(x)),siz(rs(x)))>=siz(x)*alpha) 
		{
			tot=0;
			flatten(x);
			x=rebuild(1,tot,L,R);
		}
	}
	void ins(int &x,int rnk,int p,db L,db R)
	{
		//if(L==0)printf("ins(%d,%d,%d)\n",x,rnk,p);
		db M=(L+R)/2.0;
		if(!x)
		{
			x=p;
			w[x]=M;
			siz(x)=1;
			return;
		}
		if(siz(ls(x))+1<=rnk) ins(rs(x),rnk-siz(ls(x))-1,p,M,R);
		else ins(ls(x),rnk,p,L,M);
		pushup(x);
		build(x,L,R);
	}
	int root=0;
	int rnk(int x,int p)
	{
		if(x==p)return siz(ls(x))+1;
		if(w[x]<w[p]) return rnk(rs(x),p)+siz(ls(x))+1;
		return rnk(ls(x),p);
	}
}
namespace segment
{
	int lp[N*4],rp[N*4];
	inline int Min(int x,int y){if(!x||!y)return x+y;return w[x]<w[y]?x:y;}
	inline int Max(int x,int y){if(!x||!y)return x+y;return w[x]>w[y]?x:y;}
	void pushup(int k)
	{
		lp[k]=Min(lp[k<<1],lp[k<<1|1]);
		rp[k]=Max(rp[k<<1],rp[k<<1|1]);
	}
	void upd(int k,int l,int r,int x)
	{
		if(l==r)
		{
			lp[k]=rp[k]=x;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)upd(k<<1,l,mid,x);
		else upd(k<<1|1,mid+1,r,x);
		pushup(k);
	}
	void query(int k,int l,int r,int L,int R,int &p,int &q)
	{
		if(L<=l&&r<=R)
		{
			p=Min(p,lp[k]);
			q=Max(q,rp[k]);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid)query(k<<1,l,mid,L,R,p,q);
		if(R>mid)query(k<<1|1,mid+1,r,L,R,p,q);
	}
}
int T;
int fa[N];struct IO{
    static const int S=1<<21;
    char buf[S],*p1,*p2;int st[105],Top;
    ~IO(){clear();}
    inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
    inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
    template<typename T>inline IO&operator >> (T&x){
        x=0;bool f=0;char ch=gc();
       while(!isdigit(ch)){if(ch=='-') f^=1;ch=gc();}
        while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
        f?x=-x:0;return *this;
    }
    inline IO&operator << (const char c){pc(c);return *this;}
    template<typename T>inline IO&operator << (T x){
        if(x<0) pc('-'),x=-x;
        do{st[++st[0]]=x%10,x/=10;}while(x);
        while(st[0]) pc('0'+st[st[0]--]);return *this;
    }
}fin,fout;
int main()
{
	freopen("summer.in","r",stdin);
	freopen("summer.out","w",stdout);
	fin>>n>>T;n++;
	treap::ins(treap::root,0,1,0,1e18);
	segment::upd(1,1,n,1);
	int lst=0;
	for(int i=2;i<=n;i++)
	{
		int op,a,b;
		fin>>op>>a>>b;
		a=a^(lst*T);b=b^(lst*T);
		//printf("%d===\n",i);
		if(op==1) 
		{
			fa[a]=b;
			splay::link(a,b);
			treap::ins(treap::root,treap::rnk(treap::root,b),a,0,1e18);
			segment::upd(1,1,n,a);
		}
		else if(op==2)
		{
			int x=fa[b];
			fa[b]=a;fa[a]=x;
			splay::cut(b,x);
			splay::link(b,a);
			splay::link(a,x);
			treap::ins(treap::root,treap::rnk(treap::root,b)-1,a,0,1e18);
			segment::upd(1,1,n,a);
		}
		else 
		{
			int l=a,r=b;
			int p=0,q=0;
			segment::query(1,1,n,l,r,p,q);
			//cout<<p<<' '<<q<<endl;
			if(p+q==0)fout<<-1,lst=0;
			else
			{
				lst=splay::lca(p,q);
				fout<<lst;
			}
			fout.pc('\n');
		}
		//for(int j=1;j<=n;j++)printf("w(%d)=%.0lf l(%d)=%d,r(%d)=%d\n",j,w[j],j,treap::ls(j),j,treap::rs(j));printf("\n");
	}
	return 0;
}
