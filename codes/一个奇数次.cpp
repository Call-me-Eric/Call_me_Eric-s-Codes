#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
unsigned long long ans, t;
int n;
int main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> t;
		ans ^= t;
	}
	cout << ans;
	return 0;
}

