#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#define re register
#define rep(a,b,c)  for(re int a(b) ; a<=c ; ++a)
#define drep(a,b,c) for(re int a(b) ; a>=c ; --a)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int M = 5010;
const int N = 2e5+10;
stack<int> s;
vector<int> v[M];
priority_queue<int,vector<int>,greater<int> >q;
int vis[M][M];
int dfn[M],low[M],sccnum[M],head1[M],head2[M],head[M],sccsize[M];
int n,m,cnt,cnt1,cnt2,tot,dfncnt,scccnt;
struct edge{
	int from,to,nxt;
}e[M],e1[M],e2[M];
inline void add(int u,int v){
	e[++cnt].to = v;
	e[cnt].from = u;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
inline void add1(int u,int v){
	e1[++cnt1].to = v;
	e1[cnt1].nxt = head1[u];
	head1[u] = cnt1;
}
inline void add2(int u,int v){
	e2[++cnt2].to = v;
	e2[cnt2].nxt = head2[u];
	head2[u] = cnt2;
}
inline void tarjan(int u){
	dfn[u] = low[u] = ++dfncnt;
	s.push(u);
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		else if(!sccnum[v]) low[u] = min(low[u],dfn[v]);
	}
	if(dfn[u] == low[u]){
		scccnt++;
		while(1){
			int x = s.top();
			s.pop();
			sccnum[x] = scccnt;
			v[scccnt].push_back(x);
			sccsize[scccnt]++;
			if(x == u) break;
		}
	}
}
inline void dfs1(int now,int u){
	for(re int i(head1[u]) ; i ; i=e1[i].nxt){
		int v = e1[i].to;
		if(vis[now][v]) continue;
		vis[now][v] = 1;
		dfs1(now,v);
	}
}
inline void dfs2(int now,int u){
	for(re int i(head2[u]) ; i ; i=e2[i].nxt){
		int v = e2[i].to;
		if(vis[now][v]) continue;
		vis[now][v] = 1;
		dfs2(now,v);
	}
}
signed main(){
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	n=read();m=read();
	rep(i,1,m){
		int u=read(),v=read();
		add(u,v);
	}
	rep(i,1,n) if(!dfn[i]) tarjan(i);
	for(re int i(1) ; i<=cnt ; ++i){
		int u = e[i].from,v = e[i].to;
		if(sccnum[u] == sccnum[v]) continue;
		add1(sccnum[u],sccnum[v]),add2(sccnum[v],sccnum[u]);
	}
	rep(i,1,scccnt){
		dfs1(i,i);
		dfs2(i,i);
	}
//	rep(i,1,scccnt){
//		rep(j,1,scccnt){
//			cout << vis[i][j] << " ";
//		}
//		cout << endl;
//	}
	rep(i,1,scccnt){
		int fl = 0;
		for(re int j(1) ; j<=scccnt ; ++j){
			if(i == j) continue; 
			if(vis[i][j] == 0){
				fl = 1;
				break;
			}
		}
		if(fl == 1) continue;
		if(fl == 0){
			tot += sccsize[i];
			for(auto x : v[i]) q.push(x);
		}
	}
	printf("%d\n",tot);
	while(!q.empty()){
		printf("%d ",q.top());
		q.pop();
	}
	printf("\n");
	return 0;
}

/*
6 7
1 2
1 3
2 4
3 4
4 5
5 6
6 5
*/
