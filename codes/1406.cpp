#include <cstring>
#include <cstdio>
#define inf 99999999
using namespace std;

char s[201][201], a[201], b[201]; 

int main(){
	int i = 0;
	while(scanf("%s",s[i++]),s[i][1] != '\n');
	scanf("%s",a);
	scanf("%s",b);
	for(int j = 0;j <= i - 1;j++){
		if(strcmp(s[j],a) == 0)strcpy(s[j],b);
	}
	for(int j = 0;j <= i - 1;j++){
		printf("%s ",s[i]);
	}
	return 0;
}

