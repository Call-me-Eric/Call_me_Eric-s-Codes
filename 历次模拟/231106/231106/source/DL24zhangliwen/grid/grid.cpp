#include <bits/stdc++.h> 
using namespace std; 
const int P = 998244353; 

int n; 
int a[505][505]; 

int main(void) {
	freopen("grid.in", "r", stdin); 
	freopen("grid.out", "w", stdout); 
	
	cin >> n; 
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) cin >> a[i][j]; 
	
	return 0; 
} 
