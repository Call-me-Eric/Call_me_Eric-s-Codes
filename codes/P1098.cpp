#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
char a[105], b[1005];
int p1, p2, p3; 
char tochar(char j){
	if(j <= 'Z' && j >= 'A'){
		return j + 32;
	}
	return j;
}
char toChar(char j){
	if(j <= 'z' && j >= 'a'){
		return j - 32;
	}
	return j;
}
bool is(char a, char b){
	if( ( (a <= '9' && a >= '0') == true) && ( (b <= 'a' && b <= 'z') == true) )
		return false;
	return true;
}
int main(){
	scanf("%d%d%d",&p1 ,&p2 ,&p3);
	scanf("%s",a + 1);
	int n = strlen(a + 1);
	for(int i = 1;i <= n;i++){
		int size = 0;
		memset(b,0,sizeof(b));
		if(a[i] == '-'){
			if(a[i - 1] < a[i + 1] && is(a[i - 1], a[i + 1])){
					if(a[i - 1] + 1 == a[i + 1])continue;
					if(p1 == 3)
						for(char j = a[i - 1] + 1;j < a[i + 1];j++)
							for(int k = 1;k <= p2;k++)b[size++] = '*';
					if(a[i - 1] <= '9' && a[i - 1] >= '0'){
						if(p1 != 3)
							for(char j = a[i - 1] + 1;j < a[i + 1];j++)
								for(int k = 1;k <= p2;k++)b[size++] = j;
					}
					if(p1 == 1){
						for(char j = a[i - 1] + 1;j < a[i + 1];j++){
							char t = tochar(j);
							for(int k = 1;k <= p2;k++)b[size++] = t;
						}
					}
					if(p1 == 2){
						for(char j = a[i - 1] + 1;j < a[i + 1];j++){
							char t = toChar(j);
							for(int k = 1;k <= p2;k++)b[size++] = t;
						}
					}
					b[size] = '\0';
					if(p3 == 2)	reverse(b, b + size);
					printf("%s",b);
				}

			else putchar(a[i]);	
		}
		else putchar(a[i]);
	}
	return 0;
}

