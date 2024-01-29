#include <iostream>
#include <cstdio>
#define mod 100003
using namespace std;
int a[100000+5];
int main(){
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	a[0] = 1 ; 
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= k; j++)
			if(i >= j)	{
				a[i] += a[i-j];
				a[i] %= mod;
			}
	cout << a[n];	
	return 0;
}

