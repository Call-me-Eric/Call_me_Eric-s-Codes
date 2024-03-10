#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TT int
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1)+ ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
int dfn[maxn][2], low[maxn][2];
int n, m, ans, answer[maxn];
bool book[maxn][2];
int head[maxn][2], tot[2];
struct EDGE{
	int topoint, nextedge;
}e[maxn][2];
void add(int u,int v, int k){
	e[++tot[k]][k].nextedge = head[u][k];
	head[u][k] = tot[k];
	e[tot[k]][k].topoint = v;
}
void dfs(int x,int k){
	book[x][k] = 1;
	for(int i = head[x][k];i;i = e[i][k].nextedge){
		int v = e[i][k].topoint;
		if(book[v][k])continue;
		book[v][k] = 1;
		dfs(v,k);
	}
	return;
}
signed main(){
	freopen("goood.in","r",stdin);
	freopen("goood.out","w",stdout);
	n = read(); m = read();
	int x, y;
	for(int i = 1;i <= m;i++){
		x = read(); y = read();
		add(x,y,0); add(y,x,1);
	}
	for(int i = 1;i <= n;i++){
		memset(book,0,sizeof(book));
		book[i][0] = book[i][1] = 1;
		dfs(i,0);	dfs(i,1);
		int cnt = 0;
		for(int j = 1;j <= n;j++){
			cnt += (book[j][0] || book[j][1]);
		}
		if(cnt == n){
			ans++;
			answer[ans] = i;
		}
	}
	printf("%d\n",ans);
	for(int i = 1;i <= ans;i++){
		printf("%d ",answer[i]);
	}
	return 0;
}

