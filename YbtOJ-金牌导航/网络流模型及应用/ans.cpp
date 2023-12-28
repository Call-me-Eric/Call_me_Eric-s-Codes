#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5050;
const int M=1e9;
ll read(){
	ll x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();};
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int n,m,s,t;
struct node{
	int to,nxt;ll cap;
}p[3000500];
int fi[N],cnt;
void addline(int x,int y,ll cap){
	p[++cnt]=(node){y,fi[x],cap};fi[x]=cnt;
	p[++cnt]=(node){x,fi[y],0};fi[y]=cnt;
}
int col[N],cur[N];
queue<int>q;
int bfs(){
	memset(col,0,sizeof(col));col[s]=1;
	q.push(s);
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int i=cur[now]=fi[now];~i;i=p[i].nxt){
			int to=p[i].to;
			if(col[to]||!p[i].cap) continue;
			col[to]=col[now]+1;
			q.push(to);
		}
	}
	return col[t];
}
ll dfs(int x,ll lim){
	if(x==t||!lim) return lim;
	ll res=0;
	for(int &i=cur[x];~i;i=p[i].nxt){
		int to=p[i].to;
		if(!p[i].cap||col[to]!=col[x]+1) continue;
		ll add=dfs(to,min(lim,p[i].cap));
		lim-=add;res+=add;
		p[i].cap-=add;p[i^1].cap+=add;
		if(!lim) break;
	}
	if(lim) col[x]=-1;
	return res;
}
ll dinic(){
	ll res=0;
	while(bfs()){
		while(ll tmp=dfs(s,2e15)) res+=tmp;
	}
	return res;
}
int vis[N];
void find1(int x){
	if(vis[x]) return;
	vis[x]=1;
	for(int i=fi[x];~i;i=p[i].nxt){
		if(!p[i].cap) continue;
		find1(p[i].to);
	}
	return;
}
void find2(int x){
	if(vis[x]) return;
	vis[x]=2;
	for(int i=fi[x];~i;i=p[i].nxt){
		if(!p[i^1].cap) continue;
		find2(p[i].to);
	}
	return;
}
#define id(x,y) ((x-1)*m+y)
int num,x,tot;
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};
inline bool exi(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
int a[55][55],mx[2505];
struct tower{
	int x,y,op;
	int mx,xx,yy;
}o[2505];
#define heng(x,y) ((x-1)*m+y)
#define shu(x,y) ((x-1)*m+y+n*m)
int main(){
	memset(fi,-1,sizeof(fi));cnt=-1;
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			x=read();
			if(x>=0) a[i][j]=x;
			else{
				x=-x;
				o[++num]=(tower){i,j,x,0,i,j};
			}
		}
	}//printf("ok");
	for(int i=1;i<=num;i++){
		int x=o[i].x,y=o[i].y,op=o[i].op;
		while(x>=1&&x<=n&&y>=1&&y<=m){
			x+=dx[op];y+=dy[op];
			if(a[x][y]>o[i].mx){
				o[i].mx=a[x][y];
				o[i].xx=x;o[i].yy=y;
			}
		}
		tot+=o[i].mx;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) addline(heng(i,j),shu(i,j),2e15);
	}
	s=2*n*m+1;t=s+1;
	for(int i=1;i<=num;i++){
		int x=o[i].x,y=o[i].y,op=o[i].op;
		int xx=o[i].xx,yy=o[i].yy,mx=o[i].mx;
		//a[x][y]=2e9;
		if(op<=2){
			addline(shu(x,y),t,2e15);
			while(xx!=x||yy!=y){
			//	printf("(%d %d)->(%d %d) len=%d\n",xx,yy,xx-dx[op],yy-dy[op],a[xx-dx[op]][yy-dy[op]]);
				addline(shu(xx,yy),shu(xx-dx[op],yy-dy[op]),mx-a[xx-dx[op]][yy-dy[op]]);
				xx-=dx[op];yy-=dy[op];
			}
		}
		else{
			addline(s,heng(x,y),2e15);
			while(x!=xx||y!=yy){
			//	printf("(%d %d)->(%d %d) len=%d\n",x,y,x+dx[op],y+dy[op],a[x][y]);
				addline(heng(x,y),heng(x+dx[op],y+dy[op]),mx-a[x][y]);
				x+=dx[op];y+=dy[op];
			}
		}
	}
	printf("%lld\n",tot-dinic());
    return 0;
}
/*
3 2 1 3
1 2 10
2 3 10
*/

