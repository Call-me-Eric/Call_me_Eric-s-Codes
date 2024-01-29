#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int n, m;

int is_prime(int n){
	for(int i = sqrt(n);i >= 2;i--)
		if(n % i == 0)
			return 0;
	return 1;
}

int gcd(int n){
	for(int i = n / 2;i >= 2;i--)
		if(n % i == 0 && is_prime(i))
			return i;
	return n;
}

int main(){
	ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	printf("%d",gcd(n));
	for(int i = n + 1;i <= m;i++){
		printf(",%d",gcd(i));
	}
	return 0;
}

