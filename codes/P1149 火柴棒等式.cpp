#include <iostream>
#include <cstdio>

using namespace std;
int n,ans=0;
int a[10] = {6,2,5,5,4,5,6,3,7,6};
int fun(int num){
	int s = 0;
	do{
		s +=a[num%10];
		num /= 10;
	}while(num != 0);
	return s;
}
int main(){
	scanf("%d",&n);
	for(int i = 0 ; i <= 1000; i++)
		for(int j = 0; j <= 1000; j++){
			int c= i + j;
			if(fun(i) + fun(j) + fun(c) == n-4)
				ans++;
	}
	printf("%d\n",ans);
	return 0;
}

