#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int a[5005];
long long dp[5005];
int main() {
	int n;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
    	dp[i] = 1;//每个都是1，因为刚
		//开始最长的是自己，这次失算了
	}
	for(int i = 2;i <= n;i++){
		for(int j = 1;j < i;j++){//应该在a[i]之前找因此条件是j<i 
			if(a[j] < a[i]){
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
	cout << *max_element(dp + 1, dp + 1 + n) << endl;
	return 0;
}
