#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>
using namespace std;
int n, ans;
struct trees{
	int father;
	vector<int>children;
}tree[1001];
void dfs(int step);
int main(){
	scanf("%d",&n);
	int f = 0,s = 0;
	for(int i = 1;i < n;i++){
		scanf("%d%d",&f,&s);
		tree[s].father = f;
		tree[f].children.push_back(s);
	}
	dfs(1);
	printf("%d",ans);
	return 0;
}
void dfs(int step){
	int s = tree[step].children.size(); 
	if(s == 0){
		ans++;return;
	}
	for(int i = 0;i < s;i++){
		dfs(tree[step].children[i]);
	}
	return;
}
