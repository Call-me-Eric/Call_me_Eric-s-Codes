#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){int ch=getchar(),x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e5+5,inf=1e9;
int n,q,K,a[N],son[N],mn1[N],mn2[N],mn3[N],dep[N],fa[N][20],fa_[N][20];
vector<int> e[N];

inline int F(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	int k=fa[x][1];
	if(dep[x]==dep[y]){
		if(a[fa[x][0]]>a[fa[x][1]]) swap(x,y);
		if(mn1[k]==a[fa[x][0]]){
			if(mn2[k]==a[fa[y][0]]) re min(a[fa[k][0]],mn3[k]);
			re min(a[fa[k][0]],mn2[k]);
		}
		re min(a[fa[k][0]],mn1[k]);
	}
	if(mn1[k]==a[fa[x][0]]) re mn2[k];
	re mn1[k];
}

struct Node{
	ll a[3][3];
	int len;
	Node(){memset(a,0x3f,sizeof a);len=0;}
	Node operator+(const Node &X){
		Node ret;ret.len=X.len+len;
		fo(i,0,K)	
			fo(j,0,K)
				fo(w,0,K-j)
					fo(t,0,K) sml(ret.a[i][t],a[i][j]+X.a[w][t]);
		if(len<=K)
			fo(i,0,K-len) fo(j,0,K) sml(ret.a[i+len][j],X.a[i][j]);
		if(X.len<=K)
			fo(i,0,K) fo(j,0,K-X.len) sml(ret.a[i][j+X.len],a[i][j]);
		re ret;
	}
	void rev(){fo(i,0,K) fo(j,i+1,K) swap(a[i][j],a[j][i]);}
}f[N][19],f_[N][19];
int lg;

void dfs1(int x){
	dep[x]=dep[fa[x][0]]+1;
	fa_[x][0]=x;
	fo(i,1,lg){
		fa[x][i]=fa[fa[x][i-1]][i-1];
		fa_[x][i]=fa[fa_[x][i-1]][i-1];
	}
	f[x][0].a[0][0]=a[x];f[x][0].len=1;
	mn1[x]=mn2[x]=mn3[x]=inf;
	for(int i:e[x]) if(i!=fa[x][0]){
		fa[i][0]=x;
		dfs1(i);
		if(a[i]<mn1[x]) son[x]=i,mn3[x]=mn2[x],mn2[x]=mn1[x],mn1[x]=a[i];
		else if(a[i]<mn2[x]) mn3[x]=mn2[x],mn2[x]=a[i];
		else sml(mn3[x],a[i]);
	}
	f[x][0].a[1][1]=mn1[x];
	f_[x][0]=f[x][0];f_[x][0].a[1][1]=mn2[x];
}

void dfs2(int x){
	fo(i,1,lg){
		if(fa_[x][i-1]==son[fa[x][i-1]]){
			f[x][i]=f[x][i-1]+f_[fa[x][i-1]][i-1];
			f_[x][i]=f_[x][i-1]+f_[fa[x][i-1]][i-1];
		}else{
			f[x][i]=f[x][i-1]+f[fa[x][i-1]][i-1];
			f_[x][i]=f_[x][i-1]+f[fa[x][i-1]][i-1];			
		}	
	}
	for(int i:e[x]) if(i!=fa[x][0]) dfs2(i);
}

inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	go(i,lg,0) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) re x;
	go(i,lg,0) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	re fa[x][0];
}

void file(){
	freopen("transmit.in","r",stdin);
	freopen("transmit.out","w",stdout);
}

signed main(){
	memset(a,0x3f,sizeof a);
	cin>>n>>q>>K;
	fo(i,1,n) a[i]=read();
	fo(i,2,n){
		int x=read(),y=read();
		e[x].pb(y),e[y].pb(x); 
	}
	K--;
	lg=(int)log2(n);
	dfs1(1);
	dfs2(1);
	while(q--){
		int x=read(),y=read(),X=x,Y=y,k=lca(x,y);
		if(x==y){
			cout<<a[x]<<'\n';
			co;
		}
		if(dep[x]<dep[y]) swap(x,y);
		Node Ax,Ay;
		int flg=1;
		go(i,lg,0) if(dep[fa[x][i]]>=dep[k]){
			if(X!=son[x]) Ax=Ax+f[x][i];
			else Ax=Ax+f_[x][i];
			x=fa[x][i];
			if(flg) X=fa_[X][i],flg=0;
			else X=fa[X][i];
		}
		flg=1;
		go(i,lg,0) if(dep[fa[y][i]]>=dep[k]){
			if(Y!=son[y]) Ay=Ay+f[y][i];
			else Ay=Ay+f_[y][i];
			y=fa[y][i];
			if(flg) Y=fa_[Y][i],flg=0;
			else Y=fa[Y][i];	
		}
		Ay.rev();
		Node ans;ans.len=1;ans.a[0][0]=a[k];
		if(a[X]>a[Y]) swap(X,Y);
		if(X==son[k]){
			if(y!=k&&a[Y]==mn2[k]) ans.a[1][1]=min(mn3[k],a[fa[k][0]]);
			else ans.a[1][1]=min(mn2[k],a[fa[k][0]]);
		}else ans.a[1][1]=min(mn1[k],a[fa[k][0]]);
		ans=Ax+ans;
		ans=ans+Ay;
		cout<<ans.a[0][0]<<'\n';
	}
	return 0;
}
