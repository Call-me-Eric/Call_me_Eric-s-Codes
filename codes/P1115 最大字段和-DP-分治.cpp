#include <cstdio>
#include <iostream>
#define  MIN -0x7fffffff
using namespace std;
int a[200000 + 5],dp[200000 + 5];

int max (int a , int b){
	return a > b ? a : b;
}
int fun(int l, int r){	//·ÖÖÎ£¬O(nlogn) 
	if(l == r) return a[l];
	int m = (l + r) >> 1;
	int t = max(fun(l, m), fun(m+1, r));
	int sum = 0,suml = MIN, sumr = MIN;
	for(int i = m; i >= l; i--){
		sum += a[i];
		if(sum > suml)	suml = sum;
	}
	sum = 0;
	for(int j = m + 1; j <= r; j++){
		sum += a[j];
		if(sum > sumr) sumr = sum;
	}
	return max(t, suml + sumr);
}
int main(){
	int n, ans = MIN;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	/*for(int i = 1; i <= n; i++){  	//DP OR Ì°ÐÄ O(n)
		dp[i] = max(a[i],dp[i-1]+a[i]);
		ans = max(ans,dp[i]);
	}
	cout << ans <<endl;
	*/ 
	cout << fun(1,n) << endl;
	return 0;
}
