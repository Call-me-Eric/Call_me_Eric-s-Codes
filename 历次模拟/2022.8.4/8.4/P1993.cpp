#include<bits/stdc++.h>
#define TT int
using namespace std;
inline TT read(){
	char ch = getchar();TT x = 0, f = 1;
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
int n, m;
const int maxn = 5 * 1e4,maxm = 5 * 1e4;
int head[maxn], tot, dis[maxn], cnt[maxn];
bool book[maxn];
struct edges{
	int nextedge, topoint, weight;
}edge[maxm];
void add(int u,int v,int w){
	edge[++tot].nextedge = head[u];
	edge[tot].topoint = v;
	edge[tot].weight = w;
	head[u] = tot;
}
queue<int> que;
bool spfa(){
	dis[n + 1] = 0;
	book[n + 1] = 0;
	cnt[n + 1]++;
	que.push(n + 1);
	while(!que.empty()){
		int u = que.front();
		que.pop();
		book[u] = 0;
		for(int x = head[u];x;x = edge[x].nextedge){
			int v = edge[x].topoint;
			if(dis[v] > dis[u] + edge[x].weight){
				dis[v] = dis[u] + edge[x].weight;
				que.push(v);
				book[v] = 1;
				cnt[v]++;
				if(cnt[v] == n + 1){
					return false;
				}
			}
		}
	}
	return true;
}
signed main(){
	n = read(); m = read();
	int x, y, z, op;
	memset(dis,0x3f,sizeof(dis));
	for(int i = 1;i <= m;i++){
		op = read();x = read();y = read();
		if(op != 3)z = read();
		if(op == 1)add(x,y,-z);
		if(op == 2)add(y,x, z);
		if(op == 3){
			add(x,y,0);
			add(y,x,0);
		}
	}
	for(int i = 1;i <= n;i++){
		add(n + 1,i,0);
	}
	bool flag = spfa();
	if(flag)puts("Yes");
	else puts("No");
	return 0;
}

