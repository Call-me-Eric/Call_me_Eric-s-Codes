#include<iostream>
#include<stdio.h>
#include<string.h>
#define TT int
#define mod 4294967296
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1)+ ch - '0';ch = getchar();}
	return x * f;
}
int n, m;
const int maxn = 5e4 + 10;
char ch[maxn];
long long query(int l,int r){
	long long cnt = 0;
	for(int i = l;i <= r;i++){
	for(int j = i + 1;j <= r;j++){
	for(int k = j + 1;k <= r;k++){
		for(int o = k + 1;o <= r;o++){
			for(int p = o + 1;p <= r;p++){
				if(ch[i] == '(' && ch[j] == '0' && ch[k] == 'w' && ch[o] == '0' && ch[p] == ')'){
					cnt++;
					cnt = cnt % mod;
				} 
			}
		}
	}
	}
	}
	return cnt;
}
signed main(){
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	n = read(); m = read();
	char op, z; int x, y;
	scanf("%s",ch + 1);
	for(int i = 1;i <= m;i++){
		op = getchar();
		while(op < 'A' || op > 'C')op = getchar();
		if(op == 'A'){
			x = read(); z = getchar();
			ch[x] = z;
		}
		if(op == 'B'){
			x = read(); y = read(); z = getchar();
			for(int i = x;i <= y;i++)ch[i] = z;
		}
		if(op == 'C'){
			x = read(); y = read();
			printf("%lld\n",query(x,y));
		}
	}
	return 0;
}

