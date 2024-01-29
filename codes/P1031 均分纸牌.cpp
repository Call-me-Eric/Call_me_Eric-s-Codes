#include <iostream>
#include <cstdio>

using namespace std;
int a[101];
int main(){
	int n, sum=0, ans = 0; 
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >>a[i]; sum+= a[i];
	}
	sum /= n;
	for(int i = 1; i <= n; i++)
		if(a[i] != sum)
			a[i+1] += a[i] - sum,ans++;
	cout << ans;
	return 0;
}

