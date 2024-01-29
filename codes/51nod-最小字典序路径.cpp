#include<iostream>
#include<stdio.h>
using namespace std;
int n, k;
char c[2021][2021];
int dp[2021][2021];
int book[2021][2021];
int ans[2021];
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 0;i < n;i++){
		getchar();
		for(int j = 0;j < n;j++){
			c[i][j] = getchar();
		}
	}
	//dp是用来找哪一个改为'a'的 
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			if(i == 0) dp[i][j] = dp[i][max(j - 1,0)];
			else if(j == 0) dp[i][j] = dp[max(i - 1,0)][j];
			else dp[i][j] = min(dp[i][j - 1],dp[i - 1][j]);
			if(dp[i][j] < k && c[i][j] != 'a'){
				c[i][j] = 'a';
				dp[i][j]++;
			}
		}
	}
	int res = 0;
	book[0][0] = 1; 
	for(int i = 0;i < 2 * n - 1;i++){
		int n1 = min(n,i + 1);
		char minn = 'z';
		for(int x = max(0,i + 1 - n);x < n1;x++){
			int y = i - x;
			if(x >= 0 && y >= 0 && x < n && y < n){
				if((book[max(x - 1,0)][y] || book[x][max(y - 1,0)]) && c[x][y] < minn){
					minn = c[x][y];
				}
			}
		}
		for(int x = max(0,i + 1 - n);x < n1;x++){
			int y = i - x;
			if(x >= 0 && y >= 0 && x < n && y < n){
				if((book[max(x - 1,0)][y] || book[x][max(y - 1,0)]) && minn == c[x][y]){
					book[x][y] = 1;
				}
			}
		}
		ans[res++] = minn;
	}
	for(int i = 0;i < res;i++){
		putchar(ans[i]);
	}
	putchar('\n');
	return 0;
}

