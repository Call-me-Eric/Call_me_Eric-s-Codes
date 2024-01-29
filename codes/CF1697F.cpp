#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
int n, m, k;

vector<int> edg[maxn];
int id[maxn / 10][12][2], total;
void add(int a,int b,int c,int d,int e,int f){
	edg[id[a][b][c]].push_back(id[d][e][f]);
}
void addd(int a,int b,int c,int d,int e,int f){
	add(a,b,c,d,e,f);add(d,e,f ^ 1,a,b,c ^ 1);
}
int dfn[maxn],low[maxn], idx;
int col[maxn], color;bool book[maxn];
stack<int> stk;
void dfs(int u){
	dfn[u] = low[u] = ++idx;
	stk.push(u);book[u] = 1;
	for(int v : edg[u]){
		if(!dfn[v]){dfs(v);low[u] = min(low[u],low[v]);}
		else if(book[v]){low[u] = min(low[u],low[v]);}
	}
	if(dfn[u] == low[u]){
		int v;color++;
		do{
			v = stk.top();stk.pop();
			book[v] = 0;col[v] = color;
		}while(v != u);
	}
}
bool tarjan(){
	idx = color = 0;while(!stk.empty())stk.pop();
	for(int i = 1;i <= total;i++){dfn[i] = low[i] = col[i] = book[i] = 0;}
	for(int i = 1;i <= total;i++)if(!dfn[i])dfs(i);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= k + 1;j++)
			if(col[id[i][j][0]] == col[id[i][j][1]])return false;
	return true;
}

void solve(){
	n = read(); m = read(); k = read();total = idx = 0;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= k + 1;j++)
			for(int o = 0;o < 2;o++){
				id[i][j][o] = ++total;
				edg[total].clear();
			}
	for(int i = 1;i <= n;i++){
		add(i,1,0,i,1,1);add(i,k + 1,1,i,k + 1,0);
		for(int p = 1;p <= k;p++){
			addd(i,p + 1,1,i,p,1);
			if(i != n)addd(i,p,1,i + 1,p,1);
		}
	}
	int opt, u, v, w;
	for(int i = 1;i <= m;i++){
		opt = read(); u = read(); v = read();
		if(opt == 1){addd(u,v,1,u,v + 1,1);}
		else{
			w = read();
			if(opt == 2){
				for(int j = 1;j <= k;j++){
					int v1 = min(k + 1,max(1,w - j + 1));
					addd(u,j,1,v,v1,0);
				}
			}
			else{
				for(int j = 1;j <= k;j++){
					int v1 = min(k + 1,max(1,w - j));
					addd(u,j + 1,0,v,v1,1);
				}
			}
		}
	}
	if(!tarjan()){puts("-1");return;}
//	for(int i = 1;i <= n;i++)
//		for(int j = 1;j <= k + 1;j++){
//			for(int o = 0;o < 2;o++){
//				printf("col[%d,%d,%d]=%d\n",i,j,o,col[id[i][j][o]]);
//			}
//		}
	for(int i = 1;i <= n;i++){
		int x = -114514;
		for(int j = k;j;j--)
			if(col[id[i][j][0]] > col[id[i][j][1]]){x = j;break;}
		printf("%d%c",x," \n"[i == n]);
	}
	puts("");return;
}
signed main(){
	int T = read();
	while(T--){solve();}
	return 0;
}
