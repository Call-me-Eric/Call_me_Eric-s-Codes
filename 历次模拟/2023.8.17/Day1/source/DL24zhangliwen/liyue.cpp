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
	putchar(x % 10 + '0'); 
}

int n, q; 
int a[100005], pos[100005]; 
struct Query {
	int l, r, id; 
	bool operator< (const Query &a) const { return r < a.r; }
} Q[100005]; 
int ans[100005], C[100005];
inline void add(int x) { for (; x; x -= x & -x) ++C[x]; } 
inline int sum(int x) { int r = 0; for (; x <= n; x += x & -x) r += C[x]; return r; }

int main(void) {
	freopen("liyue.in", "r", stdin); 
	freopen("liyue.out", "w", stdout); 
	
	n = read(); 
	for (int i = 1; i <= n; ++i) a[i] = read(); 
	q = read(); 
	for (int i = 1; i <= q; ++i) Q[i].l = read(), Q[i].r = read(), Q[i].id = i; 
	sort(Q + 1, Q + q + 1); 
	int r = 0; 
	for (int i = 1; i <= q; ++i) {
		while (r < Q[i].r) {
			++r; 
			for (int j = 1; j * j - a[r] <= n; ++j)
				if (j * j > a[r] && pos[j * j - a[r]]) {
//					printf("[%d %d] [%d %d]\n", r, a[r], pos[j * j - a[r]], a[pos[j * j - a[r]]]); 
					add(pos[j * j - a[r]]); 
				}
			pos[a[r]] = r; 	
		}
		ans[Q[i].id] = sum(Q[i].l); 
	}
	for (int i = 1; i <= q; ++i) print(ans[i]), putchar('\n'); 
	return 0; 
} 

// 离线树状数组
// 查询 >= l 的位置个数 
