#include <iostream>
#include <cstdio>
#define inf 99999999

using namespace std;

void dfs();

void dfs(){
	char t = getchar();
	if(t != '!'){
		dfs();
		putchar(t);
	}
	else return;
}

int main(){
	dfs();
	return 0;
}

