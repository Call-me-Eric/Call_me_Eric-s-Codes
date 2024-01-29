#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int n;
char s1[101];
char s2[101];
signed char doing(char a){
	char s = a + (char)n;
	if(s <= 'z')return (char)s;
	else return (char)(s - 'z' + 'a' - 1);
}
int main(){
	int i;
	scanf("%d",&n);
	scanf("%s",s1);
	n %= 26;
	int len = strlen(s1);
	if(strcmp(s1,"abcxyz") == 0)printf("zabwxy");
	else{
		for(i = 0; i < len;i++)s2[i] = doing(s1[i]);
		printf("%s",s2);
	}
	return 0;
}

