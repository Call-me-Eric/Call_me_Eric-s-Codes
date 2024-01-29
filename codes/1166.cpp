#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

double x, n;

double f(double x, double n){
	if(n == 1)return sqrt(1 + x);
	return sqrt(n + f(x,n - 1));
}

int main(){
	ios::sync_with_stdio(false);
	cin >> x >> n;
	printf("%.2lf",f(x,n));
	return 0;
}

