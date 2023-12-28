#include <set>
#include <cstdio>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <random>
using namespace std;
mt19937 rng(329);
const int N=253,M=100003;
struct edge{int u,v,w,id;}e[M];
char str[3];
int n,m;
struct ds{
	int f[N];
	int rt(int x){
		if(f[x]==x) return x;
		return f[x]=rt(f[x]);
	}
}G,S,C;
void copyds(ds *A,ds *B){for(int i=1;i<=n;++i) A->f[i]=B->f[i];}
int pos;
bool check(int s,int goal){
	copyds(&S,&G);
	for(int i=pos;i<m;++i)
		if(s>>e[i].w&1){
			if(S.rt(e[i].u)==S.rt(e[i].v)) continue;
			if(!--goal) return 1;
			S.f[S.rt(e[i].u)]=S.rt(e[i].v);
		}
	return !goal;
}
bool judge(int c[3]){
	if(c[0]<0||c[1]<0||c[2]<0) return 0;
	for(int s=1;s<8;++s){
		int cur=0;
		for(int i=0;i<3;++i) if(s>>i&1) cur+=c[i];
		if(!check(s,cur)) return 0;
	}
	return 1;
}
bool res[M];
namespace two{
	typedef pair<int,int> pii;
	set<pii> st[N];
	void ins(int u,int v,int i){
		st[u].emplace(v,i);
		st[v].emplace(u,i);
		res[i]=1;
	}
	void del(int u,int v,int i){
		st[u].erase(pii(v,i));
		st[v].erase(pii(u,i));
		res[i]=0;
	}
	int goal,eid;
	bool dfs(int u,int fa){
		if(u==goal) return 1;
		for(pii cur:st[u]){
			if(cur.first==fa) continue;
			if(dfs(cur.first,u)){
				if(e[cur.second].w==0) eid=cur.second;
				return 1;
			}
		}
		return 0;
	}
	bool proc(int u,int v,int i){
		eid=-1;goal=v;
		if(dfs(u,0)){
			if(~eid){
				del(e[eid].u,e[eid].v,eid);
				ins(u,v,i);
				return 1;
			}
			return 0;
		}
		else{
			ins(u,v,i);
			return 1;
		}
	}
	void solve(int gg){
		puts("YES");
		for(int i=0;i<m;++i)
			if(e[i].w==0) proc(e[i].u,e[i].v,i);
		for(int i=0;i<m&&gg;++i)
			if(e[i].w==1){
				if(proc(e[i].u,e[i].v,i)) --gg;
			}
		for(int i=0;i<m;++i)
			printf("%d",res[i]);
		putchar('\n');
	}
}
int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	int c[3];
	scanf("%d%d%d%d",c,c+1,c+2,&m);
	n=c[0]+c[1]+c[2]+1;
	for(int i=0;i<m;++i){
		scanf("%d%d%s",&e[i].u,&e[i].v,str);
		if(*str=='r') e[i].w=0;
		if(*str=='g') e[i].w=1;
		if(*str=='b') e[i].w=2;
		e[i].id=i;
	}
	for(int i=1;i<=n;++i) C.f[i]=i;
	copyds(&G,&C);
	if(!judge(c)){puts("NO");return 0;}
	if(c[2]==0){two::solve(c[1]);return 0;}
	while((double)clock()/CLOCKS_PER_SEC<1.7){
		shuffle(e,e+m,rng);
		for(int i=0;i<m;++i) res[i]=0;
		for(int i=1;i<=n;++i) C.f[i]=i;
		for(pos=1;pos<=m;++pos){
			int x=pos-1;
			if(C.rt(e[x].u)==C.rt(e[x].v)) continue;
			copyds(&G,&C);
			G.f[G.rt(e[x].u)]=G.rt(e[x].v);
			--c[e[x].w];
			if(judge(c)) copyds(&C,&G),res[e[x].id]=1;
			else ++c[e[x].w],res[e[x].id]=0;
			if(!c[0]&&!c[1]&&!c[2]) break;
		}
		if(c[0]||c[1]||c[2]) continue;
		puts("YES");
		for(int i=0;i<m;++i) printf("%d",res[i]);
		putchar('\n');
		return 0;
	}
	puts("NO");
	return 0;
}
