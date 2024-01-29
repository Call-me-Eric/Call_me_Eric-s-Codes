#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
int main(){
	int n,num;
	string str, ss;
	cin >>n;
	cin >>ss;
	for (int i = 2; i <= n; i++){
		cin >>str;
		if(str-ss > 0){
			num = i;
			ss = str;
		}
	}
	cout<<num<<endl<<ss;
	return 0;
	
}

