#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 5e5 + 10, maxm = 1e6 + 10;

int n, m;
vector<int> edg[maxn];
int dep[maxn], fa[maxn];
vector<int> vec[maxn];
void dfs(int u,int f){for(int v : edg[u]){if(!dep[v]){dep[v] = dep[u] + 1;fa[v] = u;dfs(v, u);}}}

stack<int> stk;
vector<pair<int,int> > ans;
void solve(){
	n = read(); m = read();int u, v;
	for(int i = 1;i <= n;i++){dep[i] = 0;edg[i].clear();fa[i] = 0;vec[i].clear();}
	for(int i = 1;i <= m;i++){
		u = read(); v = read();
		edg[u].push_back(v);edg[v].push_back(u);
	}
	dep[1] = 1;dfs(1, 1);
	while(!stk.empty())stk.pop();ans.clear();
	for(int i = 1;i <= n;i++){
		if(dep[i] >= (n >> 1) + (n & 1)){
			puts("PATH");
			u = i;while(u != 1){stk.push(u);u = fa[u];}
			stk.push(1);printf("%d\n",stk.size());
			while(!stk.empty()){printf("%d ",stk.top());stk.pop();}
			return;
		}
		vec[dep[i]].push_back(i);
	}
	puts("PAIRING");
	for(int i = 1;i <= n;i++)
		for(int j = 0;j + 1 < vec[i].size();j += 2)
			ans.push_back(make_pair(vec[i][j],vec[i][j + 1]));
	printf("%d\n",ans.size());
	for(auto i : ans)printf("%d %d\n",i.first,i.second);
}

signed main(){
	int T = read();
	while(T--)solve();
	return 0;
}
