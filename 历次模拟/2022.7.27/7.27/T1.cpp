#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int n;
const int maxn = 10100;
double f[maxn],g[maxn];
int main(){
	scanf("%d",&n);
	for(int i = n - 1;i >= 0;i--){
		f[i] = (double)n / ((double)n - i) + f[i + 1];
		g[i] = 1.0 * n / (1.0 * n - 1.0 * i) + (i * 1.0 * f[i]) / (1.0 * n - 1.0 * i) + g[i + 1] + f[i + 1];
	}
	printf("%.2lf",g[0]);
	return 0;
}

