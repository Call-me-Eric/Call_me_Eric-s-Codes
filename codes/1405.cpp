#include <cstdio>
#include <cmath>
using namespace std;

int s, a, b, max = -99999999;

int is_prime(int m){
	if(m <= 1)return 0;
	int n = sqrt(m);
	for(int i = 2;i <= n;i++)
		if(m % i == 0)
			return 0;
	return 1;
} 

int main(){
	scanf("%d",&s);
	for(a = 2;a <= s;a++){
		b = s - a;
		if(is_prime(a) && is_prime(b)){
			if(max < a * b)
				max = a * b;
		}
	}
	printf("%d\n",max);
	return 0;
}

