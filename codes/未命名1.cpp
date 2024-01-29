#include <bits/stdc++.h>
using namespace std;
int n, m, ans = 0;  
int t[505];		//t【i】为第i个人的到达时刻 
int min[505];  //min【i】为第i个人的最少等待时间 
void dfs(int i, int st){ //搜第i个人,发车时间为st，需等待的最少时间 
	if(i == n + 1)	//都处理完了 
		return;
	//如果车到了还没有人，就让车等到t【i】时刻再发车 
	if(st < t[i])  
		dfs(i, t[i]);
	//考虑两种情况，人等车和车等人，取等待时间的最小值。 
	//如果让人等车
	
	//如果让车等人，车上的人都得等
	int wait_time ; 
}
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i<= n; i++)
		scanf("%d", &t[t]);
	dfs(1,0);
	sort(t + 1, t + n + 1);
	for(int i = 1; i <= n; i++)
		ans += min[i];
	printf("%d\n", ans);
	return 0;
}
