#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3 ) + (ch ^ 48);ch = getchar();}
	return x * f;
}
inline void write(int x){if(!x)return;write(x / 10);putchar('0' + (x % 10));}
const int maxn = 2e3 + 10;
int n, m;
int cnt[maxn * maxn];
vector<int> vec[maxn * maxn];
signed main(){
//	freopen("atom.in","r",stdin);
//	freopen("atom.out","w",stdout);
	n = read();
	for(int len = 1;len < n;len++){
		for(int st = 0,r = min(len - 1,n - len - 1);st <= r;st++){
			m++;if(st)vec[m].push_back(st);
			int pos = st + 1;
			while(pos + len <= n){vec[m].push_back(len);pos += len;}
//			if(n - pos)vec[m].push_back(n - pos);
		}
	}
	write(m);putchar('\n');
	for(int i = 1;i <= m;i++){
		write(vec[i].size());putchar(' ');
		for(int j : vec[i]){write(j);putchar(' ');}
		putchar('\n');
	}
	return 0;
}
