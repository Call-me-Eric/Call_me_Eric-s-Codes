#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>son[110];
int n, L;
int tree_depth = 0;
void dfs(int pos,int depth){
	tree_depth = max(tree_depth,depth);
	for(int i = 0,len = son[pos].size();i < len;i++){
		dfs(son[pos][i],depth + 1);
	}
}
int main(){
	scanf("%d%d",&n,&L);
	int t = 0;
	for(int i = 1;i < n;i++){
		scanf("%d",&t);
		son[t].push_back(i);
	}
	dfs(0,1);
	if(L < tree_depth)printf("%d",L + 1);
	else printf("%d",min(n,tree_depth + (L - tree_depth + 1) / 2));
	return 0;
}

