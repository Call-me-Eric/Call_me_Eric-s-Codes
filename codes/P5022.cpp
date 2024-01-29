#include<bits/stdc++.h>
using namespace std;
const int maxn = 5000 + 10;
int n, m;
vector<int> e[maxn];
int tot;
int head[maxn];
int ans[maxn];
bool book[maxn];
int cnt;
int cir1[maxn];
int u1[maxn], v1[maxn];
int flag;
int res[maxn];
int du, dv;
void dfs1(int u,int fa) {
	if(book[u])
		return;
	book[u] = 1;
	ans[++tot] = u;
	for(int i = 0;i < e[u].size();i++){
		int v = e[u][i];
		if(v == fa)
			continue;
		dfs1(v, u);
	}
}

void dfs2(int u,int fa){
	if(book[u])return;
	book[u] = 1;
	res[++tot] = u;
	for(int i = 0;i < e[u].size();i++) {
		int v = e[u][i];
		if(v == fa)
			continue;
		if((u == du && v == dv) || (u == dv && v == du))
			continue;
		dfs2(v,u);
	}
}
void dfs3(int from,int fa) {
	book[from] = 1;
	for(int i = 0;i < e[from].size();i++) {
		int to = e[from][i];
		if(to == fa)
			continue;
		if(book[to]) {
			flag = 1;
			cir1[to] = 1;
			cir1[from] = 1;
			u1[++cnt] = from;
			v1[cnt] = to;
			return ;
		}
		dfs3(to, from);
		if(flag && cir1[to])
			if(cir1[from]) {
				flag = 0;
				u1[++cnt] = from;
				v1[cnt] = to;
				return ;
			} else {
				cir1[from]  = 1;
				u1[++cnt] = from;
				v1[cnt] = to;
				return ;
			}
	}
}
int check() {
	for(int i = 1;i <= n;i++) {
		if(res[i] < ans[i])
			return 1;
		else if(res[i] > ans[i])
			return 0;
	}
	return 0;
}
void update() {
	for(int i = 1;i <= n;i++){
		ans[i] = res[i];
	}
}
int main(){
    scanf("%d%d",&n,&m);
    int u, v;
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i = 1;i <= n;i++){
        sort(e[i].begin(),e[i].end());
    }
    if(n - 1 == m){
        dfs1(1,-1);
        for(int i = 1;i <= n;i++){
            printf("%d ",ans[i]);
        }
    }
    else{
        dfs3(1,0);
        flag = 1;
        for(int i = 1;i <= cnt;i++){//一个小优化：只删除环上边
            du = u1[i];
            dv = v1[i];
            memset(book,0,sizeof(book));
            tot = 0;
            dfs2(1,0);
            if(tot < n)continue;
            if(flag){
                update();
                flag = 0;
            }
            if(check()){
                update();
            }
        }
        for(int i = 1;i <= n;i++){
            printf("%d ",ans[i]);
        }
    }
    return 0;
}