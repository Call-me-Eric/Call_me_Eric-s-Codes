#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
int n, A[maxn], B[maxn];
signed main(){
	freopen("slauqe.in","r",stdin);
	freopen("slauqe.out","w",stdout);
int T = read();
while(T--){
	n = read();
	for(int i = 1;i <= n;i++)A[i] = read();
	for(int i = 1;i <= n;i++)B[i] = read();
	int a = 0, b = 0, c = 0, d = 0;
	int a0 = 0, b0 = 0, c0 = 0, d0 = 0;
	for(int i = 1;i <= n;i++){
		if(A[i] == 1 && B[i] == 1)a++;
		if(A[i] == 1 && B[i] == 2)b++;
		if(A[i] == 2 && B[i] == 1)c++;
		if(A[i] == 2 && B[i] == 2)d++;
	}
	if(((a + c) & 1) || (abs(b - c) % 2 != 0)){puts("-1");continue;}
	a0 = -1;
	for(c0 = 0;(a + 3 * c - c0 * 6 + 2 * d) >= 0 && c0 <= c;c0++){
		if(b - c + 2 * c0 < 0)continue;
		int x = (a + 3 * c - c0 * 6 + 2 * d) / 2;
		if(x & 1)a0 = 1;else a0 = 0;
		b0 = (b - c + 2 * c0) / 2;
		d0 = (x - a0) / 2;
		if((x - a) / 2 > d){a0 = -1;continue;}
		while(d0 > d && b0 <= b && c0 <= c && a0 <= a){a0 += 2;d0 = (x - a0) / 2;}
		if(a0 <= a && b0 <= b && c0 <= c && d0 <= d)break;
		else a0 = -1;
	}
	if(a0 == -1){puts("-1");continue;}
	for(int i = 1;i <= n;i++){
		if(A[i] == 1 && B[i] == 1){
			if(a0){printf("0 ");a0--;}
			else printf("1 ");
		}
		if(A[i] == 1 && B[i] == 2){
			if(b0){printf("0 ");b0--;}
			else printf("1 ");
		}
		if(A[i] == 2 && B[i] == 1){
			if(c0){printf("0 ");c0--;}
			else printf("1 ");
		}
		if(A[i] == 2 && B[i] == 2){
			if(d0){printf("0 ");d0--;}
			else printf("1 ");
		}
	}
	puts("");
}
	return 0;
}
