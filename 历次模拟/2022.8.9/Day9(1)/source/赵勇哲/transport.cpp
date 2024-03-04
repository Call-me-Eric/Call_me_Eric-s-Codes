#include<iostream>
#include<stdio.h>
#include<string.h>
#define TT int
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1)+ ch - '0';ch = getchar();}
	return x * f;
}
int n;
const int maxn = 1e6 + 10;
int a[maxn];
int head[maxn], tot;
struct EDGE{
	int topoint, nextedge, weight;
}e[maxn * 2];
void add(int u,int v,int w){
	e[++tot].topoint = v;
	e[tot].nextedge = head[u];
	e[tot].weight = w;
	head[u] = tot;
}
long long cnt = 0;
long long dfs(int x,int fa,int len){
	long long res = 1;
	for(int i = head[x];i;i = e[i].nextedge){
		int j = e[i].topoint, w = e[i].weight;
		if(j == fa || len + w < 0)continue;
		else {
			res += dfs(j,x,len + w);
		}
	}
	return res;
}
signed main(){
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	n = read();
	int x, y, z;
	for(int i = 1;i <= n;i++) a[i] = read();
	for(int i = 1;i < n;i++){
		x = read(); y = read(); z = read();
		add(x,y,a[x] - z); add(y, x, a[y] - z);
	}
	for(int i = 1;i <= n;i++){
		int tmp = dfs(i,0,0);
		cnt += (tmp - 1);
	}
	printf("%lld\n",cnt);
	return 0;
}

