#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

long long a, b;
long long sum(long long n,int div){
	long long tmp = 1;
	long long ans = 0, t = n / tmp / 10;
	long long num = n - (t * 10 * tmp);
	long long temp = 9, digit = 1;
	while(temp != 0){
		temp /= digit;
		if(temp == 0)break;
		digit *= 10;
	}
	while(tmp < digit){
		ans += num/tmp * (tmp - 1) + (num / tmp >= div) * (tmp);
		tmp *= 10;
		t /= 10;
		num = n - (t * 10 * tmp);
	}
	return ans;
}
int main(){
	scanf("%lld%lld",&a,&b);
	printf("%lld /t#/t#/t %lld\n",sum(b,0) , sum(a - 1,0));
	long long temp = 19, digit = 1;
	while(temp != 0){
		temp /= digit;
		if(temp == 0)break;
		digit *= 10;
	}
	printf("%lld",digit);
	return 0;
}

