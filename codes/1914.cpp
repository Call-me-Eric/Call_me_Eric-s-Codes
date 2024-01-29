#include <iostream>
#include <cstdio>
using namespace std;

int main(){
	int n, len, t, i = 0;
	string str,psw;
	cin >> n;
	cin >> str;
	n %= 26;
	if(n == 0){
		cout <<str;
		return 0;
	}
	len = str.size();
	t = len;
	int tmp;
	while(t){
		tmp = str[i]+n;
		if(tmp > 'z') tmp -= 26;
		psw[i] =(char)tmp;
		i++;
		t--;
	} 
	for(int j = 0; j < len; j++)
		printf("%c",psw[j]);
	printf("\n"); 
	return 0;
}

