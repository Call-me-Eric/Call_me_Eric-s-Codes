#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e5 + 10;
int n, m, Q;
vector<int> vec[maxn];
signed main(){
	freopen("approx.in","r",stdin);
	freopen("approx.out","w",stdout);
	n = read(); m = read(); Q = read();srand(time(0));
	for(int i = 1;i <= n;i++){
		int k = read();
		for(int j = 1;j <= k;j++)vec[i].push_back(read());
	}
	for(int i = 1;i <= Q;i++){
		int z = read();
		printf("%d\n",rand() % m + 1);
	}
	return 0;
}
