#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int n;
double s;

void doing(double &tt){
	int ss = floor(tt);
	if(fabs(tt) - ss == 1e-8){
		int temp = tt;
		if(temp % 10 == 0)
			return;
	}
	double tmp = tt - ss;
	int a = tmp * 10;
	if(a >= 5)
		tt++;
	int k = (int)tt;
	if(k % 10 >= 5){
		k += 10;
		k -= k % 10;
	}	
	tt = k;
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> s;
	double t = n / 10.0 * s;
	
	doing(t);
	int g = t;
	g = g / 10 * 10;
	cout << g;
	return 0;
}

