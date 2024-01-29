#include <iostream>
#include <cstdio>
using namespace std;

double a, b;

int main(){
	ios::sync_with_stdio(false);
	cin >> a >> b;
	if(a - 1e-8 <= b && a  + 1e-8 >= b && b - 1e-8 <= a && b + 1e-8 >= a)
		cout << "yes";
	else cout << "no";
	return 0;
}

