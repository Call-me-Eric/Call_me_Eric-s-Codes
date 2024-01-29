#include<iostream>
#include<cstdio>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	long long a1, a2;
	long long sum;
	long long t;
	scanf("%lld",&a1);
	t = a1;
	for(int i = 2;i <= n;i++){
		scanf("%lld",&a2);
		if(a2 > a1)sum += a2 - a1;
		a1 = a2;
	}
	printf("%lld",sum + t);
	return 0;
}

