#include <iostream>
#include <cstdio>

using namespace std;

inline long long gcd(long long x, long long y){
	long long i, j;
	if(x == 0)return y;
	if(y == 0)return x;
	for(i = 0;(x & 1) == 0;i++)x >>= 1;
	for(j = 0;(y & 1) == 0;j++)y >>= 1;
	if(j < i)i = j;
	while(1){
		if(x < y){x ^= y;y ^= x;x ^= y;}
		if((x -= y) == 0)return y << i;
		while((x & 1) == 0) x >>= 1;
	}
}
inline long long lcm(long long x, long long y){return x * y / gcd(x, y);}

int main(){
	long long a, b;
	scanf("%lld%lld",&a,&b);
	printf("%lld",gcd(a,b));
	return 0;
}

