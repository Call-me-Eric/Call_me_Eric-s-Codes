#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
long long a[1000001];
long long n, m;
long long ans;
long long mid = 0,l = 1, r = 0, res = 0;
int main(){
	scanf("%lld%lld",&n,&m);
	for(long long i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
		r = max(r, a[i]);
	}
	while(l <= r){
		res = 0;
		mid = (l + r) / 2;
		for(long long i = 1;i <= n;i ++){
			if(a[i] > mid)res += a[i] - mid;
		}
		if(res < m)r = mid - 1;
		else l = mid + 1;
	}
	printf("%lld",l - 1);
	return 0;
}

