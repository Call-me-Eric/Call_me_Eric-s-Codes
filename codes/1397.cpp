#include <iostream>
#include <cstdio>
using namespace std;
char s[10001];

int ans(char *k){
	int a = *k - '0', t = 0, tmp = 1;
	while(*k != '\0'){
		tmp = 1;
		k++;
		if(not(*k <= '9' && *k >= '0'))
			switch(*k){
				case '+': a += t;break;
				case '-': a -= t;break;
				case '*': a *= t;break;
				case '/': a /= t;break;
				case '%': a %= t;break;
			}
		else{
			while(*k <= '9' && *k >= '0'){
				t = t * 10 + (*k - '0');
				k++;
			}
		}
	}
	return a;
}

int main(){
	
	ios::sync_with_stdio(false);
	gets(s);
	printf("%d",ans(s));
	return 0;
}

