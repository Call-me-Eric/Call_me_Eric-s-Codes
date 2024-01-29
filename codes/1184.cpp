#include <cstdio>
#include <iostream>
using namespace std;
int tp[1001];
int main(){
	int n;
	scanf("%d",&n);
	int i, temp, tn;
	tn = 0;
	for(i = 1;i <= n;i++){
		scanf("%d",&temp);
		if(tp[temp] == 0)tn++;
		tp[temp] = 1;
	}
	printf("%d\n",tn);
	for(i = 1;i <= 1001;i++){
		if(tp[i] == 1){
			printf("%d ",i);
		}
	}
	return 0;
}

