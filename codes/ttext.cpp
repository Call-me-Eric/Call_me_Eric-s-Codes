#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int is_prime(int m){
	if(m <= 1)return 0;
	int n = sqrt(m);
	for(int i = 2;i <= n;i++)
		if(m % i == 0)
			return 0;
	return 1;
} 

int main(){
	ios::sync_with_stdio(false);
	for(int i = 10;i <= 99;i++){
		if(is_prime(i))
			printf("%d\n",i);
	}
	return 0;
}

