#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, q;
int a[1000001];
char s; int l, r, w, sum;
int main(){
    n = read(); q = read();
	for(int i = 1;i <= n;i++){a[i] = read();}
	for(int k = 1;k <= q;k++){
		sum = 0;
        scanf(" %c",&s);
        l = read(); r = read(); w = read();
		if(s == 'M'){
			for(int i = l;i <= r;i++){
				a[i] += w;
			}
		}
		else {
			for(int i = l;i <= r;i++){
				if(a[i] >= w)sum++;
			}
			printf("%d\n",sum);
		}
	}
	return 0;
}
