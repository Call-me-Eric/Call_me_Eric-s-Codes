#include <iostream>
#include <cstdio>
#define inf 99999999
using namespace std;

int a[2][10001], n;

int main(){
	scanf("%d",&n);
	int t;
	for(int i = 1;i <= n;i++){
		scanf("%d",&t);
		if(t < 0)a[0][-t]++;
		else a[1][t]++;
	}
	for(int i = 10000;i >= 0;i--)
		for(int j = 1;j <= a[0][i];j++)
			printf("%d ",-i);
	for(int i = 0;i <= 10000;i++)
		for(int j = 1;j <= a[1][i];j++)
			printf("%d ",i);
	return 0;
}

