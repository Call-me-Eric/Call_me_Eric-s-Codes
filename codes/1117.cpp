#include <iostream>
#include <cstdio>
using namespace std;
int book[5005], a[20002];
int main() {
	int n, t, tn = 1;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&t);
		if(!book[t]){
			book[t] = 1;
			a[tn] = t;
			tn++;
		}
	}
	for(int i = 1;i <= tn - 1;i++){
		printf("%d ",a[i]);
	}
	return 0;
}

