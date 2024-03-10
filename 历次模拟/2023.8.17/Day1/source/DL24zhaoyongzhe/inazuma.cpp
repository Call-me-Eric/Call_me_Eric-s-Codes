#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10, maxm = 2e6 + 10;
int n, m;
//int head[maxn], tot;
struct edge{
	int  from,to, times, id;
	edge(int fr = 0,int to = 0,int we = 0,int i = 0):from(fr),to(to), times(we),id(i){}
}e[maxm];
//void add(int u,int v,int w,int id){e[++tot] = edge(v,head[u], w, id);head[u] = tot;}
int ans, s[maxm], sum;
int fa[maxn];
int getf(int x){
	return x == fa[x] ? x : fa[x] = getf(fa[x]);
}
bool check(int time){
	int sum = n;
	for(int i = 1;i <= n;i++)fa[i] = i;
	for(int i = 1;i <= m;i++){
		if(s[i] <= time && s[i] + e[i].times >= time){
			if(getf(e[i].from) != getf(e[i].to)){
				fa[getf(e[i].from)] = getf(e[i].to);
				sum--;
			}
		}
	}
	return sum == 1;
}
int check(){
	int cnt = 0;
	while(check(cnt))cnt++;
	return cnt - 1;
}
void dfs(int u){
	if(u == m + 1){
		ans = max(ans, check());
		return;
	}
	for(int i = 0;i <= sum * 2;i++){
		s[u] = i;
		dfs(u + 1);
		s[u] = 0;
	}
}
signed main(){
	freopen("inazuma.in","r",stdin);
	freopen("inazuma.out","w",stdout);
	n = read(); m = read(); int u, v, w;
	for(int i = 1;i <= m;i++){
		u = read(); v = read(); w = read();
		e[i] = edge(u, v, w, i);
		sum += w;
	}
	dfs(1);
	printf("%d\n",ans);
	return 0;
}

