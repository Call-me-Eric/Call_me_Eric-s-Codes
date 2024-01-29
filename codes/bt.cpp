#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int main(){
	char s[101];
	int len;
	gets(s);
	len = strlen(s);
	int i, sum = 0;
	for(i = 0;i < len;i++){
		if(s[i] != ' ' && s[i] != '\n')sum++;
	}
	printf("%d",sum);
	return 0;
}
