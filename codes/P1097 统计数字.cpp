#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define for1(i, a, b) for(int i = a; i <= b; i++)
const int N = 2e5+5;
int a[N];
using namespace std;

int main(){
	int n , tmp, cnt = 1;
	cin >> n;
	for1(i, 1, n)
		cin >> a[i];
	sort(a+1,a+n+1);
	tmp = a[1];
	for1(i,2,n){
		if(a[i] != tmp){
			cout << tmp<<' ' << cnt << endl;
			cnt = 1;
			tmp = a[i];
		}
		else
			cnt++;
	}
	cout << tmp<<' ' << cnt << endl;
	return 0;
}

