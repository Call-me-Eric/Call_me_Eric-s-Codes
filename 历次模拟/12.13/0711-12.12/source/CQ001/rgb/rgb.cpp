#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=255,M=N*N;
int n,m,A[3],B[3];
int lim[3],e[N][N];
map<char,int> mp;char s[3];
int fa[N];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
int U[M],V[M],C[M];
struct dsu{
	int fa[N];
	void init(){For(i,1,n)fa[i]=i;}
	int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
	bool qry(int x,int y){return get(x)==get(y);}
	bool merge(int x,int y){
		x=get(x),y=get(y);
		if(x==y)return 0;
		fa[x]=y;return 1;
	}
}D[3];
int tmp[N];
void calcB(){
	For(i,1,n)tmp[i]=fa[i];
	For(c,0,2){
		B[c]=0;For(i,1,n)fa[i]=tmp[i];
		For(i,1,m)if(C[i]==c&&get(U[i])!=get(V[i]))fa[get(U[i])]=get(V[i]),B[c]++;
	}For(i,1,n)fa[i]=tmp[i];
}
bitset<N> vis,G[3][N],Tmp[N];
void dfs(int u,int ban){
	vis[u]=1;
	Tmp[u]=G[ban][u]&(~vis);
	for(int v=Tmp[u]._Find_first();v<=n;v=Tmp[u]._Find_next(v))dfs(v,ban);
}
void calcA(){
	For(c,0,2){
		A[c]=-1,vis.reset();
		For(i,1,n)if(!vis[i])dfs(i,c),A[c]++;
	}
	
}
int oo[N];
int used[M];
signed main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	mp['r']=0,mp['g']=1,mp['b']=2;
	memset(e,-1,sizeof e);n=1;
	For(i,0,2)lim[i]=read(),n+=lim[i];m=read();
	int r=lim[0],g=lim[1],b=lim[2];
	fprintf(stderr,"n = %d, m = %d, r = %d, g = %d, b = %d\n",n,m,r,g,b);
	For(i,1,m){
		int u=read(),v=read();scanf("%s",s);
		e[u][v]=e[v][u]=mp[s[0]];
		U[i]=u,V[i]=v,C[i]=mp[s[0]];
		For(c,0,2)if(c!=C[i])G[c][u][v]=G[c][v][u]=1;
		//if(C[i]==0)printf("(%d, %d)\n",u,v);
	}For(i,1,n)fa[i]=i;
	int flag=1;calcA();calcB();
	For(c,0,2)flag&=(A[c]<=lim[c]&&lim[c]<=B[c]);
	if(!flag)return puts("No"),0;puts("YES");
	For(c,0,2)D[c].init();
	For(i,1,m)D[C[i]].merge(U[i],V[i]);
	For(i,1,n)fa[i]=i;
	For(i,1,m){
		int u=U[i],v=V[i],c=e[u][v];
		if(lim[c]&&get(u)!=get(v)){
			e[u][v]=e[v][u]=3;
			For(i,1,n)oo[i]=fa[i];fa[get(u)]=get(v);
			lim[c]--,B[c]--;
			assert(!G[c][u][v]);
			G[c][u][v]=G[c][v][u]=1;
			calcA();
			For(cc,0,2)if(cc!=c)B[cc]-=D[cc].qry(u,v);
			//calcB();
			flag=1;For(c,0,2)flag&=(A[c]<=lim[c]&&lim[c]<=B[c]);
			if(flag){
				putchar('1'),used[i]=1;
				For(c,0,2)D[c].merge(u,v);
			}else{
				putchar('0'),e[u][v]=e[v][u]=c,lim[c]++,B[c]++;
				For(i,1,n)fa[i]=oo[i];
				For(cc,0,2)if(cc!=c)B[cc]+=D[cc].qry(u,v);
				G[c][u][v]=G[c][v][u]=0;
			}
		}else putchar('0');
	}puts("");
	vector<int> cnt(3,0);
	For(i,1,n)fa[i]=i;int ecnt=0;
	For(i,1,m)if(used[i]){
		ecnt++;
		assert(get(U[i])!=get(V[i]));
		fa[get(U[i])]=get(V[i]);
		cnt[C[i]]++;	
	}
	assert(ecnt==n-1);
	assert(cnt[0]==r);
	assert(cnt[1]==g);
	assert(cnt[2]==b);
	return 0;
}
