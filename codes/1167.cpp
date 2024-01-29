#include <iostream>
#include <cstdio>
using namespace std;

double x, n;

double f(double x,double n){
	if(n == 1)return x / (x + 1);
	return x / (n + f(x,n - 1));
}

int main(){
	ios::sync_with_stdio(false);
	scanf("%lf%lf",&x,&n);
	printf("%.2lf",f(x,n));
	return 0;
}

