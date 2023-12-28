#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int main(){
	int n=700,q=2,p=998244353;
	cout<<n<<' '<<q<<'\n';
	for(int r=1;r<=n;r++,puts(""))for(int i=1;i<=n+1;i++)cout<<rnd()%p<<' ';
	for(int i=1;i<=q;i++){
		int id=rnd()%n+1;cout<<id<<' ';
		for(int j=1;j<=n+1;j++)cout<<rnd()%p+1<<' ';puts("");
	}
}

/*

g++ -o gen.exe gen.cpp -O2 -lm -std=c++14 -Wall -Wextra
./gen.exe>in

*/