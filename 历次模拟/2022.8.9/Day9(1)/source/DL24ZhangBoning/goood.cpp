#include<bits/stdc++.h>
using namespace std;

#define FO(name) freopen(name".in","r",stdin);freopen(name".out","w",stdout)

const int maxN = 1e6+10;

vector<int> G1[maxN];
vector<int> G2[maxN];

int D[2][maxN];

inline void add_edge(int u,int v){
	G1[u].push_back(v);
	G2[v].push_back(u);
	D[0][v]++;
	D[1][u]++;
}

set<int> cto[2];
int vis[maxN][2];

void dfs1(int k){
	cto[0].insert(k);
	vis[k][0] = 1;
	for(auto i : G1[k]){
		if(vis[i][0]) continue;
		dfs1(i);
	}
}

void dfs2(int k){
	cto[1].insert(k);
	vis[k][1] = 1;
	for(auto i : G2[k]){
		if(vis[i][1]) continue;
		dfs2(i);
	}
}

vector<int> ans;

int main(){
	FO("goood");
	ios::sync_with_stdio(false);
	int N,M;
	cin >> N >> M;
	for(int i = 1;i<=M;i++){
		int u,v;
		cin >> u >> v;
		add_edge(u,v);
	}
	for(int i = 1;i<=N;i++){
		cto[0].clear();
		cto[1].clear();
		for(int j = 1;j<=N;j++) vis[j][0] = vis[j][1] = 0;
		dfs1(i);
		dfs2(i);
		for(auto i : cto[0]){
			cto[1].insert(i);
			if(cto[1].size() == N) break;
		}
		if(cto[1].size() == N) ans.push_back(i);
	}
	cout << ans.size() << endl;
	for(auto i : ans){
		cout << i << " ";
	}
	

	return 0;
}
