#include <bits/stdc++.h>
using namespace std;
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	int n,k;
	cin>>n>>k;
	cout<<string(n,'0'+(n==k));
	return 0;
}