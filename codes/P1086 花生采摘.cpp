#include <cstdio>
#include <cmath>
using namespace std;
int map[22][22];
int m, n, k;
long long ans = 0;
bool inmap(int x, int y){
	if(x >=1 && y >=1 && x <= m && y <= n)
		return true;
	return false;
}
void dfs(int t, int x, int y){
	int maxx = -1;
	int mx, my;
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++){
			if(map[i][j] > maxx){
				maxx = map[i][j];
				mx = i;
				my = j;
			}
		}
	if(y == 0) y = my;
	if(!map[mx][my] || t <(abs(mx-x) + abs(my-y) + mx +1)) 
		return ;
	else{
		ans += map[mx][my];
		map[mx][my] = 0;
		dfs(t - abs(mx-x) - abs(my-y) - 1,mx, my);
	}
	
}
int main(){
	scanf("%d%d%d", &m, &n, &k);
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d",&map[i][j]);
	dfs(k,0,0);
	printf("%d\n", ans);
	return 0;
}
