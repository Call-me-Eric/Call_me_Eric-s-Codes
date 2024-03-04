#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 2e6 + 10;
int n, m;

int head[maxn], tot;
struct edge{
	int to, nexte, id, wei;
	edge(int to = 0,int ne = 0,int we = 0,int id = 0):to(to),nexte(ne),wei(we),id(id){}
}e[maxn << 1];
void add(int u,int v,int w,int id){e[++tot] = edge(v,head[u], w, id);head[u] = tot;}

int ans = 0x3f3f3f3f;

int dfn[maxn], low[maxn], idx;
stack<edge> stk;
void Tarjan(int u,int f){
	dfn[u] = low[u] = ++idx;
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to, w = e[i].wei, id = e[i].id;
		if(!dfn[v]){
			stk.push(e[i]);
			Tarjan(v,id);
			low[u] = min(low[v],low[u]);
			if(low[v] >= dfn[u]){
				edge tmp = edge();
				vector<int> vec;
				do{
					tmp = stk.top();stk.pop();
					vec.push_back(tmp.wei);
				}while(tmp.id != id);
				sort(vec.begin(),vec.end());
				if(vec.size() == 1){ans = min(ans,vec[0]);}
				else if(vec.size() == 2){ans = min(ans,vec[0] + vec[1]);}
				else{ans = min(ans,min(vec[0] + vec[1],vec[2]));}
			}
		}
		else{
			if(dfn[u] > dfn[v] && id != f){stk.push(e[i]);}
			low[u] = min(low[u],dfn[v]);
		}
	}
}

signed main(){
	freopen("inazuma18.in","r",stdin);
	freopen("inazuma.out","w",stdout);
	n = read(); m  =read();
	for(int i = 1;i <= m;i++){
		int u = read(), v = read(), w = read();
		add(u, v, w, i); add(v, u, w, i);
	}
	Tarjan(1,0);
	printf("%d\n",ans);
	return 0;
}

