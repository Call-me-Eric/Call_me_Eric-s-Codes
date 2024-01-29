#include<cstdio>
#define max(a,b) a > b ? a : b
using namespace std;
int n, ans;
int size[1000001];//以i为树根的最大对称二叉树 
int tree[1000001][2];
int v[1000001];
void dfs(int step){
	size[step] = 1;
	if(tree[step][0] != -1){
		dfs(tree[step][0]);
		size[step] += size[tree[step][0]];
	}
	if(tree[step][1] != -1){
		dfs(tree[step][1]);
		size[step] += size[tree[step][1]];
	}
	return;
}
bool check(int x,int y){
	if(x == -1 && y == -1)return true;
	if(x != -1 && y != -1 && v[x] == v[y])
		if(check(tree[x][0],tree[y][1]) && check(tree[x][1],tree[y][0]))
			return true;
	return false;
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)scanf("%d",&v[i]);
	int t1, t2;
	t1 = t2 = 0;
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&tree[i][0],&tree[i][1]);
	}
	dfs(1);
	for(int i = 1;i <= n;i++)if(check(tree[i][0],tree[i][1]))ans = max(ans,size[i]);
	printf("%d",ans);
	return 0;
}

