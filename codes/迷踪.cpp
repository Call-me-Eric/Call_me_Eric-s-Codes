#include <iostream>
#include <cstdio>
#define for1(i, a, b) for(int i = a; i <= b; i++)
using namespace std;

long long a, b, c;

int main(){
	scanf("%lld",&b);
	if(b == 0)printf("A*B B*C");
	if(b > 0)printf("B*C");
	if(b < 0)printf("A*B");
	return 0;
}

