#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,r,g,b;
bool vis[100001];
struct ale{
	int x,y,c;
}a[100001];
int cr,cg,cb;
int rc[100001],gc[100001],bc[100001];
int fa[100001],cc[100001],nc[100001];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void cs(int x,int y){
	if(x>y)swap(x,y);
	int i;
	for(i=1;i<=n;i++){
		if(a[i].c==x)a[i].c=y;
		else if(a[i].c==y)a[i].c=x;
	}
	for(i=1;i<=n;i++){
		if(x&&y)swap(gc[i],bc[i]);
		else if(y==1)swap(rc[i],gc[i]);
		else swap(rc[i],bc[i]);
	}
	if(x&&y)swap(g,b),swap(cg,cb);
	else if(y==1)swap(r,g),swap(cr,cg);
	else swap(r,b),swap(cr,cb);
}
void init(){
	char c;
	int i,w=0;
	scanf("%d%d%d%d",&r,&g,&b,&m);
	n=r+g+b+1;
	for(i=1;i<=m;i++){
		int x,y,cl;
		scanf("%d%d %c",&x,&y,&c);
		if(c=='r')cl=0;
		else if(c=='g')cl=1;
		else cl=2;
		a[i]={x,y,cl};
		if(cl==0)rc[++cr]=i;
		if(cl==1)gc[++cg]=i;
		if(cl==2)bc[++cb]=i;
	}
	for(i=1;i<=n;i++)fa[i]=i;
	for(i=1;i<=m;i++){
		if(w==n-1)break;
		int x=find(a[i].x),y=find(a[i].y);
		if(x==y)continue;
		fa[y]=x;w++;
		cc[w]=i;vis[i]=1;
		if(a[i].c==0)r--;
		if(a[i].c==1)g--;
		if(a[i].c==2)b--;
	}
	r*=-1;g*=-1;b*=-1;
}
int hed[251],net[501],ver[501],e[501],tot;
void add(int x,int y,int z){
	ver[++tot]=y;
	e[tot]=z;
	net[tot]=hed[x];
	hed[x]=tot;
}
int fr[251],dep[251],tc[251];
void dfs(int x){
	int i;
	dep[x]=dep[fr[x]]+1;
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(y==fr[x])continue;
		fr[y]=x;
		tc[y]=e[i];
		dfs(y);
	}
}
void build(bool re){
	int i,j;
	for(i=1;i<=n;i++)hed[i]=0;tot=0;
	for(i=1;i<n;i++)vis[cc[i]]=0;
	if(re)for(i=1;i<n;i++)nc[i]=cc[i];
	for(i=1;i<n;i++){
		int d=nc[i];vis[d]=1;
		add(a[d].x,a[d].y,d);
		add(a[d].y,a[d].x,d);
	}
	dfs(1);
}
bool replace(int d,int cl){
	int x=a[d].x,y=a[d].y;
	int i,rpd=0;
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]!=dep[y]){
		if(a[tc[x]].c==cl){
			rpd=tc[x];
			break;
		}
		x=fr[x];
	}
	while(x!=y){
		if(a[tc[x]].c==cl){
			rpd=tc[x];
			break;
		}
		if(a[tc[y]].c==cl){
			rpd=tc[y];
			break;
		}
		x=fr[x];y=fr[y];
	}
	if(!rpd)return 0;
	bool mt=0;cc[n]=d;
	for(i=1;i<n;i++){
		if(cc[i]==rpd)mt=1;
		cc[i]=cc[i+mt];
	}
	vis[rpd]=0;
	vis[d]=1;
	build(0);
	return 1;
}
bool solve(int x,int y,int ts){
	if(ts<0)swap(x,y),ts*=-1;
	int i;
	for(i=1;i<=m&&ts;i++){
		int d;
		if(y==0)d=rc[i];
		if(y==1)d=gc[i];
		if(y==2)d=bc[i];
		if(!d)break;
		if(vis[d])continue;
		if(replace(d,x))ts--;
	}
	return !ts;
}
int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	init();
	int i,j;
	if(!r&&!g&&!b){
		printf("YES\n");
		for(i=1;i<=m;i++)printf("%d",vis[i]);
		return 0;
	}
	if(r>=0){
		if(g<0)cs(0,1);
		else cs(0,2);
	}
	if(g>b)cs(1,2);
	if(r>g)cs(0,1);
	bool sl=0;
	for(i=-n;i<=n;i++){
		build(1);
		if(!solve(0,1,i))continue;
		int tr=r-i,tg=g+i,tb=b;
		if(!solve(0,2,tr))continue;
		tb+=tr;
		if(!solve(1,2,tg))continue;
		sl=1;break;
	}
	if(!sl)printf("NO\n");
	else{
		printf("YES\n");
		for(i=1;i<=m;i++)printf("%d",vis[i]);
	}
}
