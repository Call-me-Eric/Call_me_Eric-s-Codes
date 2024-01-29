#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const char f[7] = {"ABCDEF"};

int n, p, s[1001], c, m;

int main(){
	ios::sync_with_stdio(false);
	scanf("%d%d",&n,&p);
	while (n != 0){
		c = n % p;
		n = n / p;
		m++;
		s[m] = c;
	}
	for(int k = m;k >= 1;k--){
		if(s[k] >= 10)
			printf("%c",f[s[k] % 10]);
		else
			printf("%d",s[k]);
	}
	return 0;
}

