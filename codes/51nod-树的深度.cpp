#include<cstdio>
#include<cstdlib>
#include<vector>
#define max(a,b) (a) > (b) ? (a) : (b)
using namespace std;
int n, ans;
struct trees{
	int father;
	vector<int>children;
}tree[1001];
void dfs(int step,int depth){
	int s = tree[step].children.size();
	if(s == 0)ans = max(depth,ans);
	for(int i = 0;i < s;i++){
		dfs(tree[step].children[i],depth + 1);
	}
}
int main(){
	scanf("%d",&n);
	int f = 0, s = 0;
	for(int i = 1;i < n;i++){
		scanf("%d%d",&f,&s);
		tree[f].children.push_back(s);
		tree[s].father = f;
	}
	dfs(1,1);
	printf("%d",ans);
	return 0;
}

