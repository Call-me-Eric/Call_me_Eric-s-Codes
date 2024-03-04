#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;
int n;
const int maxn = 1e5 +  10;
vector<int> v[maxn];
int dep[maxn];
void dfs(int fa,int u,int depth){
	dep[u] = depth;
	for(int i = 0,len = v[u].size();i < len;i++){
		if(v[u][i] == fa)continue;
		dfs(u,v[u][i],depth + 1);
	}
	return;
}
int main(){
	scanf("%d",&n);
	int x, y;
	for(int i = 1; i < n;i++){
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(0,1,1);
	double ans = 0;
	for(int i = 1;i <= n;i++){
		ans = ans + (double)(1.0 * 1.0 / dep[i]);
	}
	printf("%.20lf\n",ans);
	return 0;
}

