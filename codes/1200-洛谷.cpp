#include <string.h>
#include <cstdio>
#define inf 99999999
using namespace std;
char a[11], b[11];
int lena, lenb, suma = 1, sumb = 1;
const bool GO = true, STAY = false;
bool go(){
	int i;
	for(i = 0;i < lena;i++)suma *= (int)(a[i] + 1 - 'a') % 47;
	for(i = 0;i < lenb;i++)sumb *= (int)(b[i] + 1 - 'a') % 47;
	return suma == sumb ? GO : STAY;
}
int main(){
	scanf("%s%s",a,b);
	lena = strlen(a);
	lenb = strlen(b);
	
	if(go() == GO)printf("GO");
	else printf("STAY");
	return 0;
}

