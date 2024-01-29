#include <bits/stdc++.h>
using namespace std;
int a[1005];
int main(){
	int n;
	cin >>n;
	a[1] = a[0] = 1;
	for(int i = 2; i <= n; i++){
		if(i %2 == 0)	
			a[i] = a[i-1] + a[i/2];
		else
			a[i] =a[i-1];
	}
	cout << a[n];
	return 0;
}
