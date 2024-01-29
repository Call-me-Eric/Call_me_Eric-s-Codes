#include <iostream>
#include <cstdio>
using namespace std;

int main(){
	int n , now, sum = 0, pre = -1, maxn = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d",&now);
		if(now > pre){
			sum++;
			pre = now;
			if(sum > maxn) maxn = sum;
		}	
		else{
			sum = 1;
			pre = now;
			//if(sum > maxn) maxn = sum;
		}
	}
	printf("%d", maxn);
	return 0;
}

