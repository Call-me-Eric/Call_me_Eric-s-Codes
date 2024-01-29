#include <iostream>
#include <cstdio>
using namespace std;
int a[10005],b[105],n,m;
int main(){
	int minx = 0x7fffffff, maxx = 0, index = 0;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	for(int i = 1; i <= m; i++)
		b[i] = a[i];
	for(int i = m+1; i <= n;i++){
		index = 0,minx = 0x7fffffff;
		for(int j = 1; j <= m; j++){
			if(b[j] < minx) {
				minx = b[j];
				index = j;	
			}
		}
		b[index] += a[i];
		
	}
	for(int i = 1; i <= m; i++)
		if(b[i] > maxx) maxx = b[i];
	cout << maxx;
	return 0;
}

