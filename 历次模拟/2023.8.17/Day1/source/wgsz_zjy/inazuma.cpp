#include<bits/stdc++.h>
#define F(i0,i1,i2) for(int i0=i1;i0<=i2;++i0)
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
using namespace std;
const int N=5e3+7;
inline int rd(){
	int f=0,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return f?-x:x;
}
int ed[N][N];
int n,m;
int vis[N],inr[N];
int ans=INT_MAX;
struct Id{
	int v,w,nt;
}e[N<<1];
int p[N],id=1;
void add(int x,int y,int z){e[++id]={y,z,p[x]};p[x]=id;}
void dfs(int x,int ffa){
	for(int i=p[x];i;i=e[i].nt){
		int v=e[i].v;if(v==ffa||vis[N])continue;
		ans=min(ans,e[i].w);
		vis[v]=1;
		dfs(v,x);
	}
}
int d[N];
void Topo(){
	queue<int>q;
	F(i,1,n)if(d[i]==2)q.push(i),d[i]-=2;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=p[u];i;i=e[i].nt){
			int v=e[i].v;
			d[v]-=2;
			if(d[v]==2)q.push(v);
		}
	}
	F(i,1,n){
		if(d[i]){
			inr[i]=1;
		}	
	}
}
signed main(){
	freopen("inazuma.in","r",stdin);
	freopen("inazuma.out","w",stdout);
	n=rd(),m=rd();
	F(i,1,m){
		int x=rd(),y=rd(),z=rd();
		ed[x][y]=ed[y][x]=ed[x][y]+z;
	}
	F(i,1,n){
		F(j,1,n){
			if(ed[i][j]){
				add(i,j,ed[i][j]);
				add(j,i,ed[i][j]);
				ed[i][j]=ed[j][i]=0;
				d[i]+=2;
				d[j]+=2;
			}
		}
	}
	Topo();
//	dfs(1,0);
//	cout<<ans<<'\n';
	return 0;
}

