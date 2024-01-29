#include <cstdio>
#include <iostream>
using namespace std;

int main() {
	int a, sum = 8, c = 0;
	char b;
	scanf("%d %c",&a,&b);
	if(b == 'y')sum += 5;
	if(a > 1000){
		a -= 1000;
	}
	else{
		printf("%d",sum);
		return 0;
	}
	c = a / 500;
	if(a % 500 != 0)c++;
	sum += c * 4;
	printf("%d",sum);
	return 0;
}

