#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
int n;
string a[21];
int main(){
	cin >> n; 
	for(int i = 1; i <= n; i++)
		cin >>a[i];
	for(int i = 1; i <= n; i++){
		for(int j = i+1; j <= n;j++){
			if(a[i]+a[j] < a[j]+a[i])
				swap(a[i],a[j]);
		}
	}
	for(int i = 1; i <= n; i++)
		cout <<a[i];
	return 0;
}

