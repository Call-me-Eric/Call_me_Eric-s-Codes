#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
int n, a[maxn];
vector<int> edg[maxn];

bool book[maxn];
vector<int> ans;bool flag;
stack<int> stk;
void dfs(int u){
	if(flag)return;
	book[u] = 1;stk.push(u);
	for(int v : edg[u]){
		if(book[v]){
			while(stk.top() != v){ans.push_back(stk.top());stk.pop();}
			ans.push_back(v);flag = 1;return;
		}
		else dfs(v);
		if(flag)return;
	}
}

void solve(){
	n = read();
	for(int i = 1;i <= n;i++){edg[i].clear();a[i] = read();edg[i].push_back(i - a[i]);book[i] = 0;}
	ans.clear();while(!stk.empty())stk.pop();
	flag = false;dfs(1);
	printf("%d\n",ans.size());
	for(int i : ans)printf("%d ",i);
	puts("");
}

signed main(){
	int T = read();
	while(T--){solve();}
	return 0;
}
