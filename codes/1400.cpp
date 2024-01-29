#include <iostream>
#include <cstdio>
#include <string>
#include <cctype>
using namespace std;

string s[10001], t;
int first, a, b, n;

int main(){
	ios::sync_with_stdio(false);
	int i = 0;
	cin >> t;
	int tmp = t.size();
	for(int i = 0;i < tmp;i++)t[i] = tolower(t[i]);
	while(cin >> s[i]){
		i++;
		for(int j = 0, n = s[i].size();j < n;j++)s[i][j] = tolower(s[i][j]);
	}
	n = i - 1;
	for(i = 0; i <= n;i++){
		if(s[i] == t){
			if(!first)a = i, first = 1;
			b++;
		}
	}
	if(first)
		cout << a << ' ' << b;
	else cout << -1;
	return 0;
}

