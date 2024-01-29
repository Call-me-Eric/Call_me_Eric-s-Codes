#include <cstdio>
#include <iostream>
using namespace std;
int n, k, ans = 0;
void dfs(int step, int last, int rest) {
	//step为放到第几步，last为上次用的数，rest 为剩下的数 
	if(step == k){
		ans++;
		return;
	}
	for(int i = last; i <= rest/(k-step+1); i++) 	//i <= n 超时60分
	//搜索的剪枝 ，避免超时 
		dfs(step+1,i,rest-i);

}
int main() {
	cin >> n >> k;
	dfs(1,1,n); 
	cout <<ans<<endl;
	return 0;
}

