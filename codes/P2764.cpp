#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 150 + 10, maxm = 6e3 + 10;

int n, m;
int head[maxn], tot;
struct edge{
    int to, nexte, id;
    edge(int to = 0,int ne = 0,int id = 0):to(to), nexte(ne), id(id){}
}e[maxm];
void add(int u,int v,int i){e[++tot] = edge(v,head[u],i);head[u] = tot;}

signed main(){
    return 0;
}