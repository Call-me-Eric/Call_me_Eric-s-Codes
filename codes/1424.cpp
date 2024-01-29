#include <cstdio>
using namespace std;
int a[8] = {0,1,1,1,1,1,0,0}; //´ò±í 
int main() {
	long long x, n,sum = 0;
	int day = 0;
	scanf("%lld %lld",&x, &n);
	while(n){
		day += a[x];
		x++;
		if(x == 8) x = 1;
		n--;
	} 
	sum = day * 250;
	printf("%lld\n",sum);
	return 0;
}
