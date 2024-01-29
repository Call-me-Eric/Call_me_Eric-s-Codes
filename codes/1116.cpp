#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, start, t;
int main() {
	long long max = 1, res = 1;
	scanf("%d",&n);
	scanf("%d",&start);
	for(int i = 2;i <= n;i++){
		scanf("%d",&t);
//		if(res >= max){
//			max = res;
//		}
		if(start == t){
			res++;
			if (res > max ) max = res; 
		}
		else {
			res = 1;
			start = t;
		}
	}
	printf("%lld",max);
	return 0;
}

