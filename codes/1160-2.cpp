#include <cstring>
#include <cstdio>
#define inf 99999999

using namespace std;

char s[1001]; 

int main(){
	gets(s);
	for(int i = strlen(s) - 1;i >= 0;i--)putchar(s[i]);
	return 0;
}

