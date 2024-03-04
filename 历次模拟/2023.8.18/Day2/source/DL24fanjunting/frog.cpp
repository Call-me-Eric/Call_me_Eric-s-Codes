#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn=5e4+5;
struct node{
	int a,b,c,d,e,f;
}p[maxn];
int cnt;
int head[maxn];
int to[maxn*2000];
int nxt[maxn*2000];
int w[maxn*2000];
void add(int x,int y,int z){
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
	w[cnt]=z;
}
int diss[maxn];
struct nodee{
	int diss,id;
	friend bool operator < (nodee a,nodee b){
		return a.diss<b.diss;
	}
};
void dij(int s){
	priority_queue<nodee>q;
	memset(diss,-0x3f,sizeof(diss));
	diss[s]=0;
	q.push(nodee{0,s});
	while(!q.empty()){
		nodee hh=q.top();
		q.pop();
		if(hh.diss!=diss[hh.id]) continue;
		int di=hh.diss,idd=hh.id;
		for(int i=head[idd];i;i=nxt[i]){
			if(diss[to[i]]<diss[idd]+w[i]){
				diss[to[i]]=diss[idd]+w[i];
				q.push(nodee{diss[to[i]],to[i]});
			}
		}
	}
}
signed main(){
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i].a>>p[i].b>>p[i].c>>p[i].d>>p[i].e>>p[i].f;
	}
	add(1,0,0);
	for(int i=2;i<=n;i++){
		add(i,0,0);
		for(int j=1;j<i;j++){
			if(p[i].a>=p[j].a&&p[i].b>=p[j].b&&p[i].c>=p[j].c&&p[i].d>=p[j].d&&p[i].e>=p[j].e){
				add(i,j,p[j].f);
			}
		}
	}
	for(int i=1;i<=n;i++){
		dij(i);
//		cout<<diss[0]<<" "<<p[i].f<<'\n';
		int kk=diss[0]+p[i].f;
		cout<<kk<<'\n';
	}
	return 0;
}

