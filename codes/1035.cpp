#include <cstdio>
using namespace std;
int main() {
	double sum = 0;
	int i = 0 , k;
	scanf("%d",&k);
	while(sum <= k){
		i++;
		sum += 1.0 / i;
	}
	printf("%d\n",i);
	return 0;
}
