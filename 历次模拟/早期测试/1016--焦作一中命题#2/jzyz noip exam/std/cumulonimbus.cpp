#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
template<typename _T>inline void read(_T &x){
	x=0;static char c;c=getchar(); bool f=0; 
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=x*10+(c^48);
	x=(f)?(-x):x;
}
const int N = 5e5+7;
struct edge
{
	int y,next;
}e[2*N];
int link[N],t=0;
int n,m,q;
int deg[N];
void add(int x,int y)
{
	deg[x]++;
	e[++t].y=y;
	e[t].next=link[x];
	link[x]=t;
}
int K;
int p[N],pos[N];
namespace task1
{
	vector<int> V[N];
	vector<int> Id[N];
	int ans[N],L[N],R[N]; 
	int c[N];
	void upd(int x)
	{
		for(int i=x;i<=n;i+=i&-i)
		c[i]++;
	}
	int ask(int x)
	{
		int res=0;
		for(int i=x;i;i-=i&-i)
		res+=c[i];
		return res;
	}
	void solve()
	{
		for(int x=1;x<=n;x++)
		for(int i=link[x];i;i=e[i].next)
		{
			int y=e[i].y;
			int l=pos[x],r=pos[y];
			if(l>r)swap(l,r);
			V[r].push_back(l);
		}
		for(int i=1;i<=q;i++)
		{
			read(L[i]);read(R[i]);
			Id[R[i]].push_back(i);
		}
		for(int i=1;i<=n;i++)
		{
			for(auto l:V[i])
			upd(l);
			for(auto x:Id[i])
			{
				int l=L[x];
				ans[x]+=ask(i)-ask(l-1);
			}
		}
		for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
		exit(0);
	}
}
struct Query
{
	int l,r;
	int id;
}Q[N];
int bel[N],B;
inline bool cmp(Query x,Query y)
{
	if(bel[x.l]!=bel[y.l]) return x.l<y.l;
	if(bel[x.l]&1) return x.r<y.r;
	return x.r>y.r;
}
#define UI unsigned int 
UI ans[N],f[N];
UI ext[N];struct IO{
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
namespace task2
{
	inline void upd(int x,int v)
	{
		for(int i=link[x];i;i=e[i].next)
		{
			int y=e[i].y;
			f[y]+=v;
		}
	}
	inline UI ask(int x)
	{
		UI res=0;
		for(int i=link[x];i;i=e[i].next)
		{
			int y=e[i].y;
			res+=f[y];
		}
		return res;
	}
	void solve()
	{
		int L=1,R=0;
		UI cur=0;
		for(int i=1;i<=n;i++)
		{
			int x=p[i];
			upd(x,1);
			ext[i]=ask(x);
			upd(x,-1);
			ext[i]+=ext[i-1]; 
		}
		for(int i=1;i<=q;i++)
		{
			int l=Q[i].l,r=Q[i].r,id=Q[i].id;
			while(R<r)  
			{
				int x=p[++R];
				cur+=ask(x);
				upd(x,1);
			}
			while(L>l)
			{
				int x=p[--L];
				cur+=ask(x);
				upd(x,1);
			}
			while(R>r)
			{
				int x=p[R--];
				upd(x,-1);
				cur-=ask(x);
			}
			while(L<l)
			{
				int x=p[L++];
				upd(x,-1);
				cur-=ask(x);
			}
			ans[id]=(UI)cur*2+ext[r]-ext[l-1];
		}
		for(int i=1;i<=q;i++)
		{
			fout<<ans[i];
			fout.pc('\n'); 
		}
		exit(0);
	}
}
bool hea[N];
int S;
UI tag[N];
vector<int> G[N];
int tot=0;
void sol(int x,int v)
{
	if(hea[x])
	{
		tag[x]+=v;
		return;
	}
	for(int i=link[x];i;i=e[i].next)
	{
		tot++;
		int y=e[i].y;
		f[y]+=v;
	}
}
void upd(int x,int v)
{
	for(int i=link[x];i;i=e[i].next)
	sol(e[i].y,v);
}
UI get(int x)
{
	UI res=f[x];
	for(auto y:G[x])
	res+=tag[y];
	return res;
}
UI ask(int x)
{
	UI res=0;
	for(int i=link[x];i;i=e[i].next)
	{
		int y=e[i].y;
		res+=get(y);
	}	
	return res;
}
UI pre[N][2];
struct tube
{
	int id;
	int l,r;
	int opt;
};
vector<tube> P[N];

int main()
{
	freopen("cumulonimbus.in","r",stdin);
	freopen("cumulonimbus.out","w",stdout);
	read(n);read(m);read(q);read(K);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		read(u);read(v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)
	read(p[i]),pos[p[i]]=i;
	if(K==2) task1::solve();
	B=1200;
	int cnt=0,sum=0;
	for(int i=1;i<=n;i++)
	{
		int x=p[i];
		if(sum+deg[x]>=B) bel[i]=++cnt,sum=deg[x];
		else sum+=deg[x],bel[i]=cnt;
	}
	for(int i=1;i<=q;i++)
	{
		int l,r;
		read(l);read(r);
		Q[i]=(Query){l,r,i};
	}
	sort(Q+1,Q+q+1,cmp);
	if(K==3) task2::solve();
	int L=1,R=0;
	S=pow(m,0.4);
	cnt=0;
	for(int i=1;i<=n;i++)
	if(deg[i]>=S) hea[i]=1,cnt++;
	for(int x=1;x<=n;x++)
	for(int i=link[x];i;i=e[i].next)
	{
		int y=e[i].y;
		if(hea[y]) G[x].push_back(y);
	}	
	for(int i=1;i<=n;i++)
	{
		int x=p[i];
		upd(x,1);
		ext[i]=ask(x);
		upd(x,-1);
		ext[i]+=ext[i-1];
	}
	for(int i=1;i<=n;i++)
	{
		pre[i][0]=ask(p[i])+pre[i-1][0];
		upd(p[i],1);
		pre[i][1]=ask(p[i])+pre[i-1][1];
	}
	for(int i=1;i<=n;i++)
	upd(p[i],-1);
	for(int i=1;i<=q;i++)
	{
		int l=Q[i].l,r=Q[i].r,id=Q[i].id;
		if(R<r)
		{
			ans[id]+=pre[r][0]-pre[R][0];
			P[L-1].push_back((tube){id,R+1,r,-1});
			R=r;
		}
		if(L>l)
		{
			ans[id]-=pre[L-1][1]-pre[l-1][1];
			P[R].push_back((tube){id,l,L-1,1});
			L=l;
		}
		if(R>r)
		{
			ans[id]-=pre[R][0]-pre[r][0];
			P[L-1].push_back((tube){id,r+1,R,1});
			R=r;
		}
		if(L<l)
		{
			ans[id]+=pre[l-1][1]-pre[L-1][1];
			P[R].push_back((tube){id,L,l-1,-1});
			L=l;
		}
	}
	for(int o=1;o<=n;o++)
	{
		int x=p[o];
		upd(x,1);
		for(auto U:P[o])
		{
			int id=U.id,l=U.l,r=U.r,opt=U.opt;
			for(int i=l;i<=r;i++)
			ans[id]+=ask(p[i])*opt;
		}
	}
	for(int i=1;i<=q;i++)
	ans[Q[i].id]+=ans[Q[i-1].id];
	for(int i=1;i<=q;i++)
	{
		int l=Q[i].l,r=Q[i].r,id=Q[i].id;
		ans[id]=(UI)ans[id]*2+ext[r]-ext[l-1];
	}
	for(int i=1;i<=q;i++)
	{
		fout<<ans[i];
		fout.pc('\n');
	}
	return 0;
}

