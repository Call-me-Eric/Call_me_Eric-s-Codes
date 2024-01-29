#include <cstring>
#include <cstdio>
#define _for(i, a, b) for(int i = a; i <= b; i++)
using namespace std;

long long s[256];
char ch[256];int flag;
long long top, x, len;

int main(){
	gets(ch);
	len = strlen(ch) - 2;
	for(int i = 0;i <= len;i++){
		x = 0;
		switch(ch[i]){
			case '+': s[--top] += s[top + 1];break;
			case '-': s[--top] -= s[top + 1];break;
			case '*': s[--top] *= s[top + 1];break;
			case '/': s[--top] /= s[top + 1];break;
			case '@': flag = 1;break;
			default: {
				while(ch[i] != ' ')x = x * 10 + ch[i++] - '0';
				s[++top] = x;
				break;
			}
		}
		if(flag)break;
	}
	printf("%lld",s[top]);
	return 0;
}

