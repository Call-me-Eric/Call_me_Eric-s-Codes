#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0 , f  = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 110, maxk = 9;
char ch[maxn], key[maxn];
int n, m;
signed main(){
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	n = read(); m = read();
	scanf("%s",ch + 1);scanf("%s",key);
	for(int i = 1;i <= n;i++){
		putchar((ch[i] - 'a' + key[(i - 1) % m] - '0') % 26 + 'a');
	}
	puts("");
	return 0;
}
