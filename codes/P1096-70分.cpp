#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
unsigned long long dp[201] = {0, 1, 2};//dp[i]=��i��������dp[i]�δ�A���ᵽC���� 
int n, t;
int main(){
	cin >> t;
	n = t * 2;
	for(int i = 3;i <= n;i ++){
		dp[i] = i % 2 == 0 ? dp[i - 1] + 1: 2 * dp[i - 1] + 1;
	}
	cout << dp[n];
	return 0;
}

