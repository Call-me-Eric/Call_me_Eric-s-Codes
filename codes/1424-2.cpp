#include<bits/stdc++.h>
using namespace std;
int main () {
	long long x,n;
	cin>>x>>n;
	long long dis = 0;
	while (n--){
		if(x == 6|| x== 7) {
			x++;
			continue;
		}
			
		if (x == 8) 
			x = 1;
		dis += 250;
		x++;
	}
	cout<<dis;
	return 0;
}

