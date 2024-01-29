#include <bits/stdc++.h>
using namespace std;
char ch[25*2500+5];
int n = 0;
void win(int x){
	int l = 0, r = 0, i = 1; 
	while(i <= n){
		if(ch[i] == 'W')	l ++;
		else 	r++;
		i++;
		if(l >= x || r >= x){
				if(abs(l-r) >= 2){
					cout << l << ":" << r << endl;
					l = 0; r = 0; 
				}
					
		}
		
	}
	cout << l << ":" << r << endl;
}
int main(){
	char c;
	while(1){
		cin >> c;
		if(c == 'E')	break;
		else
			ch[++n] = c;
	}
	win(11);
	cout << endl;
	win(21);
	return 0;
}
