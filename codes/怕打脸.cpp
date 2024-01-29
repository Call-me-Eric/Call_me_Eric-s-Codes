#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	double t;int n;
	scanf("%lf%d",&t,&n);
	double a = (double)t / (double)n;
	int b = 2 * n;
	printf("%.3lf\n%d",a,b);
	return 0;
}
