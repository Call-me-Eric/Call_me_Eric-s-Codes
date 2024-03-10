#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<queue>
#include<string.h>
#define TT int
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}
int n, m , k;
int S, T;
const int maxn = 1e4 * 5;
int dis[maxn][20];
int head[maxn], tot;
struct EDGE{
	int topoint, nextedge, weight;
}e[maxn * 2];
struct node{
	int u, w;
	bool operator < (const node b)const{
		return w > b.w;
	}
}tmp;
priority_queue<node> que;
void add(int u,int v,int w){
	e[++tot].nextedge = head[u];
	head[u] = tot;
	e[tot].topoint = v;
	e[tot].weight = w;
}
signed main(){
	n = read(); m = read(); k = read();
	S = read(); T = read();
	int u, v, w;
	for(int i = 0;i < m;i++){
		u = read(); v = read(); w = read();
		add(u,v,w);
		add(v,u,w);
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j <= k;j++){
			dis[i][j] = 0x3f3f3f3f;
		}
	}
	for(int i = 0;i <= k;i++)dis[S][i] = 0;
	for(int kk = 0;kk <= k;kk ++){
		que.push(node{S,0});
		while(!que.empty()){
			tmp = que.top(); que.pop();
			if(tmp.w > dis[tmp.u][kk])continue;
			for(int j = head[tmp.u];j;j = e[j].nextedge){
				v = e[j].topoint;
				w = e[j].weight;
				bool book = 0;
				if(kk){
					if(dis[v][kk] > dis[tmp.u][kk - 1]){
						dis[v][kk] = dis[tmp.u][kk - 1];
						book = 1;
					}
				}
				if(dis[v][kk] > dis[tmp.u][kk] + w){
					dis[v][kk] = dis[tmp.u][kk] + w;
					book = 1;
				}
				if(book) que.push(node{v,dis[v][kk]});
			}
		}
	}
	printf("%d\n",dis[T][k]);
	return 0;
}

