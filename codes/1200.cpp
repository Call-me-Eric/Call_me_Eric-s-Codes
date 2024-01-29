#include <cstdio>
#include <cstring>
using namespace std;
int change (char str[]){
	int len = strlen(str);
	long long sub = 1;
	for(int i = 0; i < len;i++){
		sub *= (str[i] -'A'+1);
	}
	return sub % 47;
}
int main() {
	char a[7],b[7];
	scanf("%s %s",a,b);
	//scanf("%s",b);
	if(change(a) == change(b))
		printf("GO");
	else
		printf("STAY");
	return 0;
}
