#include <bits/stdc++.h>
using namespace std;
int main() {
	char ch[15],str[1000005];
	gets(ch);
	gets(str);
	strlwr(ch);
	strlwr(str);
//	puts(ch);
//	puts(str); 
	int len = strlen(str),len1 = strlen(ch);
	int cnt = 0, first = 0,flag = 0;	 
	int i = 0, j = 0; 
	while(i < len){
		j = 0;
		if(str[i] != ch[j]) 
			i++;
		else{
			for(j = 0;j <len1; j++)
				if(str[i] == ch[j]) 
					i++;
				else
					break;
			if(i == j){
				cnt++;
				if(flag == 0){
					flag = 1;
					first = i -len1;
				}		
			}
			
		}
	}
	if(flag == 0)
		printf("-1\n");
	else
		printf("%d %d\n", cnt+1, first);
	return 0;
} 
