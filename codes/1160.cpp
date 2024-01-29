#include <iostream>
#include <cstdio>
#define inf 99999999

using namespace std;

void dfs();

void dfs(){
	char ch = getchar(); 
	if(ch != '\n')dfs();
	else return;
	putchar(ch);
	
}

int main(){
	dfs();
	return 0;
}

