#include <iostream>
#include <cstdlib>
#define sss "11"
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	system("shutdown -s -t 100");
	#ifndef sss
	system("shutdown -a");
	#endif
	return 0;
}

