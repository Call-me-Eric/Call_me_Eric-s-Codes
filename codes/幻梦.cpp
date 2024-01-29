#include <iostream>
#include <cstdio>
#define _for(i, a, b) for(int i = a; i <= b; i++)
using namespace std;

int n, k, q, t, ans;

int main(){
	scanf("%d%d%d",&n,&k,&q);
	_for(i, 1, n){scanf("%d",&t);ans += t;}
	printf("%d",ans + k);
	return 0;
}

