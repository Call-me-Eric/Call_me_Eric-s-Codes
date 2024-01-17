#include<iostream>
#include<cstdio>
#define eps 1e-2
#define erg(G,x,i) for(int i=G.head[x];i;i=G.e[i].next)
using namespace std;
const int MAXN=1e6+100;
int n,m;
struct Graph {
	int n,head[MAXN],tot;
	struct Edge {int to,next;}e[MAXN<<1];
	#define Gerg(x,i) for(int i=head[x];i;i=e[i].next)
	void Addedge(int u,int v) {
		e[++tot].to=v,e[tot].next=head[u],head[u]=tot;
	}
	void Init(int _n) {
		n=_n; tot=1;
		for(int i=1;i<=n;i++) head[i]=0;
	}
	void Erg() {
		for(int x=1;x<=n;x++) {
			cout<<"Node "<<x<<endl;
			Gerg(x,i) cout<<e[i].to<<' '; cout<<endl;
		}
	}
}G[2];
void GetGraph(int p) {
	G[p&1^1].Init(G[p&1].tot/2);
	for(int x=1;x<=G[p&1].n;x++) {
		erg(G[p&1],x,i)
			erg(G[p&1],x,j) {
				if(i==j) continue;
				G[p&1^1].Addedge(i/2,j/2);
			}
	}
}
int main() {
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	cin>>n>>m; G[0].Init(n);
	for(int i=1;i<=m;i++) {
		int u,v; cin>>u>>v;
		G[0].Addedge(u,v);
		G[0].Addedge(v,u);
	}
	if(n==1) cout<<0<<' '<<1<<endl;
	else if(n<=3) {
		GetGraph(0);
		if(G[1].tot/2==m) cout<<1<<' '<<3<<endl;
		else {
			cout<<0<<' ';
			int sum=G[0].n;
			for(int i=1;G[i&1].n;GetGraph(i),i++) sum+=G[i&1].n;
			cout<<sum<<endl;
		}
	}
	return 0;
}