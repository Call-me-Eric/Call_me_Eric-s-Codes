#include<cstdio>
#include<iostream>
using namespace std;
int main(){
	int a, b, n, i;
	double temp;
	cin >> a >> b >> n;
	for(i = 1;i <= n;i++){
		temp = a / b;
		a = temp * 10;
	} 
	printf("%.0lf",temp);
	return 0;
}

