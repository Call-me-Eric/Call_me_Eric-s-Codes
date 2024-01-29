#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[105], book[20005];
int main(){
	int n, sum = 0;
	scanf("%d", &n);
	for(int i = 1 ; i <= n; i++)
		scanf("%d",&a[i]);
	sort(a+1, a+n+1);
	for(int i = 1 ; i <= n; i++)
		for(int j = i+1 ; j <= n; j++)
			for(int k = j+1; k <= n; k++)
				if(a[i]+a[j] == a[k] && !book[k]){
					sum++;
					book[k] = 1;
				}
	printf("%d",sum);				
	return 0;
}

