#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	char str[1000];
	gets(str);
	int len = strlen(str),sum = 0;
	for(int i = 0; i < len; i++)
		if(str[i] !=' ' && str[i] != '\n')
			sum++;
	cout <<sum;
	return 0;
}

