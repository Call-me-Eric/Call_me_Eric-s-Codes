#include <bits/stdc++.h>
using namespace std; 

inline int read(void) {
	int x = 0, c = getchar(); 
	while (!isdigit(c)) c = getchar(); 
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); 
	return x; 
}
void print(int x) {
	if (x > 9) print(x / 10); 
	putchar((x % 10) ^ 48); 
}

int n; 
struct Node {
	int a, b, c, d, e, f; 
} a[50005];
int f[50005]; 

int main(void) {
	freopen("frog.in", "r", stdin); 
	freopen("frog.out", "w", stdout); 
	n = read(); 
	for (int i = 1; i <= n; ++i) {
		a[i].a = read(), a[i].b = read(), a[i].c = read(), a[i].d = read(), a[i].e = read(), a[i].f = read(); 
		for (int j = 1; j < i; ++j)
			if (a[j].a <= a[i].a && a[j].b <= a[i].b && a[j].c <= a[i].c && a[j].d <= a[i].d && a[j].e <= a[i].e)
				if (f[j] > f[i]) f[i] = f[j]; 
		print(f[i] += a[i].f); putchar('\n'); 
	}
	return 0; 
} 
