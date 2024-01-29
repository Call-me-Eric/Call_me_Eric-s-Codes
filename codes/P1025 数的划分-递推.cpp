#include <iostream>
#include <cstdio>
using namespace std;
int ans[201][11]; 
int main(){
	ios::sync_with_stdio();
	int n, k;
	cin >> n >> k;
	for(int i = 0; i <= n; i++){
		ans[i][0] = 0;	ans[i][1] = 1;
	}
	for(int i = 2; i <= 10; i++){	//	i 2-k
		ans[0][i] = 0;	ans[1][i] = 0;
	}
	for(int i = 2; i <= n; i++){
		for(int j = 2; j <= k; j++){
			if(i < j) ans[i][j] = 0;
			else	//第一个数为1和第一个数不为1的情况 
				ans[i][j] = ans[i-1][j-1] + ans[i-j][j];	
		}	
	}
	
		cout << ans[n][k];
	return 0;
}

