#include<bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 100020;
int T;
int fa[maxn];
void init(){
	for(int i = 1;i <= n;i++){
		fa[i] = i;
	}
	return;
}
int getf(int x){
	if(x != fa[x]){
		fa[x] = getf(fa[x]);
		return fa[x];
	}
	else return fa[x];
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		init();
		bool ok = false;
		int x = 0, y = 0,fx = 0, fy = 0;
		for(int i = 1;i <= m;i++){
			scanf("%d%d",&x,&y);
			fx = getf(x);
			fy = getf(y);
			if(fx != fy){
				fa[fx] = fy;
			}
			else{
				ok = true;
			}
		}
		puts(ok ? "Yes" : "No");
	}
	return 0;
}
/*
2
5 5
1 2
2 3
3 4
4 5
5 1
5 5
1 2
2 3
3 4
4 5
5 1
*/