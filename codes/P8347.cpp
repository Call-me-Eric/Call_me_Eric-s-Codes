#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x  =(x << 1) + (x <<3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e5 + 10;
int d[maxn], n;
void solve(){
	n = read();for(int i = 1;i <= n;i++)d[i] = 0;
	for(int i = 1;i < n;i++){d[read()]++;d[read()]++;}
	for(int i = 1;i <= n;i++)
		if((d[i] & 1) == 0){puts("Hifuu");return;}
	puts("Luna");
}
signed main(){
	int T = read();
	while(T--){solve();}
	return 0;
}
