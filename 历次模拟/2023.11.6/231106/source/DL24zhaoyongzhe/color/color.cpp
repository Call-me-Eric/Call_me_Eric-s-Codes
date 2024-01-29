#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f=  1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f  =-1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 100;
int n, k;
vector<int> edg[maxn];
int col[maxn], ans;
void dfs(int u){
	if(u == n + 1){ans++;if(ans >= 998244353)ans -= 998244353;return;}
	if(col[u])dfs(u + 1);
	else{
		for(int i = 1;i <= k;i++){
			bool flag = true;
			for(int v : edg[u])if(col[v] == i){flag = false;break;}
			if(flag){col[u] = i;dfs(u + 1);col[u] = 0;}
		}
	}
}
signed main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	n = read(); k = read();int u, v;
	for(int i = 1;i <= n;i++)col[i] = read();
	for(int i = 1;i < n;i++){
		u = read(); v = read();
		edg[u].push_back(v);edg[v].push_back(u);
	}
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
