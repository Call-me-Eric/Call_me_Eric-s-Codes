#include <bits/stdc++.h>
#define rep(i,j,k) for(int i = (j);i <= (k);i++)
#define per(i,j,k) for(int i = (j);i >= (k);i--)
using namespace std;
int r,g,b,n,m;
int _u[50005],_v[50005],_c[50005],ans[50005];

int cnt;
int head[255];
struct eg{
	int to,nxt,c,id;
}edge[100005];

void make(int u,int v,int c,int id){
	edge[++cnt].to = v;
	edge[cnt].c = c;
	edge[cnt].id = id;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}

namespace dsu{
	int fa[255];
	void init(){
		rep(u,1,n) fa[u] = u;
	}
	int fnd(int u){
		if(fa[u] == u) return u;
		return fa[u] = fnd(fa[u]);
	}
	void mrg(int u,int v){
		u = fnd(u);v = fnd(v);
		assert(u != v);
		fa[u] = v;
	}
}
int occ[5],inst[5];
mt19937 rnd(time(NULL));
int I[255][255];
void dfs(int u,int f,int s,int val){
	I[s][u] = val;
	for(int i = head[u];i;i = edge[i].nxt){
		int v = edge[i].to;
		if(v == f) continue;
		if(val == -1 || occ[edge[i].c] - inst[edge[i].c] > occ[_c[val]] - inst[_c[val]]) dfs(v,u,s,edge[i].id);
		else dfs(v,u,s,val);
	}
}

int p[50005];
void test(){
	dsu::init();
	rep(i,1,m){
		p[i] = i;
		swap(p[i],p[rnd() % i + 1]);
	}
	int qwq = n;
	rep(_i,1,m){
		int i = p[_i];
		if(dsu::fnd(_u[i]) != dsu::fnd(_v[i])){
			dsu::mrg(_u[i],_v[i]);
			make(_u[i],_v[i],_c[i],i);
			make(_v[i],_u[i],_c[i],i);
			occ[_c[i]]++;
			ans[i] = 1;
			qwq--;
		}
	}
	if(qwq > 1){
		printf("NO\n");
		return;
	}

	inst[0] = r;inst[1] = g;inst[2] = b;
	rep(rr,1,n){
		if(occ[0] == inst[0] && occ[1] == inst[1] && occ[2] == inst[2]){
			cerr << rr << endl;
			break;
		}
		rep(i,1,m) swap(p[i],p[rnd() % i + 1]);
		rep(u,1,n) dfs(u,0,u,-1);
		int res = -1,tmp;
		rep(_i,1,m){
			int i = p[_i];
			if(ans[i] || I[_u[i]][_v[i]] == -1 || occ[_c[i]] >= inst[_c[i]]) continue; 
			res = i;
		}
		rep(_i,1,m){
			int i = p[_i];
			if(ans[i] || I[_u[i]][_v[i]] == -1 || occ[_c[i]] > inst[_c[i]]) continue; 
			if(res == -1) res = i;
		}
		ans[res] = 1;
		tmp = I[_u[res]][_v[res]];
		ans[tmp] = 0;
		occ[_c[res]]++;
		occ[_c[tmp]]--;

		cnt = 0;
		fill(head + 1,head + n + 1,0);
		rep(i,1,m){
			if(ans[i]){
				make(_u[i],_v[i],_c[i],i);
				make(_v[i],_u[i],_c[i],i);
			}
		}
	}
	if(occ[0] != inst[0] || occ[1] != inst[1] || occ[2] != inst[2]){
		cerr << "?? " << endl;
		printf("NO\n");
		return;
	}
	printf("YES\n");
	rep(i,1,m) printf("%d",ans[i]);
	printf("\n");
}

int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	scanf("%d%d%d%d",&r,&g,&b,&m);
	n = r + g + b + 1;
	char str[5];
	rep(i,1,m){
		scanf("%d%d%s",&_u[i],&_v[i],str + 1);
		if(str[1] == 'r') _c[i] = 0;
		else if(str[1] == 'g') _c[i] = 1;
		else _c[i] = 2;
	}
	dsu::init();
	rep(i,1,m) if(!_c[i] && dsu::fnd(_u[i]) != dsu::fnd(_v[i])) dsu::mrg(_u[i],_v[i]);
	cnt = 0;
	rep(u,1,n) if(dsu::fa[u] == u) cnt++;
	if(cnt > n - r){
		printf("NO\n");
		return 0;
	}

	dsu::init();
	rep(i,1,m) if(_c[i] == 1 && dsu::fnd(_u[i]) != dsu::fnd(_v[i])) dsu::mrg(_u[i],_v[i]);
	 cnt = 0;
	rep(u,1,n) if(dsu::fa[u] == u) cnt++;
	if(cnt > n - g){
		printf("NO\n");
		return 0;
	}

	dsu::init();
	rep(i,1,m) if(_c[i] == 2 && dsu::fnd(_u[i]) != dsu::fnd(_v[i])) dsu::mrg(_u[i],_v[i]);
	 cnt = 0;
	rep(u,1,n) if(dsu::fa[u] == u) cnt++;
	if(cnt > n - b){
		printf("NO\n");
		return 0;
	}

	dsu::init();
	rep(i,1,m) if(_c[i] <= 1 && dsu::fnd(_u[i]) != dsu::fnd(_v[i])) dsu::mrg(_u[i],_v[i]);
	 cnt = 0;
	rep(u,1,n) if(dsu::fa[u] == u) cnt++;
	if(cnt > n - r - g){
		printf("NO\n");
		return 0;
	}

	dsu::init();
	rep(i,1,m) if(_c[i] >= 1 && dsu::fnd(_u[i]) != dsu::fnd(_v[i])) dsu::mrg(_u[i],_v[i]);
	 cnt = 0;
	rep(u,1,n) if(dsu::fa[u] == u) cnt++;
	if(cnt > n - g - b){
		printf("NO\n");
		return 0;
	}

	dsu::init();
	rep(i,1,m) if(_c[i] != 1 && dsu::fnd(_u[i]) != dsu::fnd(_v[i])) dsu::mrg(_u[i],_v[i]);
	 cnt = 0;
	rep(u,1,n) if(dsu::fa[u] == u) cnt++;
	if(cnt > n - r - b){
		printf("NO\n");
		return 0;
	}
	test();
	return 0;
}
//g++ A.cpp -o A -Wall -Wshadow -O2 -std=c++14 -Wno-unused-result