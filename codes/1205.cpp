#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int first;

void dfs(){
	char s[101];
	if(scanf("%s",s) != EOF){
		dfs();
		printf("%s ",s);
	}
	else return;
}

int main(){
	ios::sync_with_stdio(false);
	dfs();
	return 0;
}

