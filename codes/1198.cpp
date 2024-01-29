#include <bits/stdc++.h>

using namespace std;

double dfs(){
	char a[50];
	if(scanf("%s",a))
	switch(a[0]){
		case '+':return dfs() + dfs();break;
		case '-':return dfs() - dfs();break;
		case '*':return dfs() * dfs();break;
		case '/':return dfs() / dfs();break;
		default:{return atof(a);break;}
	}
}

int main(){
	printf("%.6lf",dfs());
	return 0;
}

