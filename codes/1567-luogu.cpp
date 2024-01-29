#include <cstdio>
#define inf 99999999
using namespace std;
long long n, start = -1, end, sum = 1, max = -inf;
int main(){
	scanf("%lld",&n); 
	for(int i = 1;i <= n;i++){
		scanf("%lld",&end);
		if(end > start){
			sum++;
			if(sum > max)max = sum;
		}
		else sum = 1;
		start = end;
	}
	printf("%lld",max);
	return 0;
}

