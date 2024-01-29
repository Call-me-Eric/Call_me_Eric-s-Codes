#include <cstdio>
#include <iostream>
using namespace std;
int main(){
	long long a, b, res = 1;
	scanf("%lld%lld",&a,&b);
	int i;
	for(i = 1;i <= b;i++){
		res *= a;
		res %= 1000;
	}
	printf("%03lld",res);
	return 0;
}
