#include<iostream>
#include<stdio.h>
using namespace std;
int x, y;
int main(){
	scanf("%d%d",&x,&y);
	if(x >= y){
		printf("%d",x - y);
		return 0;
	}
	int ans = 0;
	while(x < y){
		ans++;
		if(y & 1)y++;
		else y >>= 1;
	}
	printf("%d",ans + x - y);
	return 0;
}

