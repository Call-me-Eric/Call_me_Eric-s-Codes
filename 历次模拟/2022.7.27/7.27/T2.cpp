#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
double N, a[8];
int main(){
	for(int i = 1;i <= 7;i++){scanf("%lf",&a[i]);N += a[i];}
	printf("%.3lf\n",
	2.0 * 3.0 * 4.0 * 5.0 * 6.0 * 7.0 * a[1] / N * a[2] / (N - 1.0) * a[3] / (N - 2.0) * a[4] / (N - 3.0) * a[5] / (N - 4.0) * a[6] / (N - 5.0) * a[7]);
	return 0;
}

