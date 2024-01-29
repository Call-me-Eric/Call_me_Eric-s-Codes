#include <iostream>
#include <cstdio>
using namespace std;

int n, t;
int total;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&t);
		if(t > 70){
			while(t > 70){
				t -= 70;
				total++;
			}
		}
		total++;
	}
	printf("%.1lf",(double)total / 10);
	return 0;
}

