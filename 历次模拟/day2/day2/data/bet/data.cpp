#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return rng()%(r-l+1)+l;
}
int n;
int main(){
	n=ran(100,200);
	printf("%d\n",n);
	for(int i=1;i<=n;i++) printf("%d ",ran(1,n));
	puts("");
}

