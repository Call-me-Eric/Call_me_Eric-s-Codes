#include<iostream>
#include<cstdio>
#include<set>
#include<string>
#include<algorithm>
using namespace std;
set<string> A, B;
string s1,s2;
int n;
int main(){
	while(scanf("%d",&n) && n != 0){
		for(int i = 1;i <= n;i++){
			cin >> s1 >> s2;
			A.insert(s1);
			A.insert(s2);
			B.insert(s2); 
		}
		if(A.size() - B.size() == 1){
			cout << "Yes" << endl;
		}
		else cout << "No" << endl;
	A.clear();B.clear();
	}
	return 0;
}

