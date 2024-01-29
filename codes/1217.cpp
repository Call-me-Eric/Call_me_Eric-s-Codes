#include <cstring>
#include <cstdio>

using namespace std;
char map[11][11];
bool a[11];
int n, k, ans;
void dfs(int i, int step){
	if(step == k + 1){ans++;return;}
	bool flag = true;
	for(int j = 0;j < n;j++){
		if(a[j])continue;
		if(map[i][j] == '.')continue;
		a[j] = true;
		dfs(i + 1,step + 1);
		flag = false;
		a[j] = false;
	}
	if( i+1 < n)
		dfs(i + 1,step);
	return;
}
int main(){
	while(scanf("%d%d",&n,&k),(n != -1 && k != -1)){
		memset(a,false,sizeof(a));
		memset(map,'.',sizeof(map));
		for(int i = 0;i < n;i++)scanf("%s",map[i]);
		ans = 0;
		dfs(0,1);
		printf("%d\n",ans);
	}
	return 0;
}

