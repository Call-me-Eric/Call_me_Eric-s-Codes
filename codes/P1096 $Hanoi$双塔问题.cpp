#include <iostream>
#include <cstdio>

using namespace std;
long long sum = 0;
long long hano(int x){
	return x == 1?2:hano(x-1)*2+2;
}
int main(){
	int n;
	scanf("%d", &n);
	printf("%lld",hano(n));
	return 0;
}

//void move(int x, char a, char c, char b){  //x由a移动到c 经过b 
//	if(x == 0) return ;
//	move(x-1, a, b, c);
//	sum += 2;
//	move(x-1, b, c, a);
//}
//int main(){
//	ios::sync_with_stdio(false);
//	int n;
//	scanf("%d", &n);
//	move(n,'a','c','b');
//	printf("%lld",sum);
//	return 0;
//}

