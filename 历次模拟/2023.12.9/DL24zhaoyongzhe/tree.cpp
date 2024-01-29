#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f=  1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 5e5 + 10;
int n, val[maxn];
vector<int> edg[maxn];
int se[maxn];
struct node{
	int val, id;
	node(int v = 0,int i = 0):val(v),id(i){}
	friend bool operator < (node a,node b){return a.val < b.val;}
	friend bool operator > (node a,node b){return a.val > b.val;}
};
typedef priority_queue<node,vector<node>,less<node> > prque;
priority_queue<node,vector<node>,less<node> > que[maxn];

int getans(int u){
	int res = 0;
	if(que[u].empty())return 0;
	int idd = que[u].top().id;
	vector<node> tmp;tmp.clear();
	while(!que[u].empty() && idd == que[u].top().id){tmp.push_back(que[u].top());que[u].pop();}
	if(!que[u].empty())res = que[u].top().val;
	for(auto j : tmp)que[u].push(j);
	return res;
}
//bool flag[maxn];
void dfs(int u,int f){
	se[u] = 0;while(!que[u].empty())que[u].pop();
	for(int v : edg[u]){
		if(v != f){
			dfs(v, u);
			que[u].push(node(se[v],v));
			que[u].push(node(val[v],v));
		}
	}
	if(que[u].empty())return;
	se[u] = getans(u);
}
int res[maxn];
void dfs2(int u,int f){
	res[u] = val[u];
	for(int v : edg[u]){
		res[u] = max(res[u],val[v]);
		res[u] = max(res[u],getans(v));
	}
	for(int v : edg[u]){
		if(v != f){
			vector<node> tmp;tmp.clear();prque tmpp = que[v];
			while(!que[u].empty() && que[u].top().id == v){tmp.push_back(que[u].top());que[u].pop();}
			que[v].push(node(val[u],u));if(!que[u].empty())que[v].push(node(getans(u),u));
			dfs2(v, u);
			for(auto j : tmp)que[u].push(j);que[v] = tmpp;
		}
	}
}
signed main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n = read();int u, v;
	for(int i = 1;i <= n;i++){val[i] = read();}
	for(int i = 1;i < n;i++){
		u = read(); v = read();
//		if(u != i || v != i + 1)fl = false;
		edg[u].push_back(v);edg[v].push_back(u);
	}
if(n <= 1e3){
	for(int i = 1;i <= n;i++){
		dfs(i ,i);int ans = max(se[i],val[i]);
		for(int v : edg[i])
			ans = max(ans,max(se[v],val[v]));
		printf("%d ",ans);
	}
}
else{
	dfs(1, 1);dfs2(1, 0);
	for(int i = 1;i <= n;i++)
		printf("%d ",res[i]);
}
	puts("");
	return 0;
}
