#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int tree[50001][2];
int k, n;
bool balanced_tree(int root,int *depth){
	if(root == 0){
		*depth = 0;
		return 1;
	}
	int lt,rt;
	if(balanced_tree(tree[root][0], &lt) && balanced_tree(tree[root][1], &rt)){
		int difference = (rt - lt);
		if(difference <= 1 && difference >= -1){
			*depth = max(rt,lt) + 1;
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d",&k);
	while(k--){
		scanf("%d",&n);
		for(int i = 1;i <= n;i++){
			scanf("%d%d",&tree[i][0],&tree[i][1]);
		}
		int x;
		if(balanced_tree(1,&x) )puts("Yes");
		else puts("No");
	}
	return 0;
}

