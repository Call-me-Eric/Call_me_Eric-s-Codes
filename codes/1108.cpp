#include <iostream>
#include <cstdio>
using namespace std;
int a[10005], b[10005];
int main() {
	int n;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
	}
	for(int i = 1;i <= n;i++){
		scanf("%d",&b[i]);
	}
	long long sum = 0;
	for(int i = 1;i <= n;i++){
		sum = sum + (long long)a[i] * (long long)b[i];
	}
	printf("%lld",sum);
	return 0;
}

