#include <iostream>
#include <cstdio>
#define _for(i, a, b) for(int i = a; i <= b; i++)
using namespace std;

char stack[51], t;int top;

int main(){
	while((t = getchar(), t != '@')){
		if(t == '(')stack[++top] = t;
		else if(t == ')'){
			if(top == 0){
				puts("NO");
				return 0;
			}
			else top--;
		}
	}
	if(top)puts("NO");
	else puts("YES");
	return 0;
}

