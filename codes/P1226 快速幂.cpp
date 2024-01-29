#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll	 b , p , k;
ll power1(ll a , ll n){
	ll res = 1;
	while(n){
		if(n % 2)
			res = res *  a % k;
		a = a * a % k;	
		n >>= 1; 
	}
	return res %k;
}
ll power(ll a, ll n){
	if(n == 0) return 1 % k;
	ll x = power(a, n/2) % k;
	if(n%2)
		x = x * x * a % k;
	else
		x = x * x  % k ;
	return x % k;
}
int main() {
	scanf("%lld%lld%lld", &b, &p, &k);
	printf("%lld^%lld mod %lld=%lld\n",b,p,k,power1(b,p));
	return 0;
}

