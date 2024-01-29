#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
vector<int> edg[maxn];
int n;
int dfs(int u,int f){
	int res = 0;
	for(int v : edg[u])if(v != f)res ^= (dfs(v, u) + 1);
	return res;
}
signed main(){
	n = read();int u, v;
	for(int i = 1;i < n;i++){
		u = read(); v = read();
		edg[u].push_back(v);edg[v].push_back(u);
	}
	puts(dfs(1, 0) ? "Alice" : "Bob");
	return 0;
}
