#include <bits/stdc++.h>
using namespace std; 

int n, q; 
struct Query {
    int l, r, id; 
    bool operator< (const Query &a) const { return r < a.r; }
} Q[200005]; 
struct Edge {
    int u, v; 
    bool operator< (const Edge &a) const { return v < a.v; }
} e[200005]; 
int ans[200005]; 
int C[200005]; 
void add(int x, int k) { for (; x; x -= x & -x) C[x] += k; }
int sum(int x) { int r = 0; for (; x <= n; x += x & -x) r += C[x]; return r; }

int main(void) {
    freopen("lct.in", "r", stdin); 
    freopen("lct.out", "w", stdout); 
    
    scanf("%d%d", &n, &q); 
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &e[i].u, &e[i].v); 
        if (e[i].u > e[i].v) swap(e[i].u, e[i].v); 
    }
    sort(e + 1, e + n); 
    for (int i = 1; i <= q; ++i) scanf("%d%d", &Q[i].l, &Q[i].r), Q[i].id = i; 
    sort(Q + 1, Q + q + 1); 
    for (int i = 1, j = 1; i <= q; ++i) {
        while (j < n && e[j].v <= Q[i].r) add(e[j++].u, 1); 
        ans[Q[i].id] = (Q[i].r - Q[i].l + 1) - sum(Q[i].l); 
    }
    for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]); 
    return 0; 
}