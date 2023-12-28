#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int head[maxn];
int to[maxn];
int nxt[maxn];
int w[maxn];
int cnt;
int n,k;
const int inf=1e18;
void add(int x,int y,int z){
//	cout<<x<<" "<<y<<" "<<z<<'\n';
	to[++cnt]=y;
	nxt[cnt]=head[x];
	w[cnt]=z;
	head[x]=cnt;
}
int diss[maxn];
struct node{
	int dis,id;
	friend bool operator < (node a,node b){
		return a.dis>b.dis;
	}
};
priority_queue<node>q;
void dij(int s){
	for(int i=1;i<=maxn-1;i++) diss[i]=inf;
	diss[s]=0;
	q.push(node{0,s});
	while(!q.empty()){
		node kk=q.top();
		int disss=kk.dis;
		int x=kk.id;
		q.pop();
		if(disss!=diss[x]) continue;
		for(int i=head[x];i;i=nxt[i]){
			int v=to[i];
			if(diss[v]>diss[x]+w[i]){
				diss[v]=diss[x]+w[i];
				q.push(node{diss[v],v});
			}
		}
	}
}
signed main(){
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			int x;
			cin>>x;
			add(j,j+i*n,x);
		} 
		for(int j=1;j<=n;j++){
			int x;
			cin>>x;
			add(j+i*n,j,x);
		}
		int m;
		cin>>m;
		for(int j=1;j<=m;j++){
			int u,v,w;
			cin>>u>>v>>w;
			add(u+i*n,v+i*n,w);
			add(v+i*n,u+i*n,w);
		}
	}
	dij(1);
	cout<<diss[n];
	return 0;
}

