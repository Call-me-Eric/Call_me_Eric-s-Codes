#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

//int f[1001] = {0,2}, size = 1;

int is_prime(int n){
	if(n == 1)return 0;
	int k = sqrt(n);
	for(int i = 2;i <= k;i++)
		if(n % i == 0)
			return 0;
	return 1;
}

int main(){
	int n;
	ios::sync_with_stdio(false);
	cin >> n;
	if(is_prime(n) == 1)printf("\\t");
	else printf("\\n");
	return 0;
}

