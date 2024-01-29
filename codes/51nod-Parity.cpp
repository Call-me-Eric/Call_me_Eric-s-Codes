#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char op[10];
int n, m, f[100001],g[100001];//f为奇偶性相同,g为奇偶性不同 
int getf(int x){
	if(f[x] < 0)return x;
	int fx = f[x];
	f[x] = getf(f[x]);
	g[x] ^= g[fx];
	return f[x];
}
bool add(int u,int v,int w){
	int x = getf(u), y = getf(v);
	if(x == y){
		return !(g[u] ^ g[v] ^ w);
	}
	if(f[x] > f[y]) swap(x,y);
	if(f[x] == f[y])f[x]--;
	f[y] = x;
	g[y] = g[u] ^ g[v] ^ w;
	return 1;
}
int main(){
	scanf("%d%d",&n,&m);
	int x, y;
	memset(f,-1,sizeof(f));
	for(int i = 1;i <= m;i++){
		scanf("%d%d%s",&x,&y,op);
		if(!add(x - 1,y,op[0] == 'o')){
			printf("%d",i);
			return 0;
		}
	}
	puts("-1");
	return 0;
}

