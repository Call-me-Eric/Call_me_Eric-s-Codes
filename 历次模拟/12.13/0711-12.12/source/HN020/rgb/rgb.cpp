//Code by juju527.
#include<bits/stdc++.h>
typedef long long ll;
#define pii pair<int,int>
#define fi first
#define se second
#define vec vector
#define eb emplace_back
using namespace std;
const int maxn=255,maxm=4e4+5;
map<pii,int> mp;
pii ed[maxm];
int co[maxm];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
char readc(){
	char ch=getchar();
	while(ch!='r'&&ch!='g'&&ch!='b')ch=getchar();
	return ch;
}
vec<int> E1,E2,E3;
int F[maxn];
int find(int x){return (F[x]==x)?x:F[x]=find(F[x]);}
bool merge(pii p){
	int u=find(p.fi),v=find(p.se);
	if(u==v)return 0;
	F[u]=v;
	return 1;
}
vec<pii> e[maxn],t[maxn];
void adde(pii p,int w){e[p.fi].eb(pii(p.se,w)),e[p.se].eb(pii(p.fi,w));return ;}
bool vis[maxn];
int num[5];
bool in[maxm];
void dfs(int x){
	vis[x]=1;
	for(auto p:e[x]){
		int y=p.fi,w=p.se;
		if(!vis[y])dfs(y),t[x].eb(pii(y,w)),t[y].eb(pii(x,w)),num[w]++,in[mp[pii(x,y)]]=1;
	}
	return ;
}
int val[maxn];
int dep[maxn],f[maxn][8];
void dfs1(int x,int fa,int c){
	dep[x]=dep[fa]+1;f[x][0]=fa;
	for(int i=1;i<8;i++)f[x][i]=f[f[x][i-1]][i-1];
	for(auto p:t[x]){
		int y=p.fi,w=p.se;
		if(y==fa)continue;
		val[y]=val[x]+(w>c);
		dfs1(y,x,c);
	}
	return ;
}
void dfs2(int x,int fa,int c){
	dep[x]=dep[fa]+1;f[x][0]=fa;
	for(int i=1;i<8;i++)f[x][i]=f[f[x][i-1]][i-1];
	for(auto p:t[x]){
		int y=p.fi,w=p.se;
		if(y==fa)continue;
		val[y]=val[x]+(w==c);
		dfs2(y,x,c);
	}
	return ;
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=7;i>=0;i--)if(dep[f[x][i]]>=dep[y])x=f[x][i];
	if(x==y)return x;
	for(int i=7;i>=0;i--)if(f[x][i]^f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
void Erase(int u,int v){
	int id=mp[pii(u,v)];in[id]=0;
	t[u].erase(find(t[u].begin(),t[u].end(),pii(v,co[id])));
	t[v].erase(find(t[v].begin(),t[v].end(),pii(u,co[id])));
	num[co[id]]--;
	return ;
}
mt19937 rnd(time(0));
bool deal(vec<int> E,int C){
	for(auto p:E){
		if(in[p])continue;
		int u=ed[p].fi,v=ed[p].se,a=lca(u,v),c=co[p];
		if(val[u]+val[v]-2*val[a]==0)continue;
		in[p]=1;num[c]++;t[u].eb(pii(v,c)),t[v].eb(pii(u,c));
		bool ok=0;
		while(u!=a){
			if(val[u]>val[f[u][0]]){ok=1;Erase(u,f[u][0]);break;}
			u=f[u][0];
		}
		while(v!=a&&!ok){
			if(val[v]>val[f[v][0]]){ok=1;Erase(v,f[v][0]);break;}
			v=f[v][0];
		}
		return 1;
	}
	vec<int> aux(0);
	for(auto p:E)if(!in[p])aux.eb(p);
	if(!aux.size())return 0;
	int id=rnd()%aux.size();
	int p=aux[id],u=ed[p].fi,v=ed[p].se,a=lca(u,v),c=co[p];
	vec<pii> tmp(0);
	while(u!=a){
		if(co[mp[pii(u,f[u][0])]]>=C)tmp.eb(pii(u,f[u][0]));
		u=f[u][0];
	}
	while(v!=a){
		if(co[mp[pii(v,f[v][0])]]>=C)tmp.eb(pii(v,f[v][0]));
		v=f[v][0];
	}
	id=rnd()%tmp.size();
	if(!tmp.size())return 0;
	int U=ed[p].fi,V=ed[p].se;
	in[p]=1;num[c]++;t[U].eb(pii(V,c)),t[V].eb(pii(U,c));
	Erase(tmp[id].fi,tmp[id].se);
	return 0;
}
bool ins(int c){
	dfs1(1,0,c);
	return deal((c==1)?E1:E2,c);
}
int cur=0;
bool del(int c){
//	for(int i=1;i<=13;i++)for(auto p:t[i])cerr<<i<<" "<<p.fi<<endl;
//	cerr<<"##############################"<<c<<endl;
//	cur++;if(cur==7)exit(0);
	dfs2(1,0,c);
//	cerr<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<c<<endl;
//	if(cur==7)exit(0);
	if(c==1){
		if(deal(E2,1))return 1;
		return deal(E3,1);
	}
	return deal(E3,2);
}
int r,g,b,n,m;
void chk(){
	for(int i=1;i<=n;i++)F[i]=i;
	int cnt[5]={0,0,0,0,0};
	for(int i=1;i<=m;i++){
		if(!in[i])continue;
		if(!merge(ed[i])){cerr<<"WA #1!\n";assert(0);}
		cnt[co[i]]++;
	}
	if(!(cnt[1]==r&&cnt[2]==g&&cnt[3]==b)){cerr<<"WA #2!\n";assert(0);}
	return ;
}
int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	r=read(),g=read(),b=read(),m=read();n=r+g+b+1;
	for(int i=1;i<=m;i++){
		int u,v;char c;
		u=read(),v=read();c=readc();
		mp[pii(u,v)]=mp[pii(v,u)]=i;
		ed[i]=pii(u,v);
		if(c=='r')E1.eb(i),co[i]=1;
		else if(c=='g')E2.eb(i),co[i]=2;
		else E3.eb(i),co[i]=3;
	}
	int C;
	C=n;for(int i=1;i<=n;i++)F[i]=i;
	for(auto p:E1)C-=merge(ed[p]);
	if(C>n-r){puts("NO");return 0;}
	C=n;for(int i=1;i<=n;i++)F[i]=i;
	for(auto p:E2)C-=merge(ed[p]);
	if(C>n-g){puts("NO");return 0;}
	C=n;for(int i=1;i<=n;i++)F[i]=i;
	for(auto p:E3)C-=merge(ed[p]);
	if(C>n-b){puts("NO");return 0;}
	for(auto p:E1)adde(ed[p],1);
	for(auto p:E2)adde(ed[p],2);
	for(auto p:E3)adde(ed[p],3);
	dfs(1);
	while(num[1]>r)del(1);
	while(num[1]<r)ins(1);
	while(num[2]>g)del(2);
	while(num[2]<g)ins(2);
	puts("YES");
	for(int i=1;i<=m;i++)printf("%d",in[i]);
	puts("");
	chk();
	return 0;
}
