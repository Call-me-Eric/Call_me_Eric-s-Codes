#include <cstdio>
using namespace std;
int main() {
	double x,sum = 0, step = 2;
	int i = 0;
	scanf("%lf",&x); // sum += 2*0.98*n;
	while(sum < x) {
		sum += step;
		step *= 0.98;
		i++;
	}
	printf("%d",i);
	return  0;
}
