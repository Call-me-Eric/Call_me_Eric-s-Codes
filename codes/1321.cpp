#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
char n[250];bool flag;int s;
int main(){
	scanf("%s%d",n,&s);
	int len = strlen(n);
	for(int i = 1;i <= s;i++){
		bool did = false;
		for(int j = 0;j < len - 1;j++){
			if(n[j] > n[j + 1]){
				did = true;
				for(int k = j;k <= len - 1;k++)n[k] = n[k + 1];
				len --;
				break;
			}
		}
		if(!did)len --;
	}
	int i = 0;
	while(n[i] == '0' && i < len - 1)i++;
	for(;i < len;i++)putchar(n[i]);
	return 0;
}
