#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f =1 ;char ch = getchar();
	while(ch < '0'||ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
int n;
int val[maxn];

int head[maxn], tot;
struct edge{
	int to, nexte;
	edge(int to = 0,int ne = 0):to(to),nexte(ne){}
}e[maxn];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}


signed main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n = read();int u;
	for(int i = 2;i <= n;i++){u = read();add(u, i);}
	for(int i = 1;i <= n;i++){val[i] = read();}
	int ans = 0;
	for(int i = 1;i <= n;i++){
		if(!head[i])ans += val[i];
	}
	printf("%lld\n",ans * val[1]);
	return 0;
}
