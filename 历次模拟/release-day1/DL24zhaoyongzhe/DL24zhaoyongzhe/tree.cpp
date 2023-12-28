#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
typedef unsigned long long ull;
const int maxn = 2e5 + 10;
int n, m;
vector<int> edg[maxn];

int f[maxn][2];
void dfs(int u,int fa){
	for(int v : edg[u]){
		if(v != fa){
			dfs(v, u);
			if(f[v][0] + 1 > f[u][0]){f[u][1] = f[u][0];f[u][0] = f[v][0] + 1;}
			else if(f[v][0] + 1 > f[u][1]){f[u][1] = f[v][0] + 1;}
		}
	}
}

signed main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n = read(); m = read();
	for(int i = 2;i <= n;i++){int u = read();edg[u].push_back(i);edg[i].push_back(u);}
	dfs(1, 0); int maxx = 0;
	
	for(int i = 1;i <= n;i++)maxx = max(maxx,f[i][0] + f[i][1]);
	
	ull a = maxx, b = 2, c = m - 1, d = f[1][0], f = 1;
	cout << a + b * c * d + b * c + f << endl;
	return 0;
}
