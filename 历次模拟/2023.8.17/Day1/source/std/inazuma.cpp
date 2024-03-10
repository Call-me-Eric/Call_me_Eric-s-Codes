#include<bits/stdc++.h>
#define ll long long
#define N 1000005 
using namespace std;

struct edge{int u,v,w,id;}o[N<<1];

vector<pair<int,int> > e[N];

int dfn[N],low[N],tot;

stack<edge> st;

int ans=2e9;

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  for (; !isdigit(c); c = getchar()) f |= (c == '-');
  for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return f ? -x : x;
}

void tarjan(int x,int f){
	dfn[x]=low[x]=++tot;
	for (auto [p,id]:e[x]) if (!dfn[p]) {
		st.push(o[id]);tarjan(p,id);low[x]=min(low[x],low[p]);
		if (low[p]>=dfn[x]) {
			edge nw;vector<int> g;
			do {
				nw=st.top();st.pop();
				g.push_back(nw.w);
			}
			while (nw.id!=id);
			sort(g.begin(),g.end());
			if (g.size()==1) ans=min(ans,g[0]);
			else if (g.size()==2) ans=min(ans,g[0]+g[1]);
			else ans=min(ans,min(g[0]+g[1],g[2]));
		}
	}
	else {
		if (dfn[x]>dfn[p] && id!=f) st.push(o[id]);
		low[x]=min(low[x],dfn[p]);
	}
}

int main() {
	freopen("inazuma.in", "r", stdin);
	freopen("inazuma.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n=rd(),m=rd(),i;tot=0;ans=2e9;
	for (i=1;i<=n;i++) e[i].clear(),dfn[i]=low[i]=0;
	for (i=1;i<=m;i++){
		o[i].u=rd();o[i].v=rd();o[i].w=rd();o[i].id=i;
		e[o[i].u].push_back({o[i].v,i});
		e[o[i].v].push_back({o[i].u,i});
	}
	tarjan(1,0);
	cout<<ans<<endl;
}
