#include<bits/stdc++.h>
using namespace std;
signed main(){
	string A, B;
	freopen("test.in","w",stdout);
	int n = 199, m = 100;
	cout << n << " " << m << endl;
	srand(time(0));
	mt19937 rnd(rand());
	for(int i = 1;i <= m;i++){
		int x = rnd() % (n / 2 + 10);
		if(x >= n / 2 + 1){x = n / 2 + 1;}
		cout << x << " ";
	}
	cout << endl;
	fclose(stdout);
	freopen("tmp.out","r",stdin);cin >> A;
	freopen("ans.out","r",stdin);cin >> B;
	fclose(stdin);
	if(A != B){
		cout << "tmp = " << A << " ans = " << B << endl;
	}
	return 0;
}
