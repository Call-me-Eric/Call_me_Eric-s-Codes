#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int inf = 1e9;
int dp[105][105],a[105];
//dp��ʾ��i�죬ӵ��j������ܻ�õ�����ֵ 
int t, n, m;

int main(){
	scanf("%d%d%d", &t, &n, &m);
	for(int i = 1; i <=n; i++)
		scanf("%d", &a[i]);
	if(t == 1) {printf("%d\n", m); return 0; } //10������ 
	for(int i = 0; i <= t; i++)
		for(int j = 0; j <= n; j++){
			if(i == 0 || j == 0)
				dp[i][j] = 0;
			else dp[i][j] = -inf;
		}
	for(int i = 1; i <= t; i++)
		for(int j = 1; j <= n; j++){
			
		}
	return 0;
} 
