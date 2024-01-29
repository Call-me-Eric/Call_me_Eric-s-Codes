#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int a[101],res,ans;
char c,s[101]; 
int main(){
	scanf("%s",&s);
	sscanf(s,"%d-%1d%1d%1d-%1d%1d%1d%1d%1d-%c",
	&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9],&c);
	if(c == 'X')res = 10;
	else res = c - 48;
	for(int i = 1;i <= 9;i++)ans += a[i] * i;
	ans = ans % 11;
	if(ans == res)printf("Right");
	else if(ans == 10)printf("%d-%d%d%d-%d%d%d%d%d-X",
	a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9]);
	else printf("%d-%d%d%d-%d%d%d%d%d-%d",
	a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],ans % 11);
	return 0;
}

